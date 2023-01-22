#pragma once

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "fintamath/multimethod/Converter.hpp"

namespace fintamath {

class IMathObject;
using MathObjectPtr = std::unique_ptr<IMathObject>;

class IMathObject {
public:
  virtual ~IMathObject() = default;

  virtual MathObjectPtr clone() const = 0;

  virtual std::string toString() const {
    return {};
  }

  template <typename T>
  bool instanceOf() const {
    return dynamic_cast<const T *>(this);
  }

  template <typename T>
  const T &to() const {
    return dynamic_cast<const T &>(*this);
  }

  template <typename T>
  T &to() {
    return dynamic_cast<T &>(*this);
  }

  virtual MathObjectPtr simplify() const {
    return clone();
  }

  friend bool operator==(const IMathObject &lhs, const IMathObject &rhs) {
    return lhs.equalsAbstract(rhs);
  }

  friend bool operator!=(const IMathObject &lhs, const IMathObject &rhs) {
    return !lhs.equalsAbstract(rhs);
  }

protected:
  virtual bool equalsAbstract(const IMathObject &rhs) const = 0;
};

template <typename Derived>
class IMathObjectCRTP : virtual public IMathObject {
public:
  MathObjectPtr clone() const final {
    return std::make_unique<Derived>(to<Derived>());
  }

  bool operator==(const Derived &rhs) const {
    return equals(rhs);
  }

  bool operator!=(const Derived &rhs) const {
    return !equals(rhs);
  }

protected:
  virtual bool equals(const Derived &rhs) const {
    return toString() == rhs.toString();
  }

  bool equalsAbstract(const IMathObject &rhs) const final {
    if (rhs.instanceOf<Derived>()) {
      return equals(rhs.to<Derived>());
    }
    if (MathObjectPtr tmpRhs = Converter::convert(rhs, *this); tmpRhs != nullptr) {
      return equals(tmpRhs->template to<Derived>());
    }
    if (MathObjectPtr tmpLhs = Converter::convert(*this, rhs); tmpLhs != nullptr) {
      return *tmpLhs == rhs;
    }
    return false;
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator==(const LhsType &lhs, const RhsType &rhs) {
  return lhs == LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator==(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) == rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator!=(const LhsType &lhs, const RhsType &rhs) {
  return lhs != LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator!=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) != rhs;
}

inline std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
