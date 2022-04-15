#pragma once

#include "fintamath/core/MathObject.hpp"

#define FINTAMATH_CALL_OPERATOR(OPER)                                                                                  \
  if (rhs.is<Derived>()) {                                                                                             \
    return *this OPER rhs.to<Derived>();                                                                                   \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(*this, rhs); tmp != nullptr) {                                              \
    return *this OPER tmp->template to<Comparable>();                                                                  \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(rhs, *this); tmp != nullptr) {                                              \
    return tmp->template to<Comparable>() OPER rhs;                                                                    \
  }                                                                                                                    \
  throw std::invalid_argument("Incompatible types")

namespace fintamath {
  class Comparable;
  using ComparablePtr = std::unique_ptr<Comparable>;

  class Comparable : virtual public MathObject {
  public:
    ~Comparable() override = default;

    friend bool operator<(const Comparable &lhs, const Comparable &rhs);

    friend bool operator>(const Comparable &lhs, const Comparable &rhs);

    friend bool operator<=(const Comparable &lhs, const Comparable &rhs);

    friend bool operator>=(const Comparable &lhs, const Comparable &rhs);

  protected:
    virtual bool lessAbstract(const Comparable &rhs) const = 0;

    virtual bool moreAbstract(const Comparable &rhs) const = 0;
  };

  inline bool operator<(const Comparable &lhs, const Comparable &rhs) {
    return lhs.lessAbstract(rhs);
  }

  inline bool operator>(const Comparable &lhs, const Comparable &rhs) {
    return lhs.moreAbstract(rhs);
  }

  inline bool operator<=(const Comparable &lhs, const Comparable &rhs) {
    return !lhs.moreAbstract(rhs);
  }

  inline bool operator>=(const Comparable &lhs, const Comparable &rhs) {
    return !lhs.lessAbstract(rhs);
  }

  template <typename Derived>
  class ComparableImpl : virtual public Comparable, virtual public MathObjectImpl<Derived> {
  public:
    ~ComparableImpl() override = default;

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

    bool lessAbstract(const Comparable &rhs) const final {
      FINTAMATH_CALL_OPERATOR(<);
    }

    bool moreAbstract(const Comparable &rhs) const final {
      FINTAMATH_CALL_OPERATOR(>);
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return lhs < LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) < rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return lhs > LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) > rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return lhs <= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) <= rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return lhs >= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) >= rhs;
  }
}

#undef FINTAMATH_CALL_OPERATOR
