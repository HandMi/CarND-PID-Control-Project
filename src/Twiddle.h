#ifndef TWIDDLE_H
#define TWIDDLE_H

class Twiddle {
public:
  /**
   * Constructor
   */
  Twiddle();

  /**
   * Destructor.
   */
  virtual ~Twiddle();

  void Init(double initial_parameter);
  void Reset(double initial_parameter);
  void Run(double error, double &parameter);
  bool IsFinished();

private:
  static const unsigned int max_steps_ = 2000U;

  bool twiddle_finished_;
  unsigned int steps_;
  double best_parameter_;
  double delta_;
  double best_total_error_;
  double total_error_;
};

#endif // TWIDDLE_H