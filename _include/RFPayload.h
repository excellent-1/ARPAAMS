#pragma once
class RFPayload {
public:
    RFPayload();
    void setPower(double p);
    double getPower() const;
    void setFrequency(double f);
    double getFrequency() const;
private:
    double power_;
    double frequency_;
};
