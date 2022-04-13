#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Comparable : virtual public MathObject {
  public:
    ~Comparable() override = default;

    bool operator<(const Comparable &rhs) const {
      return less(rhs);
    }

    bool operator>(const Comparable &rhs) const {
      return more(rhs);
    }

    bool operator<=(const Comparable &rhs) const {
      return !more(rhs);
    }

    bool operator>=(const Comparable &rhs) const {
      return !less(rhs);
    }

  protected:
    virtual bool less(const Comparable &rhs) const = 0;

    virtual bool more(const Comparable &rhs) const = 0;
  };

  template <typename Derived>
  class ComparableImpl : virtual public Comparable, virtual public MathObjectImpl<Derived> {
  public:
    ~ComparableImpl() override = default;

  protected:
    virtual bool less(const Derived &rhs) const = 0;

    virtual bool more(const Derived &rhs) const = 0;

    bool less(const Comparable &rhs) const final {
      if (rhs.is<Derived>()) {
        return less(rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this < tmp->template to<Comparable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Comparable>() < rhs;
      }
      throw std::invalid_argument("Cannot be compared");
    }

    bool more(const Comparable &rhs) const final {
      if (rhs.is<Derived>()) {
        return more(rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this > tmp->template to<Comparable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Comparable>() > rhs;
      }
      throw std::invalid_argument("Cannot be compared");
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return lhs < LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) < rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return lhs > LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) > rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return lhs <= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) <= rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return lhs >= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<ComparableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) >= rhs;
  }
}
