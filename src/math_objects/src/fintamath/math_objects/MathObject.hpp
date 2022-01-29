#pragma once

#include <memory>
#include <string>

class MathObject {
public:
  virtual std::string toString() const = 0;
  virtual ~MathObject() = default;
};

using MathObjectPtr = std::shared_ptr<MathObject>;
