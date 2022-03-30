#ifndef ARITHMETICEXPRESSION_HPP
#define ARITHMETICEXPRESSION_HPP

#include <memory>

#include "fintamath/math_objects/nodes/Node.hpp"

class Expression : public Node {
public:
  struct Elem {
    std::shared_ptr<MathObject> info;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
  };

  Expression() = default;
  explicit Expression(const std::string &strExpr);

  std::string toString() const override;

  std::shared_ptr<Elem> &getRootModifiable();

private:
  std::shared_ptr<Elem> root = std::make_shared<Elem>();
};

#endif // ARITHMETICEXPRESSION_HPP
