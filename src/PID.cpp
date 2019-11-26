#include "PID.h"
#include <iostream>

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;

  p_error_ = 0.0;
  i_error_ = 0.0;
  d_error_ = 0.0;

  TwiddleKp_.Init(Kp_);
  TwiddleKi_.Init(Ki_);
  TwiddleKd_.Init(Kd_);
}

void PID::UpdateError(double cte) {
  d_error_ = cte - p_error_;
  p_error_ = cte;
  i_error_ += cte;

  // if (!TwiddleKp_.IsFinished()) {
  //   TwiddleKp_.Run(cte * cte, Kp_);
  // } else if (!TwiddleKi_.IsFinished()) {
  //   TwiddleKi_.Run(cte * cte, Ki_);
  // } else 
  // if (!TwiddleKd_.IsFinished()) {
  //   TwiddleKd_.Run(cte * cte, Kd_);
  // }
  // // If individual Twiddles are finished, start again to twiddle
  // if (TwiddleKp_.IsFinished() && TwiddleKi_.IsFinished() &&
  //     TwiddleKd_.IsFinished()) {
  //   std::cout << "Tuning Finished" << std::endl;
  //   TwiddleKp_.Reset(Kp_);
  //   TwiddleKi_.Reset(Ki_);
  //   TwiddleKd_.Reset(Kd_);
  // }
}

double PID::Response() {
  return Kp_ * p_error_ + Ki_ * i_error_ + Kd_ * d_error_;
}