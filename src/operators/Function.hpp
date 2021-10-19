#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>

#include "../calculator/NodeType.hpp"
#include "../numbers/Fraction.hpp"

class Function : public NodeType {
public:
  Function(const Function &);
  explicit Function(const std::string &);
  Function &operator=(const Function &);

  Fraction solve(const Fraction &) const;
  Fraction solve(const Fraction &, const Fraction &) const;

  const std::string getTypeName() const override;
  const std::string toString() const override;

public:
  std::string func;
};

namespace isType {
bool isFunction(const std::string &);
bool isBinaryFunction(const std::string &);
} // namespace isType

#endif // FUNCTION_HPP
