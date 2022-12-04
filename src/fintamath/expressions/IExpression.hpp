#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {
  class IExpression;
  using ExpressionPtr = std::unique_ptr<IExpression>;

  class IExpression : virtual public IMathObject { // TODO replace IMathObject to IArithmetic
  protected:
    using TokenVector = std::vector<std::string>;

    static ExpressionPtr parse(const std::string &str);
  protected:
    static TokenVector tokenize(const std::string &str);
  private:
    static TokenVector handleLetterToken(const std::string &str);
    static bool appendToken(TokenVector& tokens, std::string& token);
    static bool isDigit(char c);
    static bool isLetter(char c);
    static bool isBracket(char c);
    static bool isSpecial(char c);
    static std::string cutSpacesFromBeginEnd(const std::string& str);
  };

  template <typename Derived>
  class IExpressionCRTP : virtual public IExpression,
                          virtual public IMathObjectCRTP<Derived> { // TODO replace IMathObjectCRTP to IArithmeticCRTP
  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}
