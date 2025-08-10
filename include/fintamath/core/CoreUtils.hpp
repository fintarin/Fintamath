#pragma once

#include <utility>

namespace fintamath {

template <typename Number, typename Callback>
void repeat(const Number &num, Callback &&callback) {
  for (Number i = 0; i < num; ++i) {
    std::forward<Callback>(callback)();
  }
}

}
