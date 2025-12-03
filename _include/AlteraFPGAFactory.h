#pragma once
#include "IFPGAFactory.h"
#include "AlteraControllerWithTransport.h"
#include "TransportI2C.h"
#include <memory>
#include <unordered_map>
#include <mutex>

class AlteraRegisterMap : public IFPGARegisterMap {
    std::unordered_map<uint32_t, uint32_t> regs;
    mutable std::mutex m;
public:
    void set(uint32_t addr, uint32_t value) override;
    uint32_t get(uint32_t addr) const override;
};

class AlteraFPGAFactory : public IFPGAFactory {
public:
    std::unique_ptr<IFPGAController> createController() override;
    std::unique_ptr<IFPGARegisterMap> createRegisterMap() override;
    std::unique_ptr<IFPGAController> createControllerWithTransport(std::unique_ptr<ITransportI2C> t, IFPGARegisterMap* map);
};
