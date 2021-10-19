#ifndef NODETYPE_HPP
#define NODETYPE_HPP

#include <string>

class NodeType {
public:
  virtual std::string getTypeName() const = 0;
  virtual std::string toString() const = 0;
};

#endif // NODETYPE_HPP