#include "AllocatePowerCommand.h"
AllocatePowerCommand::AllocatePowerCommand(RFPayload& p, double level) : payload(p), powerLevel(level) {}
void AllocatePowerCommand::execute() { payload.setPower(powerLevel); }
