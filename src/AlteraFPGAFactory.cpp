#include "AlteraFPGAFactory.h"

void AlteraRegisterMap::set(uint32_t addr, uint32_t value) {
    std::lock_guard<std::mutex> lk(m); regs[addr] = value;
}
uint32_t AlteraRegisterMap::get(uint32_t addr) const {
    std::lock_guard<std::mutex> lk(m); auto it = regs.find(addr); return (it!=regs.end())?it->second:0u;
}

std::unique_ptr<IFPGAController> AlteraFPGAFactory::createController() {
    return std::make_unique<AlteraControllerWithTransport>(std::make_unique<MockI2C>(), nullptr);
}
std::unique_ptr<IFPGARegisterMap> AlteraFPGAFactory::createRegisterMap() {
    return std::make_unique<AlteraRegisterMap>();
}
std::unique_ptr<IFPGAController> AlteraFPGAFactory::createControllerWithTransport(std::unique_ptr<ITransportI2C> t, IFPGARegisterMap* map) {
    return std::make_unique<AlteraControllerWithTransport>(std::move(t), map);
}
