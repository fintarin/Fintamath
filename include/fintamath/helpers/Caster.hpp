#pragma once

#include <memory>

namespace fintamath::helpers {

template <typename To, typename From>
std::unique_ptr<To> cast(From &&ptr) {
  std::unique_ptr<To> res(dynamic_cast<To *>(ptr.release()));
  return res;
}

}
