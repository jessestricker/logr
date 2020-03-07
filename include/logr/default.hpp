#ifndef LOGR_DEFAULT_HPP
#define LOGR_DEFAULT_HPP

#include <logr/logger.hpp>

namespace logr {
  Target& default_target() noexcept;
  Formatter& default_formatter() noexcept;
  Logger make_default_logger();
}

#endif // LOGR_DEFAULT_HPP
