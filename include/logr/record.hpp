#ifndef LOGR_RECORD_HPP
#define LOGR_RECORD_HPP

#include <chrono>
#include <meta/source_location.hpp>
#include <sstream>
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

  class Logger;

  class RecordBuilder final {
  public:
    ~RecordBuilder() noexcept;

    RecordBuilder(RecordBuilder&&) = delete;
    RecordBuilder& operator=(RecordBuilder&&) = delete;
    RecordBuilder(const RecordBuilder&) = delete;
    RecordBuilder& operator=(const RecordBuilder&) = delete;

    template <class Writeable>
    RecordBuilder& operator<<(const Writeable& item) {
      msg_buffer_ << item;
      return *this;
    }

  private:
    Logger& logger_;
    Level level_;
    meta::SourceLocation src_loc_;
    std::ostringstream msg_buffer_;

    RecordBuilder(Logger& logger, Level level, const meta::SourceLocation& src_loc);

    friend RecordBuilder build(Logger& logger, Level level, const meta::SourceLocation& src_loc);
  };

  RecordBuilder build(Logger& logger, Level level, const meta::SourceLocation& src_loc = {});
}

#endif // LOGR_RECORD_HPP
