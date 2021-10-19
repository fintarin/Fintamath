#include "Parser.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "../numbers/Constant.hpp"
#include "../numbers/Variable.hpp"
#include "../operators/Function.hpp"
#include "../operators/Operator.hpp"
#include "ExceptionClasses.hpp"

void cutSpaces(std::string &str) {
  while (!str.empty()) {
    if (str.front() != ' ') {
      break;
    }
    str.erase(str.begin());
  }
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ' ') {
      str.erase(i, 1);
      --i;
    }
  }
}

bool isDigit(const char ch) {
  return (ch >= '0' && ch <= '9');
}

bool isLetter(const char ch) {
  return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

void addMultiply(std::vector<std::string> &vect) {
  if (vect.size() < 1) {
    return;
  }
  if (vect.back() != "," && vect.back() != "(" && !isType::isOperator(vect.back()) &&
      !isType::isFunction(vect.back())) {
    vect.insert(vect.end(), "*");
  }
}

void addClosingBracket(std::vector<std::string> &vect) {
  vect.push_back(")");
}

void addOpenBracket(std::vector<std::string> &vect) {
  addMultiply(vect);
  vect.push_back("(");
}

void addUnaryOperator(std::vector<std::string> &vect) {
  if (vect.back() == "+") {
    vect.pop_back();
  } else if (vect.back() == "-") {
    vect.pop_back();
    vect.push_back("-1");
    vect.push_back("*");
  }
}

void addOperator(std::vector<std::string> &vect, const char ch) {
  vect.push_back(std::string(1, ch));
  if (vect.size() == 1) {
    addUnaryOperator(vect);
    return;
  }
  if (*(vect.end() - 2) == "(") {
    addUnaryOperator(vect);
  }
}

void addFrac(std::vector<std::string> &vect, const std::string &str, size_t &pos) {
  addMultiply(vect);

  std::string fracStr;
  while (pos < str.size()) {
    fracStr += str[pos];
    ++pos;
    if (!isDigit(str[pos]) && !(str[pos] == '.')) {
      break;
    }
  }
  if (pos != 0) {
    --pos;
  }

  vect.push_back(fracStr);
}

void addFactorial(std::vector<std::string> &vect, const std::string &str, size_t &pos) {
  if (vect.size() < 1) {
    throw IncorrectInput("Parser");
  }
  if (vect.front() == "!" || vect.front() == "!!") {
    throw IncorrectInput("Parser");
  }

  std::string factor = "!";
  if (pos != str.size() - 1)
    if (str[pos + 1] == '!') {
      factor += '!';
      ++pos;
    }

  size_t numOfBrackets = 0;

  for (size_t i = vect.size() - 1; i > 0; --i) {
    if (vect[i] == ")") {
      ++numOfBrackets;
    } else if (vect[i] == "(") {
      if (numOfBrackets == 0) {
        throw IncorrectInput("Parser");
      }
      --numOfBrackets;
    }
    if (numOfBrackets == 0) {
      if (isType::isFunction(vect[i - 1])) {
        throw IncorrectInput("Parser");
      }
      vect.insert(vect.begin() + i, factor);
      return;
    }
  }

  if (vect.front() == "(") {
    if (numOfBrackets == 0) {
      throw IncorrectInput("Parser");
    }
    --numOfBrackets;
  }
  if (numOfBrackets != 0) {
    throw IncorrectInput("Parser");
  }

  vect.insert(vect.begin(), factor);
}

void addConstVariableFunction(std::vector<std::string> &vect, const std::string &str, size_t &pos) {
  if (str[pos] == '!') {
    addFactorial(vect, str, pos);
    return;
  }
  if (str[pos] == ',') {
    vect.push_back(",");
    return;
  }

  addMultiply(vect);

  std::string word;
  while (pos < str.size()) {
    word += str[pos];
    ++pos;
    if (!isLetter(str[pos])) {
      break;
    }
  }
  if (pos != 0) {
    --pos;
  }

  if (isType::isConstant(word) || isType::isVariable(word) || isType::isFunction(word)) {
    vect.push_back(word);
  } else {
    throw IncorrectInput("Parser");
  }
}

void addBinaryFunctions(std::vector<std::string> &vect) {
  std::vector<size_t> numOfAdded;

  for (size_t i = 0; i < vect.size(); ++i) {
    if (isType::isBinaryFunction(vect[i])) {
      if (std::find(numOfAdded.begin(), numOfAdded.end(), i) == numOfAdded.end()) {
        std::string func = vect[i];
        vect.erase(vect.begin() + i);
        size_t numOfBrackets = 1;
        bool find = false;

        for (size_t j = i + 1; j < vect.size(); ++j) {
          if (numOfBrackets == 0) {
            throw IncorrectInput("Parser");
          }
          if (vect[j] == "(") {
            ++numOfBrackets;
          } else if (vect[j] == ")") {
            --numOfBrackets;
          } else if (numOfBrackets == 1 && vect[j] == ",") {
            vect.erase(vect.begin() + j);
            vect.insert(vect.begin() + j, {")", func, "("});

            std::transform(numOfAdded.begin(), numOfAdded.end(), numOfAdded.begin(),
                           [j](const size_t &num) { return (num > j) ? num + 1 : num; });
            numOfAdded.push_back(j + 1);

            find = true;
            break;
          }
        }

        if (!find) {
          throw IncorrectInput("Parser");
        }
      }
    }
  }
}

std::vector<std::string> Parser::makeVectOfTokens(const std::string &inStr) const {
  std::string str = inStr;
  cutSpaces(str);
  std::vector<std::string> vect;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ')') {
      addClosingBracket(vect);
    } else if (str[i] == '(') {
      addOpenBracket(vect);
    } else if (isType::isOperator(std::string(1, str[i]))) {
      addOperator(vect, str[i]);
    } else if (str[i] == '!') {
      addFactorial(vect, str, i);
    } else if (isDigit(str[i])) {
      addFrac(vect, str, i);
    } else {
      addConstVariableFunction(vect, str, i);
    }
  }

  addBinaryFunctions(vect);
  std::reverse(vect.begin(), vect.end());

  return vect;
}

void addValue(const std::string &inStr, std::shared_ptr<Tree::Node> &root) {
  if (isType::isConstant(inStr)) {
    root->info = std::shared_ptr<Constant>(new Constant(inStr));
  } else if (isType::isVariable(inStr)) {
    root->info = std::shared_ptr<Variable>(new Variable(inStr));
  } else {
    try {
      root->info = std::shared_ptr<Fraction>(new Fraction(inStr));
    } catch (IncorrectInput) {
      throw IncorrectInput("Parser");
    }
  }
}

void makeTreeRec(const std::vector<std::string> &, std::shared_ptr<Tree::Node> &, const size_t, const size_t);

bool descent(const std::vector<std::string> &vectIOfTokens, std::shared_ptr<Tree::Node> &root, const size_t begin,
             const size_t end, const std::string &oper1, const std::string &oper2) {
  size_t numOfBrackets = 0;

  for (size_t i = begin; i <= end; ++i) {
    if (vectIOfTokens[i] == ")") {
      ++numOfBrackets;
    } else if (vectIOfTokens[i] == "(") {
      if (numOfBrackets == 0) {
        throw IncorrectInput("Parser");
      }
      --numOfBrackets;
    }

    if (numOfBrackets == 0) {
      if (vectIOfTokens[i] == oper1 || vectIOfTokens[i] == oper2) {
        if (isType::isBinaryFunction(oper1)) {
          root->info = std::shared_ptr<Function>(new Function(vectIOfTokens[i]));
        } else {
          root->info = std::shared_ptr<Operator>(new Operator(vectIOfTokens[i]));
        }
        makeTreeRec(vectIOfTokens, root->right, i + 1, end);
        makeTreeRec(vectIOfTokens, root->left, begin, i - 1);
        return true;
      }
    }
  }

  return false;
}

bool descent(const std::vector<std::string> &vectIOfTokens, std::shared_ptr<Tree::Node> &root, const size_t begin,
             const size_t end, const std::string &oper) {
  return descent(vectIOfTokens, root, begin, end, oper, "");
}

bool descent(const std::vector<std::string> &vectIOfTokens, std::shared_ptr<Tree::Node> &root, const size_t begin,
             const size_t end) {
  if (isType::isFunction(vectIOfTokens[end])) {
    root->info = std::shared_ptr<Function>(new Function(vectIOfTokens[end]));
    makeTreeRec(vectIOfTokens, root->right, begin, end - 1);
    return true;
  }
  return false;
}

void makeTreeRec(const std::vector<std::string> &vectIOfTokens, std::shared_ptr<Tree::Node> &root, const size_t first,
                 const size_t last) {
  if (first > last) {
    throw IncorrectInput("Parser");
  }
  if (first == SIZE_MAX || last == SIZE_MAX) {
    throw IncorrectInput("Parser");
  }

  if (root == nullptr) {
    root = std::shared_ptr<Tree::Node>(new Tree::Node);
  }

  size_t begin = first;
  size_t end = last;

  if (begin == end) {
    addValue(vectIOfTokens[begin], root);
    return;
  }

  if (descent(vectIOfTokens, root, begin, end, "+", "-")) {
    return;
  }
  if (descent(vectIOfTokens, root, begin, end, "*", "/")) {
    return;
  }
  if (descent(vectIOfTokens, root, begin, end, "^")) {
    return;
  }
  if (descent(vectIOfTokens, root, begin, end, "^")) {
    return;
  }
  if (descent(vectIOfTokens, root, begin, end, "log")) {
    return;
  }
  if (descent(vectIOfTokens, root, begin, end)) {
    return;
  }
  if (vectIOfTokens[begin] == ")" && vectIOfTokens[end] == "(") {
    makeTreeRec(vectIOfTokens, root, begin + 1, end - 1);
  }
}

Tree Parser::makeTree(const std::vector<std::string> &vectIOfTokens) const {
  if (vectIOfTokens.empty()) {
    throw IncorrectInput("Parser");
  }

  Tree tree;
  tree.root = std::shared_ptr<Tree::Node>(new Tree::Node);
  makeTreeRec(vectIOfTokens, tree.root->right, 0, vectIOfTokens.size() - 1);

  if (tree.root->right == nullptr) {
    throw IncorrectInput("Parser");
  }

  return tree;
}
