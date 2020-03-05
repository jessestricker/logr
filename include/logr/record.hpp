#ifndef LOGR_RECORD_HPP
#define LOGR_RECORD_HPP

#include <chrono>
#include <string>

namespace logr {
  enum class Level : unsigned {
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warning = 3,
    Error = 4,

    Default = Info,
  };

  using TimePoint = std::chrono::system_clock::time_point;

  struct Record {
    TimePoint time = TimePoint::clock::now();
    Level level = Level::Default;
    std::string message;
  };
}

#endif // LOGR_RECORD_HPP
