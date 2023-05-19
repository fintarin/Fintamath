#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/parser/Parser.hpp"

#define REQUIRE_ARITHMETICS(Lhs, Rhs)                                                                                  \
  template <typename Lhs, typename Rhs,                                                                                \
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, Lhs> && std::is_convertible_v<Rhs, Lhs> &&      \
                                        !std::is_same_v<Lhs, Rhs>>>

namespace fintamath {

class IArithmetic : public IMathObject {
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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IArithmetic);
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
class IArithmeticCRTP : public IArithmetic {
#define FINTAMATH_I_ARITHMETIC_CRTP IArithmeticCRTP<Derived>
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef FINTAMATH_I_ARITHMETIC_CRTP
};

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs &operator+=(Lhs &lhs, const Rhs &rhs) {
  return lhs += Lhs(rhs);
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs &operator-=(Lhs &lhs, const Rhs &rhs) {
  return lhs -= Lhs(rhs);
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs &operator*=(Lhs &lhs, const Rhs &rhs) {
  return lhs *= Lhs(rhs);
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs &operator/=(Lhs &lhs, const Rhs &rhs) {
  return lhs /= Lhs(rhs);
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return lhs + Lhs(rhs);
}

REQUIRE_ARITHMETICS(Rhs, Lhs) Rhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) + rhs;
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return lhs - Lhs(rhs);
}

REQUIRE_ARITHMETICS(Rhs, Lhs) Rhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) - rhs;
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return lhs * Lhs(rhs);
}

REQUIRE_ARITHMETICS(Rhs, Lhs) Rhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) * rhs;
}

REQUIRE_ARITHMETICS(Lhs, Rhs) Lhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return lhs / Lhs(rhs);
}

REQUIRE_ARITHMETICS(Rhs, Lhs) Rhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) / rhs;
}

}

#undef REQUIRE_ARITHMETICS
