#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/other/Abs.hpp"
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
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

Expression eqv(const Expression &lhs, const Expression &rhs) {
  return Expression(Eqv()(lhs, rhs));
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

}
