#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class IComparable : public IArithmetic {
public:
  friend inline std::strong_ordering operator<=>(const IComparable &lhs, const IComparable &rhs) {
    return lhs.compareAbstract(rhs);
  }

  template <std::derived_from<IComparable> T>
  static void registerType(Parser::Function<std::unique_ptr<IComparable>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<IComparable> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IComparable;
  }

protected:
  virtual std::strong_ordering compareAbstract(const IComparable &rhs) const = 0;

private:
  static Parser::Vector<std::unique_ptr<IComparable>, const std::string &> &getParser();
};

template <typename Derived>
class IComparableCRTP : public IComparable {
#define I_COMPARABLE_CRTP IComparableCRTP<Derived>
#include "fintamath/core/IComparableCRTP.hpp"
#undef I_COMPARABLE_CRTP
};

template <std::derived_from<IComparable> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
std::strong_ordering operator<=>(const Lhs &lhs, const Rhs &rhs) {
  return lhs <=> Lhs(rhs);
}

}
