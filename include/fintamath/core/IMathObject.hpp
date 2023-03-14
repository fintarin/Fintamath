#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "fintamath/core/CoreDefines.hpp"
#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IMathObject {
public:
  virtual ~IMathObject() = default;

  virtual unique_ptr<IMathObject> clone() const = 0;

  virtual string toString() const {
    return {};
  }

  virtual unique_ptr<IMathObject> toMinimalObject() const {
    return clone();
  }

  friend inline bool operator==(const IMathObject &lhs, const IMathObject &rhs) {
    return lhs.equalsAbstract(rhs);
  }

  friend inline bool operator!=(const IMathObject &lhs, const IMathObject &rhs) {
    return !lhs.equalsAbstract(rhs);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IMathObject, T>>>
  static void registerType(Parser::Function<unique_ptr<IMathObject>, const string &> &&parserFunc) {
    Parser::registerType<T>(parserVector, parserFunc);
  }

  static unique_ptr<IMathObject> parse(const string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual bool equalsAbstract(const IMathObject &rhs) const = 0;

private:
  static Parser::Vector<unique_ptr<IMathObject>, const string &> parserVector;
};

template <typename Derived>
class IMathObjectCRTP : virtual public IMathObject {
public:
  unique_ptr<IMathObject> clone() const final {
    return make_unique<Derived>(cast<Derived>(*this));
  }

  bool operator==(const Derived &rhs) const {
    return equals(rhs);
  }

  bool operator!=(const Derived &rhs) const {
    return !equals(rhs);
  }

protected:
  virtual bool equals(const Derived &rhs) const {
    return toString() == rhs.toString();
  }

  bool equalsAbstract(const IMathObject &rhs) const final {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return equals(*rhsPtr);
    }
    if (unique_ptr<IMathObject> rhsPtr = convert(rhs, *this); rhsPtr != nullptr) {
      return equals(cast<Derived>(*rhsPtr));
    }
    if (unique_ptr<IMathObject> lhsPtr = convert(*this, rhs); lhsPtr != nullptr) {
      return *lhsPtr == rhs;
    }
    return false;
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator==(const LhsType &lhs, const RhsType &rhs) {
  return lhs == LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator==(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) == rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator!=(const LhsType &lhs, const RhsType &rhs) {
  return lhs != LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IMathObject, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator!=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) != rhs;
}

inline std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
