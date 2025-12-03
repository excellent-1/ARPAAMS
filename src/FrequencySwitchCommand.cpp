#include "FrequencySwitchCommand.h"
FrequencySwitchCommand::FrequencySwitchCommand(RFPayload& p, double freq) : payload(p), frequency(freq) {}
void FrequencySwitchCommand::execute() { payload.setFrequency(frequency); }
