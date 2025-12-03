#include <gtest/gtest.h>
#include <chrono>
#include <iostream>

#include "TestConfig.h"
#include "FaultEvent.h"
#include "RFPayloadMonitor.h"
#include "RecoveryModule.h"
#include "XilinxFPGAFactory.h"
#include "AlteraFPGAFactory.h"
#include "RFPayload.h"
#include "AllocatePowerCommand.h"
#include "FrequencySwitchCommand.h"
#include "ResourceManager.h"
#include "TransportSPI.h"
#include "TransportI2C.h"

using namespace std::chrono_literals;

static void checkDeadlineOrWarn(std::chrono::steady_clock::duration dur,
                                std::chrono::steady_clock::duration limit,
                                const char* message) {
    if (HardFailOrWarning.load()) {
        ASSERT_LE(dur, limit) << message;
    } else {
        if (dur > limit) {
            std::cerr << "[WARNING] Timing threshold exceeded (" << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
                      << "us > " << std::chrono::duration_cast<std::chrono::microseconds>(limit).count()
                      << "us): " << message << std::endl;
        }
    }
}

TEST(ObserverPattern, SingleObserverReceivesEvent) {
    RFPayloadMonitor monitor;
    RecoveryModule recovery;
    monitor.registerObserver(&recovery);
    FaultEvent fe("RFChain1", 123, FaultEvent::Severity::CRITICAL);
    monitor.detectFault(fe);
    ASSERT_TRUE(recovery.wasRecoveryTriggered());
}

TEST(ObserverPattern, NotifyWithin50us) {
    RFPayloadMonitor monitor;
    RecoveryModule recovery;
    monitor.registerObserver(&recovery);
    FaultEvent fe("RFChain3", 999, FaultEvent::Severity::CRITICAL);
    auto start = std::chrono::steady_clock::now();
    monitor.detectFault(fe);
    auto end = std::chrono::steady_clock::now();
    checkDeadlineOrWarn(end - start, std::chrono::microseconds(50), "Observer notification exceeded 50us");
}

TEST(FactoryPattern, CreateControllersAndMaps) {
    XilinxFPGAFactory xilinx;
    auto map = xilinx.createRegisterMap();
    auto ctrl = xilinx.createControllerWithTransport(std::make_unique<MockSPI>(), map.get());
    uint32_t addr = 0x1;
    ctrl->writeRegister(addr, 0xAABBCCDD);
    uint32_t val=0; ctrl->readRegister(addr,val);
    ASSERT_EQ(val, 0xAABBCCDD);
}

TEST(CommandPattern, AllocateAndFrequencyCommands) {
    RFPayload p;
    AllocatePowerCommand a(p, 12.3);
    FrequencySwitchCommand f(p, 2.2e9);
    a.execute(); f.execute();
    ASSERT_DOUBLE_EQ(p.getPower(), 12.3);
    ASSERT_DOUBLE_EQ(p.getFrequency(), 2.2e9);
}

TEST(CommandPattern, ProcessQueueUnder500us) {
    ResourceManager rm; RFPayload p1,p2;
    rm.addCommand(std::make_unique<AllocatePowerCommand>(p1, 10.0));
    rm.addCommand(std::make_unique<FrequencySwitchCommand>(p1, 2.4e9));
    rm.addCommand(std::make_unique<AllocatePowerCommand>(p2, 7.7));
    auto start = std::chrono::steady_clock::now();
    rm.processCommands();
    auto end = std::chrono::steady_clock::now();
    checkDeadlineOrWarn(end - start, std::chrono::microseconds(500), "Processing command queue exceeded 500us");
    ASSERT_DOUBLE_EQ(p1.getPower(), 10.0);
    ASSERT_DOUBLE_EQ(p1.getFrequency(), 2.4e9);
    ASSERT_DOUBLE_EQ(p2.getPower(), 7.7);
}

TEST(Integration, FaultTriggersRecoveryAndRecoveryAddsRecoveryCommand) {
    RFPayloadMonitor monitor;
    ResourceManager rm; RFPayload payload;
    struct RecoveryWithCmd : public RecoveryModule {
        ResourceManager* rmPtr = nullptr; RFPayload* payloadPtr = nullptr;
        void notifyFault(const FaultEvent& e) override {
            RecoveryModule::notifyFault(e);
            if (rmPtr && payloadPtr) {
                rmPtr->addCommand(std::make_unique<AllocatePowerCommand>(*payloadPtr, 0.0));
            }
        }
    };
    RecoveryWithCmd rec;
    rec.rmPtr = &rm; rec.payloadPtr = &payload;
    monitor.registerObserver(&rec);
    FaultEvent fe("RFChain4", 777, FaultEvent::Severity::CRITICAL);
    auto start = std::chrono::steady_clock::now();
    monitor.detectFault(fe);
    rm.processCommands();
    auto end = std::chrono::steady_clock::now();
    ASSERT_DOUBLE_EQ(payload.getPower(), 0.0);
    checkDeadlineOrWarn(end - start, std::chrono::milliseconds(1), "End-to-end exceeded 1ms");
}

TEST(HIL, XilinxControllerWithSPI_MockWorks) {
    XilinxFPGAFactory factory; auto map = factory.createRegisterMap();
    auto ctrl = factory.createControllerWithTransport(std::make_unique<MockSPI>(), map.get());
    uint32_t addr = 0x20;
    ASSERT_TRUE(ctrl->writeRegister(addr, 0x12345678));
    uint32_t val=0; ASSERT_TRUE(ctrl->readRegister(addr,val));
    ASSERT_EQ(val, 0x12345678);
}
