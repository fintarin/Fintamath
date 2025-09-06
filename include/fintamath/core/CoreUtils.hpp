#pragma once

#include <utility>

namespace fintamath::detail {

template <typename Number, typename Callback>
constexpr void repeat(const Number &num, Callback &&callback) {
  for (Number i = 0; i < num; ++i) {
    std::forward<Callback>(callback)();
  }
}

}
