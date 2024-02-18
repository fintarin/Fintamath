#pragma once

#include <compare>
#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class IComparable : public IArithmetic {
  using ComparableParser = detail::Parser<std::unique_ptr<IComparable>()>;

public:
  friend std::strong_ordering operator<=>(const IComparable &lhs, const IComparable &rhs) {
    return lhs.compareAbstract(rhs);
  }

  static std::unique_ptr<IComparable> parse(const std::string &str) {
    return getParser().parse(str);
  }

  static void registerType(ComparableParser::StringConstructor constructor) {
    getParser().registerType(std::move(constructor));
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IComparable, "IComparable"};
  }

protected:
  virtual std::strong_ordering compareAbstract(const IComparable &rhs) const = 0;

private:
  static ComparableParser &getParser();
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
