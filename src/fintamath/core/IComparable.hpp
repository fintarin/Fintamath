#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"

#define FINTAMATH_CALL_OPERATOR(OPER)                                                                                  \
  if (rhs.is<Derived>()) {                                                                                             \
    return *this OPER rhs.to<Derived>();                                                                               \
  }                                                                                                                    \
  if (auto tmp = helpers::convertMathObject(rhs, *this); tmp != nullptr) {                                             \
    return *this OPER tmp->template to<IComparable>();                                                                 \
  }                                                                                                                    \
  if (auto tmp = helpers::convertMathObject(*this, rhs); tmp != nullptr) {                                             \
    return tmp->template to<IComparable>() OPER rhs;                                                                   \
  }                                                                                                                    \
  throw FunctionCallException(#OPER, {toString(), rhs.toString()})

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
  class ComparableCRTP : virtual public IComparable, virtual public IMathObjectCRTP<Derived> {
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
      FINTAMATH_CALL_OPERATOR(<);
    }

    bool moreAbstract(const IComparable &rhs) const final {
      FINTAMATH_CALL_OPERATOR(>);
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

#undef FINTAMATH_CALL_OPERATOR
