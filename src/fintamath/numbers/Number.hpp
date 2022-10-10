#pragma once

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"

namespace fintamath {
  class Number;
  using NumberPtr = std::unique_ptr<Number>;

  class Number : virtual public Comparable, virtual public Arithmetic, virtual public Incremental {
  public:
    ~Number() override = default;

    static NumberPtr parse(const std::string &str);

    static NumberPtr parse(int64_t num);
  };

  inline NumberPtr operator+(const Number &lhs, const Number &rhs) {
    auto res = lhs + rhs.to<Arithmetic>();
    return meta::castPtr<Number>(res);
  }

  inline NumberPtr operator-(const Number &lhs, const Number &rhs) {
    auto res = lhs - rhs.to<Arithmetic>();
    return meta::castPtr<Number>(res);
  }

  inline NumberPtr operator*(const Number &lhs, const Number &rhs) {
    auto res = lhs * rhs.to<Arithmetic>();
    return meta::castPtr<Number>(res);
  }

  inline NumberPtr operator/(const Number &lhs, const Number &rhs) {
    auto res = lhs / rhs.to<Arithmetic>();
    return meta::castPtr<Number>(res);
  }

  template <typename Derived>
  class NumberCRTP : public Number,
                     public ComparableCRTP<Derived>,
                     public ArithmeticCRTP<Derived>,
                     public IncrementalCRTP<Derived> {
  public:
    ~NumberCRTP() override = default;
  };
}
