/*
#include "XilinxFPGAFactory.h"
#include "IFPGAController.h"

std::unique_ptr<IFPGAController> XilinxFPGAFactory::createController() {
    return nullptr; // TODO: implement when Xilinx controller exists
}

std::unique_ptr<IFPGAController> 
XilinxFPGAFactory::createControllerWithTransport(
    std::unique_ptr<void> , //transport
    IFPGARegisterMap* //map
) {
    return nullptr; // TODO
}
*/


#include "XilinxFPGAFactory.h"

void XilinxRegisterMap::set(uint32_t addr, uint32_t value) {
    std::lock_guard<std::mutex> lk(m); regs[addr] = value;
}
uint32_t XilinxRegisterMap::get(uint32_t addr) const {
    std::lock_guard<std::mutex> lk(m); auto it = regs.find(addr); return (it!=regs.end())?it->second:0u;
}

std::unique_ptr<IFPGAController> XilinxFPGAFactory::createController() {
    return std::make_unique<XilinxControllerWithTransport>(std::make_unique<MockSPI>(), nullptr);
}
std::unique_ptr<IFPGARegisterMap> XilinxFPGAFactory::createRegisterMap() {
    return std::make_unique<XilinxRegisterMap>();
}
std::unique_ptr<IFPGAController> XilinxFPGAFactory::createControllerWithTransport(std::unique_ptr<ITransportSPI> t, IFPGARegisterMap* map) {
    return std::make_unique<XilinxControllerWithTransport>(std::move(t), map);
}
