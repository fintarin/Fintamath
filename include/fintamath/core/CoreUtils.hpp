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
unique_ptr<To> cast(unique_ptr<From> &&from) {
  From *fromRawPtr = from.release();
  To *toRawPtr = dynamic_cast<To *>(fromRawPtr);

  if (toRawPtr) {
    from = nullptr;
    return unique_ptr<To>(toRawPtr);
  }

  from.reset(fromRawPtr);

  return unique_ptr<To>();
}

template <typename To, typename From>
shared_ptr<To> cast(const shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from);
}

template <typename To, typename From>
shared_ptr<const To> cast(const shared_ptr<const From> &from) {
  return std::dynamic_pointer_cast<const To>(from);
}

inline unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from) {
  return Converter::convert(to, from);
}

template <typename To>
To convert(const IMathObject &from) {
  static const To to;
  auto res = convert(to, from);

  if (!res) {
    throw std::bad_cast();
  }

  return cast<To>(*res);
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
bool is(const unique_ptr<From> &from) {
  return dynamic_cast<const To *>(from.get());
}

template <typename To, typename From>
bool is(const shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from) != nullptr;
}

template <typename To, typename From>
bool is(const shared_ptr<const From> &from) {
  return std::dynamic_pointer_cast<const To>(from) != nullptr;
}

template <typename To, typename From>
bool is(const std::reference_wrapper<From> &from) {
  return dynamic_cast<To *>(&from.get());
}

template <typename To, typename From>
bool is(const std::reference_wrapper<const From> &from) {
  return dynamic_cast<const To *>(&from.get());
}

}
