#pragma once

#include <cstddef>
#include <limits>
#include <unordered_map>

namespace fintamath {

class MathObjectType {
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
    Sqrt,
    Root,
    Sin,
    Cos,
    Tan,
    Cot,
    Asin,
    Acos,
    Atan,
    Acot,
    Sign,
    Sinh,
    Cosh,
    Tanh,
    Coth,
    Asinh,
    Acosh,
    Atanh,
    Acoth,
    Min,
    Max,
    Derivative,
    Integral,
    Frac,
    PowF,

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

    None = std::numeric_limits<size_t>::max(),
  };

  using enum Id;

public:
  MathObjectType(Id rhs) : id(size_t(rhs)) {
  }

  MathObjectType(size_t rhs) : id(rhs) {
  }

  bool operator==(const MathObjectType &rhs) const = default;

  bool operator==(Id rhs) const {
    return id == size_t(rhs);
  }

  bool operator==(size_t rhs) const {
    return id == rhs;
  }

  std::strong_ordering operator<=>(const MathObjectType &rhs) const = default;

  std::strong_ordering operator<=>(Id rhs) const {
    return id <=> size_t(rhs);
  }

  std::strong_ordering operator<=>(size_t rhs) const {
    return id <=> rhs;
  }

  operator size_t() const {
    return id;
  }

private:
  size_t id = size_t(None);
};

}

namespace std {

template <>
struct hash<fintamath::MathObjectType> {
  size_t operator()(const fintamath::MathObjectType &rhs) const {
    return hash<size_t>()(size_t(rhs));
  }
};

}

namespace fintamath {

class MathObjectBoundTypes {
  using enum MathObjectType::Id;

  using TypeMap = std::unordered_map<MathObjectType, MathObjectType>;

  static TypeMap &getMutable() {
    static TypeMap ids{
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
  static const TypeMap &get() {
    return getMutable();
  }

  static void reg(const MathObjectType &type, const MathObjectType &boundType) {
    getMutable().emplace(type, boundType);
  }
};

inline bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType) {
  const auto &ids = MathObjectBoundTypes::get();

  if (auto toTypeBoundaries = ids.find(toType); toTypeBoundaries != ids.end()) {
    return fromType >= toTypeBoundaries->first && fromType < toTypeBoundaries->second;
  }

  return toType == fromType;
}

}
