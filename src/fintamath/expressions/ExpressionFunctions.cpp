#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/functions/ntheory/Mod.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

using namespace detail;

Expression operator+(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Add{}, lhs, rhs));
}

Expression operator+(const Expression &rhs) {
  return rhs;
}

Expression operator-(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Sub{}, lhs, rhs));
}

Expression operator-(const Expression &rhs) {
  return Expression(makeExprWithValidation(Neg{}, rhs));
}

Expression operator*(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Mul{}, lhs, rhs));
}

Expression operator/(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Div{}, lhs, rhs));
}

Expression mod(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Mod{}, lhs, rhs));
}

Expression eqv(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Eqv{}, lhs, rhs));
}

Expression neqv(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Neqv{}, lhs, rhs));
}

Expression less(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Less{}, lhs, rhs));
}

Expression more(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(More{}, lhs, rhs));
}

Expression lessEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(LessEqv{}, lhs, rhs));
}

Expression moreEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(MoreEqv{}, lhs, rhs));
}

Expression floor(const Expression &rhs) {
  return Expression(makeExprWithValidation(Floor{}, rhs));
}

Expression ceil(const Expression &rhs) {
  return Expression(makeExprWithValidation(Ceil{}, rhs));
}

Expression abs(const Expression &rhs) {
  return Expression(makeExprWithValidation(Abs{}, rhs));
}

Expression factorial(const Expression &rhs) {
  return Expression(makeExprWithValidation(Factorial{}, rhs));
}

Expression sqrt(const Expression &rhs) {
  return Expression(makeExprWithValidation(Sqrt{}, rhs));
}

Expression pow(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Pow{}, lhs, rhs));
}

Expression exp(const Expression &rhs) {
  return Expression(makeExprWithValidation(Exp{}, rhs));
}

Expression log(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Log{}, lhs, rhs));
}

Expression ln(const Expression &rhs) {
  return Expression(makeExprWithValidation(Ln{}, rhs));
}

Expression lb(const Expression &rhs) {
  return Expression(makeExprWithValidation(Lb{}, rhs));
}

Expression lg(const Expression &rhs) {
  return Expression(makeExprWithValidation(Lg{}, rhs));
}

Expression sin(const Expression &rhs) {
  return Expression(makeExprWithValidation(Sin{}, rhs));
}

Expression cos(const Expression &rhs) {
  return Expression(makeExprWithValidation(Cos{}, rhs));
}

Expression tan(const Expression &rhs) {
  return Expression(makeExprWithValidation(Tan{}, rhs));
}

Expression cot(const Expression &rhs) {
  return Expression(makeExprWithValidation(Cot{}, rhs));
}

Expression asin(const Expression &rhs) {
  return Expression(makeExprWithValidation(Asin{}, rhs));
}

Expression acos(const Expression &rhs) {
  return Expression(makeExprWithValidation(Acos{}, rhs));
}

Expression atan(const Expression &rhs) {
  return Expression(makeExprWithValidation(Atan{}, rhs));
}

Expression acot(const Expression &rhs) {
  return Expression(makeExprWithValidation(Acot{}, rhs));
}

Expression sinh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Sinh{}, rhs));
}

Expression cosh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Cosh{}, rhs));
}

Expression tanh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Tanh{}, rhs));
}

Expression coth(const Expression &rhs) {
  return Expression(makeExprWithValidation(Coth{}, rhs));
}

Expression asinh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Asinh{}, rhs));
}

Expression acosh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Acosh{}, rhs));
}

Expression atanh(const Expression &rhs) {
  return Expression(makeExprWithValidation(Atanh{}, rhs));
}

Expression acoth(const Expression &rhs) {
  return Expression(makeExprWithValidation(Acoth{}, rhs));
}

Expression derivative(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Derivative{}, lhs, rhs));
}

Expression notL(const Expression &rhs) {
  return Expression(makeExprWithValidation(Not{}, rhs));
}

Expression andL(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(And{}, lhs, rhs));
}

Expression orL(const Expression &lhs, const Expression &rhs) {
  return Expression(makeExprWithValidation(Or{}, lhs, rhs));
}

Expression e() {
  return E{};
}

Expression pi() {
  return Pi{};
}

Expression inf() {
  return Inf{};
}

Expression negInf() {
  return NegInf{};
}

Expression complexInf() {
  return ComplexInf{};
}

}
