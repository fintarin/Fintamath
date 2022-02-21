#pragma once

#include <string>

class MathObject {
public:
  virtual std::string toString() const = 0;
  virtual ~MathObject() = default;
};
