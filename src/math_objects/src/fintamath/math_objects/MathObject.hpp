#ifndef MATHOBJECT_HPP
#define MATHOBJECT_HPP

#include <string>

class MathObject {
public:
  virtual std::string toString() const = 0;
  virtual ~MathObject() = default;
};

#endif // MATHOBJECT_HPP
