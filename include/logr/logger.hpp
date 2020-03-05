#ifndef LOGR_LOGGER_HPP
#define LOGR_LOGGER_HPP

#include <iosfwd>
#include <logr/record.hpp>
#include <mutex>

namespace logr {
  using Target = std::ostream;
  Target* default_target() noexcept;

  using Formatter = void(Target& target, const Record& record);
  Formatter* default_formatter() noexcept;

  class Logger {
  public:
    Logger() = default;
    Logger(Target& target, Formatter& formatter);

    void append(const Record& record);

    [[nodiscard]] const Target* target() const noexcept;
    [[nodiscard]] Formatter* formatter() const noexcept;
    [[nodiscard]] Level threshold() const noexcept;

    void set_target(Target* target) noexcept;
    void set_formatter(Formatter* formatter) noexcept;
    void set_threshold(Level threshold);

  private:
    Target* target_ = default_target();
    Formatter* formatter_ = default_formatter();
    Level threshold_ = Level::Default;
    std::mutex mutex_;
  };
}

#endif // LOGR_LOGGER_HPP
