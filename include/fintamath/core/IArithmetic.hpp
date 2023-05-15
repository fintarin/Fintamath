#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IArithmetic : virtual public IMathObject {
public:
  friend inline std::unique_ptr<IArithmetic> operator+(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::getMultiAdd()(lhs, rhs)) {
      return res;
    }
    return lhs.addAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator-(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::getMultiSub()(lhs, rhs)) {
      return res;
    }
    return lhs.substractAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator*(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::getMultiMul()(lhs, rhs)) {
      return res;
    }
    return lhs.multiplyAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator/(const IArithmetic &lhs, const IArithmetic &rhs) {
    if (auto res = IArithmetic::getMultiDiv()(lhs, rhs)) {
      return res;
    }
    return lhs.divideAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator+(const IArithmetic &rhs) {
    return rhs.unaryPlusAbstract();
  }

  friend inline std::unique_ptr<IArithmetic> operator-(const IArithmetic &rhs) {
    return rhs.negateAbstract();
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiAddFunction(const Func &func) {
    getMultiAdd().add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiSubFunction(const Func &func) {
    getMultiSub().add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiMulFunction(const Func &func) {
    getMultiMul().add<Lhs, Rhs>(func);
  }

  template <typename Lhs, typename Rhs, typename Func>
  static void addMultiDivFunction(const Func &func) {
    getMultiDiv().add<Lhs, Rhs>(func);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IArithmetic, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IArithmetic, T>>>
  static void registerType(Parser::Function<std::unique_ptr<IArithmetic>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<IArithmetic> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

protected:
  virtual std::unique_ptr<IArithmetic> addAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> substractAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> negateAbstract() const = 0;

  virtual std::unique_ptr<IArithmetic> unaryPlusAbstract() const = 0;

private:
  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &getMultiAdd();

  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &getMultiSub();

  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &getMultiMul();

  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &getMultiDiv();

  static Parser::Vector<std::unique_ptr<IArithmetic>, const std::string &> &getParser();
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

  std::unique_ptr<IArithmetic> addAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "+",
        [](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.add(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs + rhs;
        });
  }

  std::unique_ptr<IArithmetic> substractAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "-",
        [](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.substract(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs - rhs;
        });
  }

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "*",
        [](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.multiply(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs * rhs;
        });
  }

  std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "/",
        [](IArithmeticCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.divide(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs / rhs;
        });
  }

  std::unique_ptr<IArithmetic> negateAbstract() const final {
    return std::make_unique<Derived>(-(*this));
  }

  std::unique_ptr<IArithmetic> unaryPlusAbstract() const final {
    return std::make_unique<Derived>(+(*this));
  }

private:
  template <typename FunctionCommonTypes, typename FunctionDifferentTypes>
  std::unique_ptr<IArithmetic> executeAbstract(const IArithmetic &rhs, const std::string &oper,
                                               FunctionCommonTypes &&funcCommonTypes,
                                               FunctionDifferentTypes &&funcDifferentTypes) const {

    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IArithmeticCRTP<Derived>>(clone());
      return cast<IArithmetic>(funcCommonTypes(*lhsPtr, *rhpPtr).toMinimalObject());
    }

    if constexpr (IsConvertible<Derived>::value) {
      if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
        auto lhsPtr = cast<IArithmeticCRTP<Derived>>(clone());
        return cast<IArithmetic>(funcCommonTypes(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
      }

      if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
        return cast<IArithmetic>(funcDifferentTypes(cast<IArithmetic>(*lhsPtr), rhs)->toMinimalObject());
      }
    }

    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
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
