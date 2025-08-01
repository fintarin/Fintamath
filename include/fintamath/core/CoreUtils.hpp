#pragma once

#include <memory>
#include <utility>

namespace fintamath {

template <typename Number, typename Function>
void repeat(const Number &num, Function &&func) {
  for (Number i = 0; i < num; ++i) {
    std::forward<Function>(func)();
  }
}

}
