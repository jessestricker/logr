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

    friend RecordBuilder do_log(Logger& logger, Level level, const meta::SourceLocation& src_loc);
  };

  RecordBuilder do_log(Logger& logger, Level level, const meta::SourceLocation& src_loc = {});

  inline RecordBuilder trace(Logger& logger, const meta::SourceLocation& src_loc = {}) {
    return do_log(logger, Level::Trace, src_loc);
  }

  inline RecordBuilder debug(Logger& logger, const meta::SourceLocation& src_loc = {}) {
    return do_log(logger, Level::Debug, src_loc);
  }

  inline RecordBuilder info(Logger& logger, const meta::SourceLocation& src_loc = {}) {
    return do_log(logger, Level::Info, src_loc);
  }

  inline RecordBuilder warning(Logger& logger, const meta::SourceLocation& src_loc = {}) {
    return do_log(logger, Level::Warning, src_loc);
  }

  inline RecordBuilder error(Logger& logger, const meta::SourceLocation& src_loc = {}) {
    return do_log(logger, Level::Error, src_loc);
  }
}

#define LOGR_LOG_TRACE(logger__) ::logr::trace(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_DEBUG(logger__) ::logr::debug(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_INFO(logger__) ::logr::info(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_WARNING(logger__) ::logr::warning(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_ERROR(logger__) ::logr::error(logger__, META_CURRENT_SOURCE_LOCATION)

#endif // LOGR_RECORD_HPP
