#pragma once

#include <sstream>
#include <string>

namespace fintamath {
  class Object {
  public:
    virtual ~Object() = default;

    virtual std::string toString() const = 0;

    template <typename T>
    T to() const;

    template <typename T>
    bool is() const;

    virtual std::shared_ptr<Object> clone() const = 0;
  };

  template <typename T>
  inline T Object::to() const {
    return dynamic_cast<const T &>(*this);
  }

  template <typename T>
  inline bool Object::is() const {
    try {
      to<T>();
    } catch (const std::bad_cast &) {
      return false;
    }
    return true;
  }
}
