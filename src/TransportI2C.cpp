#include "TransportI2C.h"

bool MockI2C::write(uint8_t addr, const std::vector<uint8_t>& data) {
    (void)addr; (void)data; return true;
}
bool MockI2C::read(uint8_t addr, size_t len, std::vector<uint8_t>& out) {
    (void)addr;
    out.assign(len, 0xAA);
    return true;
}
bool HW_I2C::write(uint8_t addr, const std::vector<uint8_t>& data) {
    (void)addr; (void)data; return true;
}
bool HW_I2C::read(uint8_t addr, size_t len, std::vector<uint8_t>& out) {
    (void)addr; out.assign(len, 0); return true;
}
