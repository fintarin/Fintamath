#include "fintamath/functions/Functions.hpp"

#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/other/Abs.hpp"
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

namespace fintamath {
  Expression eqv(const Expression &lhs, const Expression &rhs) {
    return Eqv()(lhs, rhs);
  }

  Expression abs(const Expression &rhs) {
    return Abs()(rhs);
  }

  Expression factorial(const Expression &rhs) {
    return Factorial()(rhs);
  }

  Expression doubleFactorial(const Expression &rhs) {
    return DoubleFactorial()(rhs);
  }

  Expression sqrt(const Expression &rhs) {
    return Sqrt()(rhs);
  }

  Expression pow(const Expression &lhs, const Expression &rhs) {
    return Pow()(lhs, rhs);
  }

  Expression exp(const Expression &rhs) {
    return Exp()(rhs);
  }

  Expression log(const Expression &lhs, const Expression &rhs) {
    return Log()(lhs, rhs);
  }

  Expression ln(const Expression &rhs) {
    return Ln()(rhs);
  }

  Expression lb(const Expression &rhs) {
    return Lb()(rhs);
  }

  Expression lg(const Expression &rhs) {
    return Lg()(rhs);
  }

  Expression sin(const Expression &rhs) {
    return Sin()(rhs);
  }

  Expression cos(const Expression &rhs) {
    return Cos()(rhs);
  }

  Expression tan(const Expression &rhs) {
    return Tan()(rhs);
  }

  Expression cot(const Expression &rhs) {
    return Cot()(rhs);
  }

  Expression asin(const Expression &rhs) {
    return Asin()(rhs);
  }

  Expression acos(const Expression &rhs) {
    return Acos()(rhs);
  }

  Expression atan(const Expression &rhs) {
    return Atan()(rhs);
  }

  Expression acot(const Expression &rhs) {
    return Acot()(rhs);
  }
}
