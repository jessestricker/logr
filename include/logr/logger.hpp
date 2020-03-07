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

    static Logger& global() noexcept;

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

  RecordBuilder trace(Logger& logger = Logger::global(), const meta::SourceLocation& src_loc = {});
  RecordBuilder debug(Logger& logger = Logger::global(), const meta::SourceLocation& src_loc = {});
  RecordBuilder info(Logger& logger = Logger::global(), const meta::SourceLocation& src_loc = {});
  RecordBuilder warning(Logger& logger = Logger::global(), const meta::SourceLocation& src_loc = {});
  RecordBuilder error(Logger& logger = Logger::global(), const meta::SourceLocation& src_loc = {});
}

#define LOGR_LOG_TRACE(logger__) ::logr::trace(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_DEBUG(logger__) ::logr::debug(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_INFO(logger__) ::logr::info(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_WARNING(logger__) ::logr::warning(logger__, META_CURRENT_SOURCE_LOCATION)
#define LOGR_LOG_ERROR(logger__) ::logr::error(logger__, META_CURRENT_SOURCE_LOCATION)

#define LOGR_TRACE() LOGR_LOG_TRACE(::logr::Logger::global())
#define LOGR_DEBUG() LOGR_LOG_DEBUG(::logr::Logger::global())
#define LOGR_INFO() LOGR_LOG_INFO(::logr::Logger::global())
#define LOGR_WARNING() LOGR_LOG_WARNING(::logr::Logger::global())
#define LOGR_ERROR() LOGR_LOG_ERROR(::logr::Logger::global())

#endif // LOGR_LOGGER_HPP
