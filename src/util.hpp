#ifndef LOGR_UTIL_HPP
#define LOGR_UTIL_HPP

#include <ios>
#include <locale>

namespace logr::util {
  class IosStateSave final {
  public:
    explicit IosStateSave(std::ios& ios)
        : ios_{ios} {
      copy_state(ios_, old_state_);
      reset_state(ios_);
    }

    ~IosStateSave() noexcept {
      copy_state(old_state_, ios_);
    }

  private:
    std::ios& ios_;
    std::ios old_state_ = std::ios{nullptr};

    static void copy_state(const std::ios& from, std::ios& to) {
      to.flags(from.flags());
      to.width(from.width());
      to.precision(from.precision());
      to.fill(from.fill());
      to.imbue(from.getloc());
    }

    static void reset_state(std::ios& ios) {
      static const auto default_state = std::ios{nullptr};
      copy_state(default_state, ios);
      ios.imbue(std::locale::classic());
    }
  };
}

#endif // LOGR_UTIL_HPP
