#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <string>

#include "calculator/NodeType.hpp"
#include "numbers/Fraction.hpp"

class Constant : public NodeType {
public:
  Constant(const Constant &);
  explicit Constant(const std::string &);
  Constant &operator=(const Constant &);

  Fraction toFraction() const;
  std::string toString() const override;
  std::string getTypeName() const override;

private:
  std::string constant;
};

namespace isType {
bool isConstant(const std::string &);
}

#endif // CONSTANT_HPP