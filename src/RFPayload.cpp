#include "RFPayload.h"
#include <atomic>
RFPayload::RFPayload() : power_(0.0), frequency_(0.0) {}
void RFPayload::setPower(double p) { power_ = p; }
double RFPayload::getPower() const { return power_; }
void RFPayload::setFrequency(double f) { frequency_ = f; }
double RFPayload::getFrequency() const { return frequency_; }
