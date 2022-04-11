#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename Derived>
  class Summable : virtual public MathObjectImpl<Derived> {
  public:
    ~Summable() override = default;

    Derived &operator+=(const Derived &rhs) {
      return add(rhs);
    }

    Derived &operator-=(const Derived &rhs) {
      return sub(rhs);
    }

    Derived operator+(const Derived &rhs) const {
      std::unique_ptr<Summable<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->add(rhs);
    }

    Derived operator-(const Derived &rhs) const {
      std::unique_ptr<Summable<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->sub(rhs);
    }

    Derived operator+() const {
      return Derived(this->template to<Derived>());
    }

    Derived operator-() const {
      std::unique_ptr<Summable<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->neg();
    }

  protected:
    virtual Derived &add(const Derived &rhs) = 0;

    virtual Derived &sub(const Derived &rhs) = 0;

    virtual Derived &neg() = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
    return lhs += LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
    return lhs -= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return lhs + LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) + rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return lhs - LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) - rhs;
  }
}
