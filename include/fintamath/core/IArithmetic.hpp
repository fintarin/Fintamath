#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IArithmetic;
using ArithmeticPtr = std::unique_ptr<IArithmetic>;

class IArithmetic : virtual public IMathObject {
public:
  friend inline ArithmeticPtr operator+(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::multiAdd(lhs, rhs)) {
      return res;
    }
    return lhs.addAbstract(rhs);
  }

  friend inline ArithmeticPtr operator-(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::multiSub(lhs, rhs)) {
      return res;
    }
    return lhs.substractAbstract(rhs);
  }

  friend inline ArithmeticPtr operator*(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::multiMul(lhs, rhs)) {
      return res;
    }
    return lhs.multiplyAbstract(rhs);
  }

  friend inline ArithmeticPtr operator/(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::multiDiv(lhs, rhs)) {
      return res;
    }
    return lhs.divideAbstract(rhs);
  }

  friend inline ArithmeticPtr operator+(const IArithmetic &rhs) {
    return rhs.convertAbstract();
  }

  friend inline ArithmeticPtr operator-(const IArithmetic &rhs) {
    return rhs.negateAbstract();
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiAddFunction(const Func &func) {
    multiAdd.add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiSubFunction(const Func &func) {
    multiSub.add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiMulFunction(const Func &func) {
    multiMul.add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiDivFunction(const Func &func) {
    multiDiv.add<Lhs, Rhs>(func);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IArithmetic, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IArithmetic, T>>>
  static void registerType(Parser::Function<ArithmeticPtr, const std::string &> &&parserFunc) {
    Parser::registerType<T>(parserVector, parserFunc);
  }

  static ArithmeticPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual ArithmeticPtr addAbstract(const IArithmetic &rhs) const = 0;

  virtual ArithmeticPtr substractAbstract(const IArithmetic &rhs) const = 0;

  virtual ArithmeticPtr multiplyAbstract(const IArithmetic &rhs) const = 0;

  virtual ArithmeticPtr divideAbstract(const IArithmetic &rhs) const = 0;

  virtual ArithmeticPtr convertAbstract() const = 0;

  virtual ArithmeticPtr negateAbstract() const = 0;

private:
  static MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> multiAdd;

  static MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> multiSub;

  static MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> multiMul;

  static MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> multiDiv;

  static Parser::Vector<ArithmeticPtr, const std::string &> parserVector;
};

template <typename Derived>
class IArithmeticCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IArithmetic {
public:
  Derived &operator+=(const Derived &rhs) {
    return add(rhs);
  }

  Derived &operator-=(const Derived &rhs) {
    return substract(rhs);
  }

  Derived &operator*=(const Derived &rhs) {
    return multiply(rhs);
  }

  Derived &operator/=(const Derived &rhs) {
    return divide(rhs);
  }

  Derived operator+(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) += rhs;
  }

  Derived operator-(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) -= rhs;
  }

  Derived operator*(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) *= rhs;
  }

  Derived operator/(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) /= rhs;
  }

  Derived operator+() const {
    return Derived(cast<Derived>(*this));
  }

  Derived operator-() const {
    Derived tmp = Derived(cast<Derived>(*this));
    return static_cast<IArithmeticCRTP<Derived> &>(tmp).negate();
  }

protected:
  virtual Derived &add(const Derived &rhs) = 0;

  virtual Derived &substract(const Derived &rhs) = 0;

  virtual Derived &multiply(const Derived &rhs) = 0;

  virtual Derived &divide(const Derived &rhs) = 0;

  virtual Derived &negate() = 0;

  ArithmeticPtr addAbstract(const IArithmetic &rhs) const final {
    return executeAbstract(
        rhs, "+",
        [this](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.add(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs + rhs;
        });
  }

  ArithmeticPtr substractAbstract(const IArithmetic &rhs) const final {
    return executeAbstract(
        rhs, "-",
        [this](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.substract(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs - rhs;
        });
  }

  ArithmeticPtr multiplyAbstract(const IArithmetic &rhs) const final {
    return executeAbstract(
        rhs, "*",
        [this](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.multiply(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs * rhs;
        });
  }

  ArithmeticPtr divideAbstract(const IArithmetic &rhs) const final {
    return executeAbstract(
        rhs, "/",
        [this](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.divide(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs / rhs;
        });
  }

  ArithmeticPtr convertAbstract() const final {
    return std::make_unique<Derived>(+(*this));
  }

  ArithmeticPtr negateAbstract() const final {
    return std::make_unique<Derived>(-(*this));
  }

private:
  ArithmeticPtr executeAbstract(const IArithmetic &rhs, const std::string &oper,
                                std::function<Derived(IArithmeticCRTP<Derived> &lhs, const Derived &rhs)> &&f1,
                                std::function<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> &&f2) const {
    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IArithmeticCRTP<Derived>>(clone());
      return cast<IArithmetic>(f1(*lhsPtr, *rhpPtr).toMinimalObject());
    }
    if (MathObjectPtr rhsPtr = convert(rhs, *this)) {
      auto lhsPtr = cast<IArithmeticCRTP<Derived>>(clone());
      return cast<IArithmetic>(f1(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
    }
    if (MathObjectPtr lhsPtr = convert(*this, rhs)) {
      return cast<IArithmetic>(f2(cast<IArithmetic>(*lhsPtr), rhs)->toMinimalObject());
    }
    throw InvalidInputBinaryOpearatorException(oper, toString(), rhs.toString());
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
  return lhs += LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
  return lhs -= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
  return lhs *= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
  return lhs /= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
  return lhs + LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) + rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
  return lhs - LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) - rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
  return lhs * LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) * rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
  return lhs / LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) / rhs;
}

}
