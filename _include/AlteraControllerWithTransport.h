#pragma once
#include "IFPGAController.h"
#include "IFPGARegisterMap.h"
#include "TransportI2C.h"
#include <memory>
#include <vector>

class AlteraControllerWithTransport : public IFPGAController {
    std::unique_ptr<ITransportI2C> i2c;
    IFPGARegisterMap* map_ = nullptr;
public:
    AlteraControllerWithTransport(std::unique_ptr<ITransportI2C> i2c_, IFPGARegisterMap* map=nullptr);
    bool writeRegister(uint32_t addr, uint32_t value) override;
    bool readRegister(uint32_t addr, uint32_t& value) override;
    bool sendPacket(const std::vector<uint8_t>& packet) override;
};
