#include "TransportSPI.h"
#include <mutex>

bool MockSPI::transfer(const std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) {
    static std::mutex m;
    std::lock_guard<std::mutex> lk(m);
    rx = tx;
    return true;
}

bool HW_SPI::transfer(const std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) {
    (void)tx;
    rx.clear();
    return true;
}
