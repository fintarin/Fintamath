#pragma once

#include <typeinfo>

namespace fintamath {

class TypeInfo {
public:
  TypeInfo(const std::type_info &info);

  friend bool operator==(const TypeInfo &lhs, const TypeInfo &rhs);

  friend bool operator<(const TypeInfo &lhs, const TypeInfo &rhs);

private:
  const std::type_info &info;
};

inline TypeInfo::TypeInfo(const std::type_info &tinfo) : info(tinfo) {
}

inline bool operator<(const TypeInfo &lhs, const TypeInfo &rhs) {
  return lhs.info.before(rhs.info);
}

}
