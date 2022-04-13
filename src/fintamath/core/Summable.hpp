#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Summable : virtual public MathObject {
  public:
    ~Summable() override = default;

    friend std::unique_ptr<Summable> operator+(const Summable &lhs, const Summable &rhs);

    friend std::unique_ptr<Summable> operator-(const Summable &lhs, const Summable &rhs);

    friend std::unique_ptr<Summable> operator+(const Summable &rhs);

    friend std::unique_ptr<Summable> operator-(const Summable &rhs);

  protected:
    virtual std::unique_ptr<Summable> addAbstract(const Summable &rhs) const = 0;

    virtual std::unique_ptr<Summable> substractAbstract(const Summable &rhs) const = 0;

    virtual std::unique_ptr<Summable> convertAbstract() const = 0;

    virtual std::unique_ptr<Summable> negateAbstract() const = 0;
  };

  inline std::unique_ptr<Summable> operator+(const Summable &lhs, const Summable &rhs) {
    return lhs.addAbstract(rhs);
  }

  inline std::unique_ptr<Summable> operator-(const Summable &lhs, const Summable &rhs) {
    return lhs.substractAbstract(rhs);
  }

  inline std::unique_ptr<Summable> operator+(const Summable &rhs) {
    return rhs.convertAbstract();
  }

  inline std::unique_ptr<Summable> operator-(const Summable &rhs) {
    return rhs.negateAbstract();
  }

  template <typename Derived>
  class SummableImpl : virtual public Summable, virtual public MathObjectImpl<Derived> {
  public:
    ~SummableImpl() override = default;

    Derived &operator+=(const Derived &rhs) {
      return add(rhs);
    }

    Derived &operator-=(const Derived &rhs) {
      return substract(rhs);
    }

    Derived operator+(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) += rhs;
    }

    Derived operator-(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) -= rhs;
    }

    Derived operator+() const {
      return Derived(static_cast<const Derived &>(*this));
    }

    Derived operator-() const {
      Derived tmp = Derived(static_cast<const Derived &>(*this));
      return static_cast<SummableImpl<Derived> &>(tmp).negate();
    }

  protected:
    virtual Derived &add(const Derived &rhs) = 0;

    virtual Derived &substract(const Derived &rhs) = 0;

    virtual Derived &negate() = 0;

    std::unique_ptr<Summable> addAbstract(const Summable &rhs) const final {
      if (rhs.is<Derived>()) {
        return std::make_unique<Derived>(*this + rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this + tmp->template to<Summable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Summable>() + rhs;
      }
      throw std::invalid_argument("Cannot be summarized");
    }

    std::unique_ptr<Summable> substractAbstract(const Summable &rhs) const final {
      if (rhs.is<Derived>()) {
        return std::make_unique<Derived>(*this - rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this - tmp->template to<Summable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Summable>() - rhs;
      }
      throw std::invalid_argument("Cannot be substacted");
    }

    std::unique_ptr<Summable> convertAbstract() const final {
      return std::make_unique<Derived>(+(*this));
    }

    std::unique_ptr<Summable> negateAbstract() const final {
      return std::make_unique<Derived>(-(*this));
    }
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
