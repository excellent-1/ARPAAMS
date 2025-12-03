#pragma once
#include "ICommand.h"
#include "RFPayload.h"

class FrequencySwitchCommand : public ICommand {
    RFPayload& payload;
    double frequency;
public:
    FrequencySwitchCommand(RFPayload& p, double freq);
    void execute() override;
};
