#pragma once
#include "IFPGAController.h"
#include "IFPGARegisterMap.h"
#include <memory>

class IFPGAFactory {
public:
    virtual std::unique_ptr<IFPGAController> createController() = 0;
    virtual std::unique_ptr<IFPGARegisterMap> createRegisterMap() = 0;
    virtual ~IFPGAFactory() = default;
};
