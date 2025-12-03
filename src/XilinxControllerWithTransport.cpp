#include "XilinxControllerWithTransport.h"

XilinxControllerWithTransport::XilinxControllerWithTransport(std::unique_ptr<ITransportSPI> sp, IFPGARegisterMap* map)
    : spi(std::move(sp)), map_(map) {}

bool XilinxControllerWithTransport::writeRegister(uint32_t addr, uint32_t value) {
    std::vector<uint8_t> pkt(8);
    for (int i=0;i<4;i++) pkt[i] = (addr >> (i*8)) & 0xFF;
    for (int i=0;i<4;i++) pkt[4+i] = (value >> (i*8)) & 0xFF;
    std::vector<uint8_t> resp;
    if (!spi->transfer(pkt, resp)) return false;
    if (map_) map_->set(addr, value);
    return true;
}

bool XilinxControllerWithTransport::readRegister(uint32_t addr, uint32_t& value) {
    if (map_) { value = map_->get(addr); return true; }
    value = 0; return true;
}

bool XilinxControllerWithTransport::sendPacket(const std::vector<uint8_t>& packet) {
    std::vector<uint8_t> rx;
    return spi->transfer(packet, rx);
} // 
