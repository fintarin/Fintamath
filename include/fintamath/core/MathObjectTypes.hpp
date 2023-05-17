#pragma once

#include <cstdint>
#include <unordered_map>

namespace fintamath {

enum class MathObjectType : uint32_t {
  IMathObject,

  IArithmetic,

  IExpression,

  Expression,

  IUnaryExpression,

  NegExpression,
  NotExpression,
  TrigonometryExpression,
  HyperbolicExpression,

  IBinaryExpression,

  PowExpression,
  DivExpression,
  LogExpression,
  CompExpression,
  DerivativeExpression,
  IntegralExpression,

  IPolynomExpression,

  SumExpression,
  MulExpression,
  AndExpression,
  OrExpression,
  MinMaxExpression,

  IComparable,

  INumber,

  Rational,
  Real,

  IIntegral,

  Integer,

  ILiteral,

  Boolean,
  Variable,

  IConstant,

  E,
  Pi,
  True,
  False,

  IFunction,

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

  IOperator,

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

  None,
};

static const std::unordered_map<MathObjectType, MathObjectType> MATH_OBJECT_TYPES{
    {MathObjectType::IMathObject, MathObjectType::None},                     //
    {MathObjectType::IArithmetic, MathObjectType::ILiteral},                 //
    {MathObjectType::IExpression, MathObjectType::IComparable},              //
    {MathObjectType::IUnaryExpression, MathObjectType::IBinaryExpression},   //
    {MathObjectType::IBinaryExpression, MathObjectType::IPolynomExpression}, //
    {MathObjectType::IPolynomExpression, MathObjectType::IComparable},       //
    {MathObjectType::IComparable, MathObjectType::ILiteral},                 //
    {MathObjectType::INumber, MathObjectType::ILiteral},                     //
    {MathObjectType::IIntegral, MathObjectType::ILiteral},                   //
    {MathObjectType::ILiteral, MathObjectType::IFunction},                   //
    {MathObjectType::IConstant, MathObjectType::IFunction},                  //
    {MathObjectType::IFunction, MathObjectType::None},                       //
    {MathObjectType::IOperator, MathObjectType::None},                       //
};

inline bool is(MathObjectType to, MathObjectType from) {
  if (auto toTypeBoundaries = MATH_OBJECT_TYPES.find(to); toTypeBoundaries != MATH_OBJECT_TYPES.end()) {
    return from >= toTypeBoundaries->first && from < toTypeBoundaries->second;
  }

  return from == to;
}

}
