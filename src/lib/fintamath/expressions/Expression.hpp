#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>

#include "single_entities/ISingleEntity.hpp"

class Expression {
public:
  struct Elem {
    std::shared_ptr<ISingleEntity> info;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
  };

  Expression() = default;
  explicit Expression(const std::string &strExpr);

  std::shared_ptr<Elem> &getRootModifiable();

private:
  std::shared_ptr<Elem> root = std::make_shared<Elem>();
};

#endif // EXPRESSION_HPP
