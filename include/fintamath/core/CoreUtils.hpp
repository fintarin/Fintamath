#pragma once

#include <memory>

#include "fintamath/meta/Converter.hpp"

namespace fintamath {

template <typename To>
To *cast(IMathObject *from) {
  return dynamic_cast<To *>(from);
}

template <typename To>
const To *cast(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To>
const To &cast(const IMathObject &from) {
  return dynamic_cast<const To &>(from);
}

template <typename To>
To &&cast(IMathObject &&from) {
  return dynamic_cast<To &&>(from);
}

template <typename To, typename From>
std::unique_ptr<To> cast(std::unique_ptr<From> &&from) {
  From *fromRawPtr = from.release();
  To *toRawPtr = dynamic_cast<To *>(fromRawPtr);

  if (toRawPtr) {
    from = nullptr;
    return std::unique_ptr<To>(toRawPtr);
  }

  from.reset(fromRawPtr);

  return std::unique_ptr<To>();
}

template <typename To, typename From>
std::shared_ptr<To> cast(const std::shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from);
}

inline std::unique_ptr<IMathObject> convert(const IMathObject &from, const IMathObject &to) {
  return Converter::convert(from, to);
}

template <typename To>
To convert(const IMathObject &from) {
  static const To to;
  return cast<To>(*convert(from, to));
}

template <typename To>
bool is(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To>
bool is(const IMathObject &from) {
  return dynamic_cast<const To *>(&from);
}

template <typename To, typename From>
bool is(const std::unique_ptr<From> &from) {
  return dynamic_cast<const To *>(from.get());
}

template <typename To, typename From>
bool is(const std::shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from) != nullptr;
}

template <typename To, typename From>
bool is(const std::reference_wrapper<From> &from) {
  return dynamic_cast<const To *>(&from.get());
}

}
