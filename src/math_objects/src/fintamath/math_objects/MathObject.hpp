#pragma once

#include <sstream>
#include <string>

class MathObject {
public:
  virtual ~MathObject() = 0;

  virtual std::string toString() const = 0;

  template <typename T>
  T to() const;

  template <typename T>
  bool is() const;
};

inline MathObject::~MathObject() = default;

template <typename T>
inline T MathObject::to() const {
  return dynamic_cast<const T &>(*this);
}

template <typename T>
inline bool MathObject::is() const {
  try {
    to<T>();
  } catch (const std::bad_cast &) {
    return false;
  }
  return true;
}
