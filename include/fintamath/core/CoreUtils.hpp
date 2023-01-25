#pragma once

#include <memory>

namespace fintamath {

class IMathObject;

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
To *cast(From *from) {
  return dynamic_cast<To *>(from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
const To *cast(const From *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
const To &cast(const From &from) {
  return dynamic_cast<const To &>(from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
To &&cast(From &&from) {
  return dynamic_cast<To &&>(from);
}

template <typename To, typename From,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, From> && std::is_base_of_v<IMathObject, To>>>
std::unique_ptr<To> cast(std::unique_ptr<From> &&from) {
  From *fromRawPtr = from.release();
  To *toRawPtr = dynamic_cast<To *>(fromRawPtr);

  if (toRawPtr) {
    return std::unique_ptr<To>(toRawPtr);
  }

  from.reset(fromRawPtr);

  return std::unique_ptr<To>();
}

}
