#include <logr/logr.hpp>

int main() {
  auto log = logr::make_default_logger();

  logr::info(log) << "hello" << ' ' << "world"; // function call, default src_loc
  logr::info(log, META_CURRENT_SOURCE_LOCATION) << "hello" << ' ' << "world"; // function call, macro for src_loc
  LOGR_LOG_INFO(log) << "hello" << ' ' << "world"; // macro call, calls src_loc macro

  // the last line is the expected use case for applications that use their own logger.
}
