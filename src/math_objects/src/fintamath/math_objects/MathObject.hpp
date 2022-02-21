#pragma once

#include <memory>
#include <string>

namespace fintamath {
  class MathObject {
  public:
    virtual ~MathObject() = default;

    bool operator==(const MathObject &rhs) const;
    bool operator!=(const MathObject &rhs) const;

    virtual std::string toString() const = 0;
  };

  using MathObjectPtr = std::shared_ptr<MathObject>;
}
