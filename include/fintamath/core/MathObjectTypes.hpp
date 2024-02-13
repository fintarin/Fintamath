#pragma once

#include <compare>
#include <cstddef>
#include <limits>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

#include "fintamath/config/Config.hpp"

namespace fintamath {

class MathObjectType final {
public:
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
  constexpr MathObjectType(Id rhs) : id(static_cast<size_t>(rhs)) {
  }

  constexpr MathObjectType(const size_t rhs) : id(rhs) {
  }

  constexpr bool operator==(const MathObjectType &rhs) const = default;

  constexpr bool operator==(Id rhs) const {
    return id == static_cast<size_t>(rhs);
  }

  constexpr bool operator==(const size_t rhs) const {
    return id == rhs;
  }

  constexpr std::strong_ordering operator<=>(const MathObjectType &rhs) const = default;

  constexpr std::strong_ordering operator<=>(Id rhs) const {
    return id <=> static_cast<size_t>(rhs);
  }

  constexpr std::strong_ordering operator<=>(const size_t rhs) const {
    return id <=> rhs;
  }

  constexpr operator size_t() const {
    return id;
  }

private:
  size_t id;

private:
  [[maybe_unused]] inline static const detail::Config config;
};

inline size_t hash_value(const MathObjectType &rhs) noexcept {
  return boost::hash<size_t>{}(rhs);
}

namespace detail {

class MathObjectBoundTypes final {
  using enum MathObjectType::Id;

  using TypeToTypeMap = std::unordered_map<MathObjectType, MathObjectType, boost::hash<MathObjectType>>;

  static TypeToTypeMap &getMutable() {
    static TypeToTypeMap ids{
        {IMathObject, None},
        {IArithmetic, ILiteral},
        {IExpression, IComparable},
        {IUnaryExpression, IBinaryExpression},
        {IBinaryExpression, IPolynomExpression},
        {IPolynomExpression, IComparable},
        {IComparable, ILiteral},
        {INumber, ILiteral},
        {IInteger, ILiteral},
        {ILiteral, IFunction},
        {IConstant, IFunction},
        {IFunction, None},
        {IOperator, None},
    };

    return ids;
  }

public:
  static const TypeToTypeMap &get() {
    return getMutable();
  }

  static void reg(const MathObjectType &type, const MathObjectType &boundType) {
    getMutable().emplace(type, boundType);
  }
};

}

inline bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType) {
  const auto &typeToTypeMap = detail::MathObjectBoundTypes::get();

  if (const auto toTypeBoundaries = typeToTypeMap.find(toType); toTypeBoundaries != typeToTypeMap.end()) {
    return fromType >= toTypeBoundaries->first && fromType < toTypeBoundaries->second;
  }

  return toType == fromType;
}

}
