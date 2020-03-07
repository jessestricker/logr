#include "record.hpp"

#include "logger.hpp"

namespace logr {
  RecordBuilder::RecordBuilder(Logger& logger, Level level, const meta::SourceLocation& src_loc)
      : logger_{logger}
      , level_{level}
      , src_loc_{src_loc} {
  }

  RecordBuilder::~RecordBuilder() noexcept {
    auto rec = Record{};
    rec.level = level_;
    rec.src_loc = src_loc_;
    rec.message = msg_buffer_.str();
    logger_.append(rec);
  }

  RecordBuilder do_log(Logger& logger, Level level, const meta::SourceLocation& src_loc) {
    return {logger, level, src_loc};
  }
}
