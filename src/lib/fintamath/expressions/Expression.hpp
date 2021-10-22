#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>

#include "single_entities/ISingleEntity.hpp"

struct Expression {
  struct Elem {
    std::shared_ptr<ISingleEntity> info;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
  };
  std::shared_ptr<Elem> root;
};

#endif // EXPRESSION_HPP
