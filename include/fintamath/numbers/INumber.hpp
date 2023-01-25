#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IIncremental.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class INumber;
using NumberPtr = std::unique_ptr<INumber>;

class INumber : virtual public IComparable, virtual public IArithmetic, virtual public IIncremental {
public:
  virtual bool isPrecise() const {
    return true;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<INumber, T>>>
  static void registerParser() {
    Parser::registerParser<T>(parserVector);
  }

  static NumberPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

  static NumberPtr parse(int64_t num) {
    return parse(std::to_string(num));
  }

private:
  static Parser::ParserVector<NumberPtr, std::string> parserVector;
};

inline NumberPtr operator+(const INumber &lhs, const INumber &rhs) {
  auto res = lhs + cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline NumberPtr operator-(const INumber &lhs, const INumber &rhs) {
  auto res = lhs - cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline NumberPtr operator*(const INumber &lhs, const INumber &rhs) {
  auto res = lhs * cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline NumberPtr operator/(const INumber &lhs, const INumber &rhs) {
  auto res = lhs / cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

template <typename Derived>
class INumberCRTP : public INumber,
                    public IComparableCRTP<Derived>,
                    public IArithmeticCRTP<Derived>,
                    public IIncrementalCRTP<Derived> {};

}
