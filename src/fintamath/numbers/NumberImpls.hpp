#pragma once

#include <utility>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include "fintamath/core/CoreConstants.hpp"

using namespace boost::multiprecision;

namespace fintamath {

struct RealImpl {
  using Backend = number<cpp_dec_float<FINTAMATH_DEFAULT_PRECISION>>;

  Backend v;

  RealImpl() = default;

  RealImpl(Backend inV) : v(std::move(inV)) {
  }

  operator Backend() const {
    return v;
  }
};

}
