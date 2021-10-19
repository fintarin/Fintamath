#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>

#include "calculator/NodeType.hpp"
#include "numbers/Fraction.hpp"

class Function : public NodeType {
public:
  explicit Function(const std::string &);

  Fraction solve(const Fraction &) const;
  Fraction solve(const Fraction &, const Fraction &) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  std::string func;
};

namespace isType {
bool isFunction(const std::string &);
bool isBinaryFunction(const std::string &);
} // namespace isType

#endif // FUNCTION_HPP
