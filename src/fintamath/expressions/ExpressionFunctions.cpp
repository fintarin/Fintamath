#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
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
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

Expression eqv(const Expression &lhs, const Expression &rhs) {
  return Expression(Eqv()(lhs, rhs));
}

Expression neqv(const Expression &lhs, const Expression &rhs) {
  return Expression(Neqv()(lhs, rhs));
}

Expression less(const Expression &lhs, const Expression &rhs) {
  return Expression(Less()(lhs, rhs));
}

Expression move(const Expression &lhs, const Expression &rhs) {
  return Expression(More()(lhs, rhs));
}

Expression lessEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(LessEqv()(lhs, rhs));
}

Expression moveEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(MoreEqv()(lhs, rhs));
}

Expression abs(const Expression &rhs) {
  return Expression(Abs()(rhs));
}

Expression factorial(const Expression &rhs) {
  return Expression(Factorial()(rhs));
}

Expression sqrt(const Expression &rhs) {
  return Expression(Sqrt()(rhs));
}

Expression pow(const Expression &lhs, const Expression &rhs) {
  return Expression(Pow()(lhs, rhs));
}

Expression exp(const Expression &rhs) {
  return Expression(Exp()(rhs));
}

Expression inv(const Expression &rhs) {
  return Expression(Inv()(rhs));
}

Expression log(const Expression &lhs, const Expression &rhs) {
  return Expression(Log()(lhs, rhs));
}

Expression ln(const Expression &rhs) {
  return Expression(Ln()(rhs));
}

Expression lb(const Expression &rhs) {
  return Expression(Lb()(rhs));
}

Expression lg(const Expression &rhs) {
  return Expression(Lg()(rhs));
}

Expression sin(const Expression &rhs) {
  return Expression(Sin()(rhs));
}

Expression cos(const Expression &rhs) {
  return Expression(Cos()(rhs));
}

Expression tan(const Expression &rhs) {
  return Expression(Tan()(rhs));
}

Expression cot(const Expression &rhs) {
  return Expression(Cot()(rhs));
}

Expression asin(const Expression &rhs) {
  return Expression(Asin()(rhs));
}

Expression acos(const Expression &rhs) {
  return Expression(Acos()(rhs));
}

Expression atan(const Expression &rhs) {
  return Expression(Atan()(rhs));
}

Expression acot(const Expression &rhs) {
  return Expression(Acot()(rhs));
}

Expression e() {
  return E();
}

Expression pi() {
  return Pi();
}

Expression derivative(const Expression &rhs) {
  return Expression(Derivative()(rhs));
}

Expression notL(const Expression &rhs) {
  return Expression(Not()(rhs));
}

Expression andL(const Expression &lhs, const Expression &rhs) {
  return Expression(And()(lhs, rhs));
}

Expression orL(const Expression &lhs, const Expression &rhs) {
  return Expression(Or()(lhs, rhs));
}
}
