#ifndef NODETYPE_HPP
#define NODETYPE_HPP

#include <string>

class NodeType {
public:
    const virtual std::string getTypeName() const = 0;
    const virtual std::string toString() const = 0;
};

#endif // NODETYPE_HPP