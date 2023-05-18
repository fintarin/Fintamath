#pragma once

#include <cstddef>
#include <limits>
#include <unordered_map>

namespace fintamath {

using MathObjectTypeId = size_t;

enum class MathObjectType : MathObjectTypeId {
  IMathObject = 0,

  IArithmetic = 1000,

  IExpression = 2000,

  Expression,

  IUnaryExpression = 3000,

  NegExpression,
  NotExpression,
  TrigonometryExpression,
  HyperbolicExpression,

  IBinaryExpression = 4000,

  PowExpression,
  DivExpression,
  LogExpression,
  CompExpression,
  DerivativeExpression,
  IntegralExpression,

  IPolynomExpression = 5000,

  SumExpression,
  MulExpression,
  AndExpression,
  OrExpression,
  MinMaxExpression,

  IComparable = 6000,

  INumber = 7000,

  Rational,
  Real,

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

  IFunction = 11000,

  Abs,
  Log,
  Ln,
  Lb,
  Lg,
  Exp,
  Sqrt,
  Sin,
  Cos,
  Tan,
  Cot,
  Asin,
  Acos,
  Atan,
  Acot,
  Degrees,
  Rad,
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
  Angle,

  None = std::numeric_limits<size_t>::max(),
};

inline const std::unordered_map<MathObjectTypeId, MathObjectTypeId> &getBoundTypeIds() {
  using Id = MathObjectTypeId;
  using Type = MathObjectType;

  static const std::unordered_map<Id, Id> ids{
      {Id(Type::IMathObject), Id(Type::None)},                     //
      {Id(Type::IArithmetic), Id(Type::ILiteral)},                 //
      {Id(Type::IExpression), Id(Type::IComparable)},              //
      {Id(Type::IUnaryExpression), Id(Type::IBinaryExpression)},   //
      {Id(Type::IBinaryExpression), Id(Type::IPolynomExpression)}, //
      {Id(Type::IPolynomExpression), Id(Type::IComparable)},       //
      {Id(Type::IComparable), Id(Type::ILiteral)},                 //
      {Id(Type::INumber), Id(Type::ILiteral)},                     //
      {Id(Type::IInteger), Id(Type::ILiteral)},                    //
      {Id(Type::ILiteral), Id(Type::IFunction)},                   //
      {Id(Type::IConstant), Id(Type::IFunction)},                  //
      {Id(Type::IFunction), Id(Type::None)},                       //
      {Id(Type::IOperator), Id(Type::None)},                       //
  };

  return ids;
}

inline bool isBaseOf(size_t toTypeId, size_t fromTypeId) {
  if (auto toTypeBoundaries = getBoundTypeIds().find(toTypeId); toTypeBoundaries != getBoundTypeIds().end()) {
    return fromTypeId >= toTypeBoundaries->first && fromTypeId < toTypeBoundaries->second;
  }

  return toTypeId == fromTypeId;
}

}
