#include "fintamath/core/PrefixTrie.hpp"

#include <cassert>

namespace fintamath::detail {

void PrefixTrie::add(const std::string_view str) {
  Node *parent = nullptr;
  Nodes *children = &rootChildren;

  for (char ch : str) {
    parent = &children->try_emplace(ch, Node{}).first->second;
    children = &parent->children;
  }

  if (parent) {
    parent->isLeaf = true;
  }
}

size_t PrefixTrie::getPrefixSize(const std::string_view str, size_t fromIndex) const {
  const Nodes *children = &rootChildren;
  size_t maxSize = fromIndex;

  for (size_t i = fromIndex; i < str.size(); i++) {
    const auto childIter = children->find(str[i]);
    if (childIter == children->end()) {
      break;
    }

    const Node &child = childIter->second;
    if (child.isLeaf) {
      maxSize = std::max(maxSize, i + 1);
    }

    children = &child.children;
  }

  return maxSize - fromIndex;
}

}
