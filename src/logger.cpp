#include "logger.hpp"

#include "default.hpp"

namespace logr {
  Logger::Logger(Target& target, Formatter& formatter)
      : target_{&target}
      , formatter_{&formatter} {
  }

  Logger& Logger::global() noexcept {
    static auto instance = new Logger{make_default_logger()};
    return *instance;
  }

  void Logger::append(const Record& record) {
    const auto _ = std::lock_guard{mutex_};
    if (record.level >= threshold_) {
      formatter_(*target_, record);
    }
  }

  const Target* Logger::target() const noexcept {
    return target_;
  }

  void Logger::set_target(Target& target) noexcept {
    const auto _ = std::lock_guard{mutex_};
    target_ = &target;
  }

  Formatter* Logger::formatter() const noexcept {
    return formatter_;
  }

  void Logger::set_formatter(Formatter& formatter) noexcept {
    const auto _ = std::lock_guard{mutex_};
    formatter_ = &formatter;
  }

  Level Logger::threshold() const noexcept {
    return threshold_;
  }

  void Logger::set_threshold(Level threshold) {
    const auto _ = std::lock_guard{mutex_};
    threshold_ = threshold;
  }

  RecordBuilder warning(Logger& logger, const meta::SourceLocation& src_loc) {
    return do_log(logger, Level::Warning, src_loc);
  }

  RecordBuilder error(Logger& logger, const meta::SourceLocation& src_loc) {
    return do_log(logger, Level::Error, src_loc);
  }

  RecordBuilder info(Logger& logger, const meta::SourceLocation& src_loc) {
    return do_log(logger, Level::Info, src_loc);
  }

  RecordBuilder debug(Logger& logger, const meta::SourceLocation& src_loc) {
    return do_log(logger, Level::Debug, src_loc);
  }

  RecordBuilder trace(Logger& logger, const meta::SourceLocation& src_loc) {
    return do_log(logger, Level::Trace, src_loc);
  }
}
