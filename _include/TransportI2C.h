#pragma once
#include <vector>
#include <cstdint>

class ITransportI2C {
public:
    virtual ~ITransportI2C() = default;
    virtual bool write(uint8_t addr, const std::vector<uint8_t>& data) = 0;
    virtual bool read(uint8_t addr, size_t len, std::vector<uint8_t>& out) = 0;
};

class MockI2C : public ITransportI2C {
public:
    bool write(uint8_t addr, const std::vector<uint8_t>& data) override;
    bool read(uint8_t addr, size_t len, std::vector<uint8_t>& out) override;
};

class HW_I2C : public ITransportI2C {
public:
    bool write(uint8_t addr, const std::vector<uint8_t>& data) override;
    bool read(uint8_t addr, size_t len, std::vector<uint8_t>& out) override;
};
