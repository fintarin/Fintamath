#pragma once

#include <concepts>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/MathObjectBody.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(IMathObject)

public:
  virtual ~IMathObject() = default;

  virtual std::unique_ptr<IMathObject> clone() const & = 0;

  virtual std::unique_ptr<IMathObject> clone() && = 0;

  virtual std::string toString() const {
    return std::string(getClass().getName());
  }

  virtual std::unique_ptr<IMathObject> toMinimalObject() const {
    return clone();
  }

  virtual MathObjectClass getClass() const = 0;

  friend bool operator==(const IMathObject &lhs, const IMathObject &rhs) {
    return lhs.equalsAbstract(rhs);
  }

protected:
  virtual bool equalsAbstract(const IMathObject &rhs) const = 0;
};

template <typename Derived>
class IMathObjectCRTP : public IMathObject {
#define I_MATH_OBJECT_CRTP IMathObjectCRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP
};

template <std::derived_from<IMathObject> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
bool operator==(const Lhs &lhs, const Rhs &rhs) {
  return lhs == Lhs(rhs);
}

inline std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
