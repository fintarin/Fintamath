#pragma once

#include <utility>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include "fintamath/core/CoreConstants.hpp"

using namespace boost::multiprecision;

namespace fintamath {

struct IntegerImpl {
  using Backend = cpp_int;

  Backend v;

  IntegerImpl() = default;

  IntegerImpl(Backend inV) : v(std::move(inV)) {
  }

  operator Backend() const {
    return v;
  }
};

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
