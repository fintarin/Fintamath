#pragma once

#include <memory>

namespace fintamath {

template <typename To, typename From>
std::unique_ptr<To> castPtr(From &&ptr) {
  std::unique_ptr<To> res(dynamic_cast<To *>(ptr.release()));
  return res;
}

}
