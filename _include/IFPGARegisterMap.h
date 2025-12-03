#pragma once
#include <cstdint>

class IFPGARegisterMap {
public:
    virtual ~IFPGARegisterMap() = default;
    virtual void set(uint32_t addr, uint32_t value) = 0;
    virtual uint32_t get(uint32_t addr) const = 0;
};
