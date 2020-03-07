#include "default.hpp"

#include <array>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string_view>

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
  Target& default_target() noexcept {
    return std::cerr;
  }

  Formatter& default_formatter() noexcept {
    return format_record;
  }

  Logger make_default_logger() {
    return Logger(default_target(), default_formatter());
  }
}
