#include <chrono>
#include <logr/logr.hpp>
#include <thread>

using namespace std::chrono_literals;

int main() {
  auto log = logr::Logger();
  auto rec = logr::Record{};

  rec.message = "hello";
  log.append(rec);

  std::this_thread::sleep_for(1s);

  rec.message = "oops", rec.level = logr::Level::Warning;
  log.append(rec);

  std::this_thread::sleep_for(1s);

  rec.message = "oh noo", rec.level = logr::Level::Error;
  log.append(rec);

  std::this_thread::sleep_for(1s);

  rec.message = "secret", rec.level = logr::Level::Debug;
  log.append(rec);
}
