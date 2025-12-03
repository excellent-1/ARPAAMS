#pragma once
#include "ICommand.h"
#include "RFPayload.h"

class AllocatePowerCommand : public ICommand {
    RFPayload& payload;
    double powerLevel;
public:
    AllocatePowerCommand(RFPayload& p, double level);
    void execute() override;
};
