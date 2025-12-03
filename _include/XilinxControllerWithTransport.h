#pragma once
#include "IFPGAController.h"
#include "IFPGARegisterMap.h"
#include "TransportSPI.h"
#include <memory>
#include <vector>

class XilinxControllerWithTransport : public IFPGAController {
    std::unique_ptr<ITransportSPI> spi;
    IFPGARegisterMap* map_;
public:
    XilinxControllerWithTransport(std::unique_ptr<ITransportSPI> sp, IFPGARegisterMap* map=nullptr);
    bool writeRegister(uint32_t addr, uint32_t value) override;
    bool readRegister(uint32_t addr, uint32_t& value) override;
    bool sendPacket(const std::vector<uint8_t>& packet) override;
}; //
 