#ifndef MATHCONSTANT_HPP
#define MATHCONSTANT_HPP

#include <cstdint>
#include <string>

#include "fintamath/math_objects/nodes/terms/constants/Constant.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

class MathConstant : public Constant {
public:
  explicit MathConstant(const std::string &strConst);

  Rational toRational(int64_t precision) const;
  std::string toString() const override;
  std::string getTypeName() const override;

private:
  std::string name;
};

namespace types {
bool isConstant(const std::string &str);
}

#endif // MATHCONSTANT_HPP
