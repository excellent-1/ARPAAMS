#pragma once
#include <vector>
#include <cstdint>

class IFPGAController {
public:
    virtual ~IFPGAController() = default;
    virtual bool writeRegister(uint32_t addr, uint32_t value) = 0;
    virtual bool readRegister(uint32_t addr, uint32_t& value) = 0;
    virtual bool sendPacket(const std::vector<uint8_t>& packet) = 0;
};
