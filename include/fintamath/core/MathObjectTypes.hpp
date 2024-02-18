#pragma once

#include <compare>
#include <cstddef>
#include <limits>
#include <optional>
#include <string_view>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>
#include <utility>

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
  constexpr MathObjectType(const size_t rhs, const std::string_view inName)
      : name(inName),
        id(rhs) {
  }

  constexpr MathObjectType(const Id inId, const std::string_view inName)
      : MathObjectType(static_cast<size_t>(inId), inName) {
  }

  constexpr bool operator==(const MathObjectType rhs) const {
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

inline size_t hash_value(const MathObjectType &rhs) noexcept {
  return boost::hash<size_t>{}(rhs.getId());
}

bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType);

namespace detail {

class MathObjectBoundTypes final {
  using enum MathObjectType::Id;

  using TypeIdToBoundTypeIdMap = std::unordered_map<size_t, size_t>;

  static TypeIdToBoundTypeIdMap &getMap() {
    static TypeIdToBoundTypeIdMap typeIdToBoundTypeIdMap{
        makeTypeIdPair(IMathObject, None),
        makeTypeIdPair(IArithmetic, ILiteral),
        makeTypeIdPair(IArithmetic, ILiteral),
        makeTypeIdPair(IExpression, IComparable),
        makeTypeIdPair(IUnaryExpression, IBinaryExpression),
        makeTypeIdPair(IBinaryExpression, IPolynomExpression),
        makeTypeIdPair(IPolynomExpression, IComparable),
        makeTypeIdPair(IComparable, ILiteral),
        makeTypeIdPair(INumber, ILiteral),
        makeTypeIdPair(IInteger, ILiteral),
        makeTypeIdPair(ILiteral, IFunction),
        makeTypeIdPair(IConstant, IFunction),
        makeTypeIdPair(IFunction, None),
        makeTypeIdPair(IOperator, None),
    };
    return typeIdToBoundTypeIdMap;
  }

public:
  static void bindTypes(const MathObjectType &type, const MathObjectType &boundType) {
    getMap().emplace(type.getId(), boundType.getId());
  }

  friend bool fintamath::isBaseOf(const MathObjectType &toType, const MathObjectType &fromType);

private:
  static std::pair<size_t, size_t> makeTypeIdPair(const MathObjectType::Id lhs, const MathObjectType::Id rhs) {
    return {static_cast<size_t>(lhs), static_cast<size_t>(rhs)};
  }
};

}

inline bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType) {
  const auto &map = detail::MathObjectBoundTypes::getMap();

  if (const auto boundaries = map.find(toType.getId()); boundaries != map.end()) {
    return fromType.getId() >= boundaries->first && fromType.getId() < boundaries->second;
  }

  return toType == fromType;
}

}
