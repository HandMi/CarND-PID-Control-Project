#include "Twiddle.h"
#include <iostream>

Twiddle::Twiddle()
    : twiddle_finished_(false), steps_(0U), delta_(0.0),
      best_total_error_(10000.0), total_error_(0.0) {}

Twiddle::~Twiddle() {}

void Twiddle::Init(double initial_parameter) {
  delta_ = 0.1 * std::abs(initial_parameter);
}

void Twiddle::Reset(double initial_parameter) {
  steps_ = 0U;
  delta_ = 0.1 * initial_parameter;
  twiddle_finished_ = false;
}

bool Twiddle::IsFinished() { return twiddle_finished_; }
void Twiddle::Run(double error, double &parameter) {
  if (twiddle_finished_) {
    return;
  }
  steps_ += 1;
  if (steps_ >= max_steps_ / 10U) {
    total_error_ += error;
  }
  if (steps_ > max_steps_) {
    steps_ = 0;
    std::cout << delta_ << " param " << parameter << " error: " << total_error_
              << std::endl;
    if (total_error_ < best_total_error_) {
      best_parameter_ = parameter;
      best_total_error_ = total_error_;
      parameter += delta_;
      delta_ *= 1.2;
    } else {
      delta_ *= -0.9;
      parameter = best_parameter_ + delta_;
    }
    total_error_ = 0.0;
    if (std::abs(delta_) < (0.01 * std::abs(parameter))) {
      twiddle_finished_ = true;
      parameter = best_parameter_;
      std::cout << "best parameter: " << parameter << std::endl;
      return;
    }
  }
}