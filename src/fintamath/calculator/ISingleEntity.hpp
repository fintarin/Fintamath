#ifndef ISINGLEENTITY_HPP
#define ISINGLEENTITY_HPP

#include <string>

class ISingleEntity {
public:
  virtual std::string getTypeName() const = 0;
  virtual std::string toString() const = 0;
};

#endif // ISINGLEENTITY_HPP
