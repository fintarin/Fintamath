#pragma once

#include <string_view>
#include <unordered_map>

namespace fintamath::detail {

class PrefixTrie {
  struct Node;
  using Nodes = std::unordered_map<char, Node>;

  struct Node {
    Nodes children;
    bool isLeaf = false;
  };

public:
  void add(std::string_view str);

  size_t getPrefixSize(std::string_view str, size_t fromIndex = 0) const;

private:
  Nodes rootChildren;
};

}
