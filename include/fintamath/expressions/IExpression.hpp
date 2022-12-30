#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/Defines.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/helpers/Parser.hpp"

namespace fintamath {

class IExpression;
using ExpressionPtr = std::unique_ptr<IExpression>;

class IExpression : virtual public IMathObject {
public:
  ~IExpression() override = default;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IExpression, T>>>
  static void addParser() {
    helpers::addParser<T>(parserMap);
  }
  static ExpressionPtr parse(const std::string &str) {
    return helpers::parse(parserMap, tokenize(str));
  }
  static ExpressionPtr parse(const TokenVector &tokens) {
    return helpers::parse(parserMap, tokens);
  }
  static std::string tokensToString(const TokenVector &tokens);
  virtual uint16_t getInfoPriority() = 0;

  virtual void setPrecision(uint8_t precision) = 0;

  virtual MathObjectPtr simplify(bool isPrecise) const = 0;

  virtual std::vector<MathObjectPtr> getVariables() const;

private:
  static bool appendToken(TokenVector &tokens, std::string &token);
  static bool isDigit(char c);
  static bool isBracket(char c);
  static bool isBracket(const std::string &c);
  static bool isOpenBracket(char c);
  static bool isCloseBracket(char c);
  static bool isSpecial(char c);
  static std::string cutSpacesFromBeginEnd(const std::string &str);
  static bool isCanInsertMultiplyCharacter(char c);
  static bool findCharInStr(char c, const std::string &str);

protected:
  static bool isLetter(char c);
  static bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);
  static TokenVector tokenize(const std::string &str);
  static bool isOneSymbolToken(const std::string &token);
  static bool isOneSymbolToken(char token);
  static TokenVector cutBraces(const TokenVector &tokens);
  static std::string tryPutInBracketsIfNeg(const MathObjectPtr &obj);

  template <typename T>
  static void pushPolynomToPolynom(typename T::Polynom &push, typename T::Polynom &cont);

private:
  static helpers::ParserVector<ExpressionPtr, TokenVector> parserMap;
};

template <typename T>
void IExpression::pushPolynomToPolynom(typename T::Polynom &push, typename T::Polynom &cont) {
  for (const auto &elem : push) {
    cont.emplace_back(elem);
  }
}

template <typename Derived>
class IExpressionCRTP : virtual public IExpression, virtual public IMathObjectCRTP<Derived> {};

}
