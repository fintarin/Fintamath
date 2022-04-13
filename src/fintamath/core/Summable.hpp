#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Summable : virtual public MathObject {
  public:
    ~Summable() override = default;

    virtual std::unique_ptr<Summable> operator+(const Summable &rhs) const = 0;

    virtual std::unique_ptr<Summable> operator-(const Summable &rhs) const = 0;
  };

  template <typename Derived>
  class SummableImpl : virtual public Summable, virtual public MathObjectImpl<Derived> {
  public:
    ~SummableImpl() override = default;

    std::unique_ptr<Summable> operator+(const Summable &rhs) const final {
      if (rhs.is<Derived>()) {
        auto res = std::make_unique<Derived>(to<Derived>());
        *res += rhs.to<Derived>();
        return res;
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this + tmp->template to<Summable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Summable>() + rhs;
      }
      throw std::invalid_argument("Cannot be summarized");
    }

    std::unique_ptr<Summable> operator-(const Summable &rhs) const final {
      if (rhs.is<Derived>()) {
        auto res = std::make_unique<Derived>(to<Derived>());
        *res -= rhs.to<Derived>();
        return res;
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this - tmp->template to<Summable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Summable>() - rhs;
      }
      return {};
    }

    Derived &operator+=(const Derived &rhs) {
      return add(rhs);
    }

    Derived &operator-=(const Derived &rhs) {
      return substract(rhs);
    }

    Derived operator+(const Derived &rhs) const {
      return Derived(to<Derived>()) += rhs;
    }

    Derived operator-(const Derived &rhs) const {
      return Derived(to<Derived>()) -= rhs;
    }

    Derived operator+() const {
      return Derived(to<Derived>());
    }

    Derived operator-() const {
      return 0 - to<Derived>();
    }

  protected:
    virtual Derived &add(const Derived &rhs) = 0;

    virtual Derived &substract(const Derived &rhs) = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
    return lhs += LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
    return lhs -= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return lhs + LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) + rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return lhs - LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) - rhs;
  }
}
