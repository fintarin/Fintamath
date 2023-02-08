#pragma once

#include <memory>

#include "fintamath/meta/Converter.hpp"

namespace fintamath {

class IMathObject;
using MathObjectPtr = std::unique_ptr<IMathObject>;

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
To *cast(IMathObject *from) {
  return dynamic_cast<To *>(from);
}

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
const To *cast(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
const To &cast(const IMathObject &from) {
  return dynamic_cast<const To &>(from);
}

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
To &&cast(IMathObject &&from) {
  return dynamic_cast<To &&>(from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
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

inline MathObjectPtr convert(const IMathObject &from, const IMathObject &to) {
  return Converter::convert(from, to);
}

template <typename To>
To convert(const IMathObject &from) {
  static const To to;
  return cast<To>(*convert(from, to));
}

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
bool is(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To, typename = std::enable_if_t<std::is_base_of_v<IMathObject, To>>>
bool is(const IMathObject &from) {
  return dynamic_cast<const To *>(&from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
bool is(const std::unique_ptr<From> &from) {
  return dynamic_cast<const To *>(from.get());
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
bool is(const std::reference_wrapper<From> &from) {
  return dynamic_cast<const To *>(&from.get());
}

}
