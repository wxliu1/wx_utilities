
#ifndef _TIME_ELAPSED_
#define _TIME_ELAPSED_

// Integer types of known sizes.
using TimeInMillis = int64_t;  // Represents time in milliseconds.

class Timer {
 public:
  Timer() : start_(clock::now()) {}

  // Return time elapsed in milliseconds since the timer was created.
  TimeInMillis Elapsed() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() -
                                                                 start_)
        .count();
  }

 private:
  // Fall back to the system_clock when building with newlib on a system
  // without a monotonic clock.
#if defined(_NEWLIB_VERSION) && !defined(CLOCK_MONOTONIC)
  using clock = std::chrono::system_clock;
#else
  using clock = std::chrono::steady_clock;
#endif
  clock::time_point start_;
};

// Returns a timestamp as milliseconds since the epoch. Note this time may jump
// around subject to adjustments by the system, to measure elapsed time use
// Timer instead.
TimeInMillis GetTimeInMillis() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now() -
             std::chrono::system_clock::from_time_t(0))
      .count();
}

#endif