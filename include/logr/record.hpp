#ifndef LOGR_RECORD_HPP
#define LOGR_RECORD_HPP

#include <chrono>
#include <meta/source_location.hpp>
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

  struct Record {
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    TimePoint time = TimePoint::clock::now();
    Level level = Level::Default;
    meta::SourceLocation src_loc;
    std::string message;
  };
}

#endif // LOGR_RECORD_HPP
