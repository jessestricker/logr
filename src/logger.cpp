#include "logger.hpp"

#include <array>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string_view>
#include <type_traits>

#include "util.hpp"

namespace {
  using namespace logr;
  using namespace std::string_view_literals;

  constexpr auto level_string(Level level) noexcept {
    constexpr auto str = std::array<std::string_view, 5>{"trc", "dbg", "inf", "wrn", "err"};
    auto&& index = static_cast<std::underlying_type_t<Level>>(level);
    return str.at(index);
  }

  void format_record(Target& target, const Record& record) {
    const auto _ = util::IosStateSave(target);
    target.imbue(std::locale::classic());

    // write to target
    auto&& time = decltype(record.time)::clock::to_time_t(record.time);
    auto&& utc_time = std::gmtime(&time);
    target << '[' << level_string(record.level) << ']';
    target << '[' << std::put_time(utc_time, "%F") << ']';
    target << '[' << std::put_time(utc_time, "%T") << ']';
    if (record.src_loc != meta::SourceLocation{}) {
      target << ' ' << record.src_loc << ':';
    }
    target << ' ' << record.message << '\n';
  }
}

namespace logr {
  Target* default_target() noexcept {
    return &std::cerr;
  }

  Formatter* default_formatter() noexcept {
    return &format_record;
  }

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

  void Logger::set_target(Target* target) noexcept {
    const auto _ = std::lock_guard{mutex_};
    target_ = target ? target : default_target();
  }

  Formatter* Logger::formatter() const noexcept {
    return formatter_;
  }

  void Logger::set_formatter(Formatter* formatter) noexcept {
    const auto _ = std::lock_guard{mutex_};
    formatter_ = formatter ? formatter : default_formatter();
  }

  Level Logger::threshold() const noexcept {
    return threshold_;
  }

  void Logger::set_threshold(Level threshold) {
    const auto _ = std::lock_guard{mutex_};
    threshold_ = threshold;
  }
}
