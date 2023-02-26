#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IBinaryExpression &rhs) : lhs(rhs.lhs->clone()), rhs(rhs.rhs->clone()) {
}

IBinaryExpression::IBinaryExpression(const IMathObject &lhs, const IMathObject &rhs)
    : lhs(lhs.clone()), rhs(rhs.clone()) {
}

IBinaryExpression::IBinaryExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : lhs(std::move(lhs)), rhs(std::move(rhs)) {
}

IBinaryExpression &IBinaryExpression::operator=(const IBinaryExpression &rhs) {
  if (&rhs != this) {
    if (rhs.lhs && rhs.rhs) {
      this->lhs = rhs.lhs->clone();
      this->rhs = rhs.rhs->clone();
    } else {
      this->lhs = nullptr;
      this->rhs = nullptr;
    }
  }
  return *this;
}

void IBinaryExpression::setPrecision(uint8_t precision) {
  // TODO: implement it
}

std::string IBinaryExpression::toString() const {
  // TODO: implement it
  return {};
}

}
