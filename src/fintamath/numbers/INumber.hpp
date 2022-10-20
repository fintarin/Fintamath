#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IIncremental.hpp"

namespace fintamath {
  class INumber;
  using NumberPtr = std::unique_ptr<INumber>;

  class INumber : virtual public IComparable, virtual public IArithmetic, virtual public IIncremental {
  public:
    ~INumber() override = default;

    static NumberPtr parse(const std::string &str);

    static NumberPtr parse(int64_t num);
  };

  inline NumberPtr operator+(const INumber &lhs, const INumber &rhs) {
    auto res = lhs + rhs.to<IArithmetic>();
    return help::castPtr<INumber>(res);
  }

  inline NumberPtr operator-(const INumber &lhs, const INumber &rhs) {
    auto res = lhs - rhs.to<IArithmetic>();
    return help::castPtr<INumber>(res);
  }

  inline NumberPtr operator*(const INumber &lhs, const INumber &rhs) {
    auto res = lhs * rhs.to<IArithmetic>();
    return help::castPtr<INumber>(res);
  }

  inline NumberPtr operator/(const INumber &lhs, const INumber &rhs) {
    auto res = lhs / rhs.to<IArithmetic>();
    return help::castPtr<INumber>(res);
  }

  template <typename Derived>
  class INumberCRTP : public INumber,
                     public ComparableCRTP<Derived>,
                     public IArithmeticCRTP<Derived>,
                     public IIncrementalCRTP<Derived> {
  public:
    ~INumberCRTP() override = default;
  };
}
