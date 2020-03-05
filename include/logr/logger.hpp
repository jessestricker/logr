#ifndef LOGR_LOGGER_HPP
#define LOGR_LOGGER_HPP

#include <iosfwd>
#include <logr/record.hpp>
#include <mutex>

namespace logr {
  using Target = std::ostream;
  using Formatter = void(Target& target, const Record& record);

  class Logger {
  public:
    Logger(Target& target, Formatter& formatter);

    void append(const Record& record);

    [[nodiscard]] const Target* target() const noexcept;
    [[nodiscard]] Formatter* formatter() const noexcept;
    [[nodiscard]] Level threshold() const noexcept;

    void set_target(Target& target) noexcept;
    void set_formatter(Formatter& formatter) noexcept;
    void set_threshold(Level threshold);

  private:
    Target* target_;
    Formatter* formatter_;
    Level threshold_ = Level::Default;
    std::mutex mutex_;
  };
}

#endif // LOGR_LOGGER_HPP
