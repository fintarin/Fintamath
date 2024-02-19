#pragma once

#include <compare>
#include <cstddef>
#include <limits>
#include <string_view>

#include "fintamath/config/Config.hpp"

namespace fintamath {

struct MathObjectType final {
  enum class Id : size_t {
    IMathObject = 0,

    IArithmetic = 1000,

    IExpression = 2000,

    Expression,
    FunctionExpression,

    IUnaryExpression = 3000,

    NotExpression,
    TrigExpression,
    InvTrigExpression,
    HyperbExpression,
    InvHyperbExpression,
    FloorCeilExpression,
    AbsExpression,
    SignExpression,

    IBinaryExpression = 4000,

    PowExpression,
    DivExpression,
    LogExpression,
    CompExpression,
    DerivativeExpression,
    IntegralExpression,

    IPolynomExpression = 5000,

    AddExpression,
    MulExpression,
    AndExpression,
    OrExpression,
    MinMaxExpression,

    IComparable = 6000,

    INumber = 7000,

    Rational,
    Real,
    Complex,

    IInteger = 8000,

    Integer,

    ILiteral = 9000,

    Boolean,
    Variable,

    IConstant = 10000,

    E,
    Pi,
    True,
    False,
    Inf,
    NegInf,
    ComplexInf,
    Undefined,
    I,

    IFunction = 11000,

    Abs,
    Log,
    Ln,
    Lb,
    Lg,
    Exp,
    Sqr,
    Sqrt,
    Root,
    Sin,
    Cos,
    Tan,
    Cot,
    Sec,
    Csc,
    Asin,
    Acos,
    Atan,
    Acot,
    Asec,
    Acsc,
    Sign,
    Sinh,
    Cosh,
    Tanh,
    Coth,
    Sech,
    Csch,
    Asinh,
    Acosh,
    Atanh,
    Acoth,
    Asech,
    Acsch,
    Min,
    Max,
    Derivative,
    Integral,
    Frac,
    FracMixed,
    PowFunction,
    Floor,
    Ceil,

    IOperator = 12000,

    Add,
    Sub,
    Mul,
    Div,
    Neg,
    UnaryPlus,
    Factorial,
    Percent,
    Pow,
    Eqv,
    Neqv,
    Less,
    More,
    LessEqv,
    MoreEqv,
    Not,
    And,
    Or,
    Impl,
    Equiv,
    Nequiv,
    Index,
    Deg,
    Comma,
    Mod,

    None = std::numeric_limits<size_t>::max(),
  };

  using enum Id;

public:
  consteval MathObjectType(const size_t inId, const std::string_view inName)
      : name(inName),
        id(inId) {
  }

  consteval MathObjectType(const Id inId, const std::string_view inName)
      : MathObjectType(static_cast<size_t>(inId), inName) {
  }

  constexpr bool operator==(const MathObjectType &rhs) const {
    return id == rhs.id && name == rhs.name;
  }

  constexpr std::strong_ordering operator<=>(const MathObjectType &rhs) const {
    return id <=> rhs.id;
  }

  constexpr size_t getId() const {
    return id;
  }

  constexpr std::string_view getName() const {
    return name;
  }

private:
  std::string_view name;
  size_t id;

private:
  [[maybe_unused]] inline static const detail::Config config;
};

constexpr size_t hash_value(const MathObjectType &rhs) noexcept {
  return rhs.getId();
}

}
