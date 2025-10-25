#pragma once

#include <string_view>
#include <unordered_map>

namespace fintamath::detail {

class PrefixTrie {
public:
  void add(std::string_view str);

  size_t getPrefixSize(std::string_view str, size_t fromIndex = 0) const;

private:
  struct Node;

  using Nodes = std::unordered_map<char, Node>;

  struct Node {
    Nodes children;
    bool isLeaf = false;
  };

private:
  Nodes rootChildren;
};

}
