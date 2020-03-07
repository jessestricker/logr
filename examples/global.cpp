#include <logr/logr.hpp>

int main() {
  // simple
  auto rec = logr::Record{};
  rec.message = "hello world";
  logr::Logger::global().append(rec);

  // or via record builder
  logr::info(logr::Logger::global()) << "hello world";
  logr::info() << "hello world";
  LOGR_INFO() << "hello world"; // macro call, used for source location
}
