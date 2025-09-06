#pragma once

namespace fintamath::detail {

template <typename... Args>
struct Overload : Args... {
  using Args::operator()...;
};

template <typename... Args>
Overload(Args...) -> Overload<Args...>;

}
