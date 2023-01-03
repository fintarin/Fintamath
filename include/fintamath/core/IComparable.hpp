#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"

namespace fintamath {

class IComparable;
using ComparablePtr = std::unique_ptr<IComparable>;

class IComparable : virtual public IMathObject {
public:
  friend bool operator<(const IComparable &lhs, const IComparable &rhs);

  friend bool operator>(const IComparable &lhs, const IComparable &rhs);

  friend bool operator<=(const IComparable &lhs, const IComparable &rhs);

  friend bool operator>=(const IComparable &lhs, const IComparable &rhs);

protected:
  virtual bool lessAbstract(const IComparable &rhs) const = 0;

  virtual bool moreAbstract(const IComparable &rhs) const = 0;
};

inline bool operator<(const IComparable &lhs, const IComparable &rhs) {
  return lhs.lessAbstract(rhs);
}

inline bool operator>(const IComparable &lhs, const IComparable &rhs) {
  return lhs.moreAbstract(rhs);
}

inline bool operator<=(const IComparable &lhs, const IComparable &rhs) {
  return !lhs.moreAbstract(rhs);
}

inline bool operator>=(const IComparable &lhs, const IComparable &rhs) {
  return !lhs.lessAbstract(rhs);
}

template <typename Derived>
class IComparableCRTP : virtual public IComparable, virtual public IMathObjectCRTP<Derived> {
public:
  bool operator<(const Derived &rhs) const {
    return less(rhs);
  }

  bool operator>(const Derived &rhs) const {
    return more(rhs);
  }

  bool operator<=(const Derived &rhs) const {
    return !more(rhs);
  }

  bool operator>=(const Derived &rhs) const {
    return !less(rhs);
  }

protected:
  virtual bool less(const Derived &rhs) const = 0;

  virtual bool more(const Derived &rhs) const = 0;

  bool lessAbstract(const IComparable &rhs) const final {
    return executeAbstract(
        rhs, "<", [this](const IComparableCRTP<Derived> &lhs, const Derived &rhs) { return lhs.less(rhs); },
        [](const IComparable &lhs, const IComparable &rhs) { return lhs < rhs; });
  }

  bool moreAbstract(const IComparable &rhs) const final {
    return executeAbstract(
        rhs, ">", [this](const IComparableCRTP<Derived> &lhs, const Derived &rhs) { return lhs.more(rhs); },
        [](const IComparable &lhs, const IComparable &rhs) { return lhs > rhs; });
  }

private:
  bool executeAbstract(const IComparable &rhs, const std::string &oper,
                       std::function<bool(const IComparableCRTP<Derived> &lhs, const Derived &rhs)> &&f1,
                       std::function<bool(const IComparable &, const IComparable &)> &&f2) const {
    if (rhs.is<Derived>()) {
      return f1(*this, rhs.to<Derived>());
    }
    if (MathObjectPtr tmpRhs = Converter::convert(rhs, *this); tmpRhs != nullptr) {
      return f1(*this, tmpRhs->template to<Derived>());
    }
    if (MathObjectPtr tmpLhs = Converter::convert(*this, rhs); tmpLhs != nullptr) {
      return f2(tmpLhs->to<IComparable>(), rhs);
    }
    throw InvalidInputBinaryOpearatorException(oper, toString(), rhs.toString());
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<(const LhsType &lhs, const RhsType &rhs) {
  return lhs < LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) < rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>(const LhsType &lhs, const RhsType &rhs) {
  return lhs > LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) > rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<=(const LhsType &lhs, const RhsType &rhs) {
  return lhs <= LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) <= rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>=(const LhsType &lhs, const RhsType &rhs) {
  return lhs >= LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) >= rhs;
}

}
