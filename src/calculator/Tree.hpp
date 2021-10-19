#ifndef TREE_HPP
#define TREE_HPP

#include <memory>

#include "NodeType.hpp"

struct Tree {
  struct Node {
    std::shared_ptr<NodeType> info;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
  };
  std::shared_ptr<Node> root;
};

#endif // TREE_HPP