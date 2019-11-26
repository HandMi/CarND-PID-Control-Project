#ifndef PID_H
#define PID_H

#include "Twiddle.h"

class PID {
public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp, double Ki, double Kd);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID Response
   * @output The PID Response Term
   */
  double Response();

private:
  /**
   * PID Errors
   */
  double p_error_;
  double i_error_;

  double d_error_;
  /**
   * PID Coefficients
   */
  double Kp_;
  double Ki_;
  double Kd_;

  /**
   * Twiddles
   */
  Twiddle TwiddleKp_;
  Twiddle TwiddleKi_;
  Twiddle TwiddleKd_;
};

#endif // PID_H