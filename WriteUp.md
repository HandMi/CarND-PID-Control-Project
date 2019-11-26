# **PID Control Project**

In this project we were asked to implement a [PID Controller](https://en.wikipedia.org/wiki/PID_controller) to regulate a car's steering behavior on a predefined test track. The 3 PID hyperparameters were then tuned according to the suggested Twiddle algorithm.

## Effect of the PID Parameters

### Proportional Parameter

The P parameter controls the direct response to any deviation from the center line. In the project this parameter needs to be set high enough such that the car responds quickly to sudden direction changes but low enough to not cause any oscillations. The higher this parameter was set the more the car started to oscillate around the center line (in amplitude) and the slower it went back to an equilibrium position.

### Integral Parameter

The I parameter accounts for aggregate error of time, this may be inherent bias in the system or situations where the P parameter alone does not produce an adequate response (e.g. corners). Setting this value too high produces instabilities and oscillations, or even uncontrollable overshoot. Is this value set too low the car will have less stable trajectories, especially in corners.

### Derivative Parameter

Finally, the D parameter reacts to sudden changes the error. In contrast to P and I paramater it slows down the response of the system and smoothens the trajectory. High values dampen out oscillations of the car but also make it slower to react to errors. Low D parameter values cause overshooting and increase the oscillations inherent to a P or PI controller system.

### Final parameters

Initially, the parameters were manually tuned to values that allowed the car to relatively safely complete the course. Then a slightly simplified Twiddle/Local Hill climbing algorithm was applied to the PID controller of the car. This algorithm can be found in the 'Twiddle' class in the source code. Each Twiddle cycle accumulates the error for 2000 steps. Then the total squared error is compared to he best result so far. If the new parameters perform better, the algorithm continues to test values around the optimal parameter until it eventually converges. 
P, I and D parameters are tuned consecutively:

```cpp
if (!TwiddleKp_.IsFinished()) {
  TwiddleKp_.Run(cte * cte, Kp_);
} else if (!TwiddleKi_.IsFinished()) {
  TwiddleKi_.Run(cte * cte, Ki_);
} else 
if (!TwiddleKd_.IsFinished()) {
  TwiddleKd_.Run(cte * cte, Kd_);
}
// If individual Twiddles are finished, start again to twiddle
if (TwiddleKp_.IsFinished() && TwiddleKi_.IsFinished() &&
    TwiddleKd_.IsFinished()) {
  std::cout << "Tuning Finished" << std::endl;
}
```

The best parameter set in my Twiddle Run were (-0.198004, -0.00095, -1.2535). As can be seen in the video, the car still tends to oscillate a little bit. It seems like the system prefers small oscillations around the mean instead of having longer periods of smooth overshoot or undershoot. However, these parameters become unmaintainable when the throttle is increased. At high throttle, the P parameter has to be tuned down (e.g. to -1.2) and the D parameter has to be tuned up (e.g. to -2.5) to keep the car from oscillating.

The final video can be found [here](https://www.youtube.com/watch?v=fm9Q232JsXM).