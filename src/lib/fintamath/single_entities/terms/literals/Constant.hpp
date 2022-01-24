#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <cstdint>
#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

class Constant : public ISingleEntity {
public:
  explicit Constant(const std::string &strConst);

  Rational toRational(int64_t precision) const;
  std::string toString() const override;
  std::string getTypeName() const override;

private:
  std::string name;
};

namespace types {
bool isConstant(const std::string &str);
}

#endif // CONSTANT_HPP
