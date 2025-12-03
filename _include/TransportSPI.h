#pragma once
#include <vector>
#include <cstdint>

class ITransportSPI {
public:
    virtual ~ITransportSPI() = default;
    virtual bool transfer(const std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) = 0;
};

class MockSPI : public ITransportSPI {
public:
    bool transfer(const std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) override;
};

class HW_SPI : public ITransportSPI {
public:
    bool transfer(const std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) override;
};
