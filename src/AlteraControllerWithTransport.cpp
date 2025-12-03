#include "AlteraControllerWithTransport.h"

AlteraControllerWithTransport::AlteraControllerWithTransport(std::unique_ptr<ITransportI2C> i2c_, IFPGARegisterMap* map)
    : i2c(std::move(i2c_)), map_(map) {}

bool AlteraControllerWithTransport::writeRegister(uint32_t addr, uint32_t value) {
    std::vector<uint8_t> data(8);
    for (int i=0;i<4;i++) data[i] = (addr >> (i*8)) & 0xFF;
    for (int i=0;i<4;i++) data[4+i] = (value >> (i*8)) & 0xFF;
    if (!i2c->write(0x50, data)) return false;
    if (map_) map_->set(addr, value);
    return true;
}
bool AlteraControllerWithTransport::readRegister(uint32_t addr, uint32_t& value) {
    if (map_) { value = map_->get(addr); return true; }
    value = 0; return true;
}
bool AlteraControllerWithTransport::sendPacket(const std::vector<uint8_t>& packet) {
    return i2c->write(0x50, packet);
} // 