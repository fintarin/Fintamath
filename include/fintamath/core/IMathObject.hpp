#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IMathObject {
public:
  virtual ~IMathObject() = default;

  virtual std::unique_ptr<IMathObject> clone() const & = 0;

  virtual std::unique_ptr<IMathObject> clone() && = 0;

  virtual std::string toString() const {
    return typeid(*this).name();
  }

  virtual std::unique_ptr<IMathObject> toMinimalObject() const {
    return clone();
  }

  virtual MathObjectType getType() const = 0;

  friend inline bool operator==(const IMathObject &lhs, const IMathObject &rhs) {
    return lhs.equalsAbstract(rhs);
  }

  template <std::derived_from<IMathObject> T>
  static void registerType(Parser::Function<std::unique_ptr<IMathObject>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<IMathObject> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IMathObject;
  }

protected:
  virtual bool equalsAbstract(const IMathObject &rhs) const = 0;

private:
  static Parser::Vector<std::unique_ptr<IMathObject>, const std::string &> &getParser();
};

template <typename Derived>
class IMathObjectCRTP : public IMathObject {
#define I_MATH_OBJECT_CRTP IMathObjectCRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP
};

template <std::derived_from<IMathObject> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
bool operator==(const Lhs &lhs, const Rhs &rhs) {
  return lhs == Lhs(rhs);
}

inline std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
