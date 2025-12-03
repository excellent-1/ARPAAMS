#pragma once
#include "IFPGAFactory.h"
#include "XilinxControllerWithTransport.h" // Will be included in Command Pattern commit
#include "TransportSPI.h" // Will be included in Command Pattern commit
#include <memory>
#include <unordered_map>
#include <mutex>

class XilinxRegisterMap : public IFPGARegisterMap {
    std::unordered_map<uint32_t, uint32_t> regs;
    mutable std::mutex m;
public:
    void set(uint32_t addr, uint32_t value) override;
    uint32_t get(uint32_t addr) const override;
};

class XilinxFPGAFactory : public IFPGAFactory {
public:
    std::unique_ptr<IFPGAController> createController() override;
    std::unique_ptr<IFPGARegisterMap> createRegisterMap() override;
  //Will be included in Command Pattern commit
  //  std::unique_ptr<IFPGAController> createControllerWithTransport(std::unique_ptr<ITransportSPI> t, IFPGARegisterMap* map);
};
