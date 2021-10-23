#include "expressions/Expression.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"

using namespace std;

static vector<string> makeVectOfTokens(const string &strExpr);
static Expression makeExpression(const vector<string> &tokensVect);

static void cutSpaces(string &strExpr);

static bool isDigit(char ch);
static bool isLetter(char ch);

static void addMultiply(vector<string> &tokensVect);
static void addClosingBracket(vector<string> &tokensVect);
static void addOpenBracket(vector<string> &tokensVect);
static void addUnaryOperator(vector<string> &tokensVect);
static void addOperator(vector<string> &tokensVect, char token);
static void addRational(vector<string> &tokensVect, const string &token, size_t &pos);
static void addFactorial(vector<string> &tokensVect, const string &token, size_t &pos);
static void addConstVariableFunction(vector<string> &tokensVect, const string &token, size_t &pos);
static void addBinaryFunctions(vector<string> &tokensVect);
static void addValue(shared_ptr<Expression::Elem> &elem, const string &token);

static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end,
                    const string &oper1, const string &oper2);
static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end,
                    const string &oper);
static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end);

static void makeExpressionRec(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t first,
                              size_t last);

Expression::Expression(const std::string &strExpr) {
  *this = makeExpression(makeVectOfTokens(strExpr));
}

std::shared_ptr<Expression::Elem> &Expression::getRootModifiable() {
  return root;
}

static vector<string> makeVectOfTokens(const string &strExpr) {
  string tmpStrExpr = strExpr;
  cutSpaces(tmpStrExpr);
  vector<string> tokensVect;

  for (size_t i = 0; i < tmpStrExpr.size(); ++i) {
    if (tmpStrExpr[i] == ')') {
      addClosingBracket(tokensVect);
    } else if (tmpStrExpr[i] == '(') {
      addOpenBracket(tokensVect);
    } else if (types::isOperator(string(1, tmpStrExpr[i]))) {
      addOperator(tokensVect, tmpStrExpr[i]);
    } else if (tmpStrExpr[i] == '!') {
      addFactorial(tokensVect, tmpStrExpr, i);
    } else if (isDigit(tmpStrExpr[i])) {
      addRational(tokensVect, tmpStrExpr, i);
    } else {
      addConstVariableFunction(tokensVect, tmpStrExpr, i);
    }
  }

  addBinaryFunctions(tokensVect);
  reverse(tokensVect.begin(), tokensVect.end());

  return tokensVect;
}

static Expression makeExpression(const vector<string> &tokensVect) {
  if (tokensVect.empty()) {
    throw invalid_argument("Parser invalid input");
  }

  Expression expr;
  expr.getRootModifiable() = std::make_shared<Expression::Elem>();
  makeExpressionRec(tokensVect, expr.getRootModifiable()->right, 0, tokensVect.size() - 1);

  if (expr.getRootModifiable()->right == nullptr) {
    throw invalid_argument("Parser invalid input");
  }

  return expr;
}

static void cutSpaces(string &strExpr) {
  while (!strExpr.empty()) {
    if (strExpr.front() != ' ') {
      break;
    }
    strExpr.erase(strExpr.begin());
  }
  for (size_t i = 0; i < strExpr.size(); ++i) {
    if (strExpr[i] == ' ') {
      strExpr.erase(i, 1);
      --i;
    }
  }
}

static bool isDigit(char ch) {
  return (ch >= '0' && ch <= '9');
}

static bool isLetter(char ch) {
  return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

static void addMultiply(vector<string> &tokensVect) {
  if (tokensVect.empty()) {
    return;
  }
  if (tokensVect.back() != "," && tokensVect.back() != "(" && !types::isOperator(tokensVect.back()) &&
      !types::isFunction(tokensVect.back())) {
    tokensVect.insert(tokensVect.end(), "*");
  }
}

static void addClosingBracket(vector<string> &tokensVect) {
  tokensVect.emplace_back(")");
}

static void addOpenBracket(vector<string> &tokensVect) {
  addMultiply(tokensVect);
  tokensVect.emplace_back("(");
}

static void addUnaryOperator(vector<string> &tokensVect) {
  if (tokensVect.back() == "+") {
    tokensVect.pop_back();
  } else if (tokensVect.back() == "-") {
    tokensVect.pop_back();
    tokensVect.emplace_back("-1");
    tokensVect.emplace_back("*");
  }
}

static void addOperator(vector<string> &tokensVect, char token) {
  tokensVect.emplace_back(1, token);
  if (tokensVect.size() == 1) {
    addUnaryOperator(tokensVect);
    return;
  }
  if (*(tokensVect.end() - 2) == "(") {
    addUnaryOperator(tokensVect);
  }
}

static void addRational(vector<string> &tokensVect, const string &token, size_t &pos) {
  addMultiply(tokensVect);

  string strVal;
  while (pos < token.size()) {
    strVal += token[pos];
    ++pos;
    if (!isDigit(token[pos]) && !(token[pos] == '.')) {
      break;
    }
  }
  if (pos != 0) {
    --pos;
  }

  tokensVect.push_back(strVal);
}

static void addFactorial(vector<string> &tokensVect, const string &token, size_t &pos) {
  if (tokensVect.empty()) {
    throw invalid_argument("Parser invalid input");
  }
  if (tokensVect.front() == "!" || tokensVect.front() == "!!") {
    throw invalid_argument("Parser invalid input");
  }

  string factorialFunc = "!";
  if (pos != token.size() - 1) {
    if (token[pos + 1] == '!') {
      factorialFunc += '!';
      ++pos;
    }
  }

  size_t bracketsNum = 0;

  for (size_t i = tokensVect.size() - 1; i > 0; --i) {
    if (tokensVect[i] == ")") {
      ++bracketsNum;
    } else if (tokensVect[i] == "(") {
      if (bracketsNum == 0) {
        throw invalid_argument("Parser invalid input");
      }
      --bracketsNum;
    }
    if (bracketsNum == 0) {
      if (types::isFunction(tokensVect[i - 1])) {
        throw invalid_argument("Parser invalid input");
      }
      tokensVect.insert(tokensVect.begin() + (int64_t)i, factorialFunc);
      return;
    }
  }

  if (tokensVect.front() == "(") {
    if (bracketsNum == 0) {
      throw invalid_argument("Parser invalid input");
    }
    --bracketsNum;
  }
  if (bracketsNum != 0) {
    throw invalid_argument("Parser invalid input");
  }

  tokensVect.insert(tokensVect.begin(), factorialFunc);
}

static void addConstVariableFunction(vector<string> &tokensVect, const string &token, size_t &pos) {
  if (token[pos] == '!') {
    addFactorial(tokensVect, token, pos);
    return;
  }
  if (token[pos] == ',') {
    tokensVect.emplace_back(",");
    return;
  }

  addMultiply(tokensVect);

  string literalExpr;
  while (pos < token.size()) {
    literalExpr += token[pos];
    ++pos;
    if (!isLetter(token[pos])) {
      break;
    }
  }
  if (pos != 0) {
    --pos;
  }

  if (types::isConstant(literalExpr) || types::isFunction(literalExpr)) {
    tokensVect.push_back(literalExpr);
  } else {
    throw invalid_argument("Parser invalid input");
  }
}

static void addBinaryFunctions(vector<string> &tokensVect) { // NOLINT
  vector<size_t> placementsVect;

  for (size_t i = 0; i < tokensVect.size(); ++i) {
    if (types::isBinaryFunction(tokensVect[i])) {
      if (find(placementsVect.begin(), placementsVect.end(), i) == placementsVect.end()) {
        string token = tokensVect[i];
        tokensVect.erase(tokensVect.begin() + (int64_t)i);
        size_t bracketsNum = 1;
        bool isFind = false;

        for (size_t j = i + 1; j < tokensVect.size(); ++j) {
          if (bracketsNum == 0) {
            throw invalid_argument("Parser invalid input");
          }
          if (tokensVect[j] == "(") {
            ++bracketsNum;
          } else if (tokensVect[j] == ")") {
            --bracketsNum;
          } else if (bracketsNum == 1 && tokensVect[j] == ",") {
            tokensVect.erase(tokensVect.begin() + (int64_t)j);
            tokensVect.insert(tokensVect.begin() + (int64_t)j, {")", token, "("});

            transform(placementsVect.begin(), placementsVect.end(), placementsVect.begin(),
                      [j](size_t k) { return (k > j) ? k + 1 : k; });
            placementsVect.push_back(j + 1);

            isFind = true;
            break;
          }
        }

        if (!isFind) {
          throw invalid_argument("Parser invalid input");
        }
      }
    }
  }
}

static void addValue(shared_ptr<Expression::Elem> &elem, const string &token) {
  if (types::isConstant(token)) {
    elem->info = std::make_shared<Constant>(token);
  } else {
    try {
      elem->info = std::make_shared<Rational>(token);
    } catch (const invalid_argument &) {
      throw invalid_argument("Parser invalid input");
    }
  }
}

static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end,
                    const string &oper1, const string &oper2) {
  size_t bracketsNum = 0;

  for (size_t i = begin; i <= end; ++i) {
    if (tokensVect[i] == ")") {
      ++bracketsNum;
    } else if (tokensVect[i] == "(") {
      if (bracketsNum == 0) {
        throw invalid_argument("Parser invalid input");
      }
      --bracketsNum;
    }

    if (bracketsNum == 0) {
      if (tokensVect[i] == oper1 || tokensVect[i] == oper2) {
        if (types::isBinaryFunction(oper1)) {
          elem->info = std::make_shared<Function>(tokensVect[i]);
        } else {
          elem->info = std::make_shared<Operator>(tokensVect[i]);
        }
        makeExpressionRec(tokensVect, elem->right, i + 1, end);
        makeExpressionRec(tokensVect, elem->left, begin, i - 1);
        return true;
      }
    }
  }

  return false;
}

static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end,
                    const string &oper) {
  return descent(tokensVect, elem, begin, end, oper, "");
}

static bool descent(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t begin, size_t end) {
  if (types::isFunction(tokensVect[end])) {
    elem->info = std::make_shared<Function>(tokensVect[end]);
    makeExpressionRec(tokensVect, elem->right, begin, end - 1);
    return true;
  }
  return false;
}

static void makeExpressionRec(const vector<string> &tokensVect, shared_ptr<Expression::Elem> &elem, size_t first,
                              size_t last) {
  if (first > last) {
    throw invalid_argument("Parser invalid input");
  }
  if (first == SIZE_MAX || last == SIZE_MAX) {
    throw invalid_argument("Parser invalid input");
  }

  if (elem == nullptr) {
    elem = std::make_shared<Expression::Elem>();
  }

  if (first == last) {
    addValue(elem, tokensVect[first]);
    return;
  }

  if (descent(tokensVect, elem, first, last, "+", "-")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "*", "/")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "^")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "^")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "log")) {
    return;
  }
  if (descent(tokensVect, elem, first, last)) {
    return;
  }
  if (tokensVect[first] == ")" && tokensVect[last] == "(") {
    makeExpressionRec(tokensVect, elem, first + 1, last - 1);
  }
}
