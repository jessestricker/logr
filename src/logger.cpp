#include "logger.hpp"

namespace logr {
  Logger::Logger(Target& target, Formatter& formatter)
      : target_{&target}
      , formatter_{&formatter} {
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
}
