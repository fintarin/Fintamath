#include "calculator/Parser.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "numbers/Constant.hpp"
#include "numbers/Variable.hpp"
#include "operators/Function.hpp"
#include "operators/Operator.hpp"

using namespace std;

static void cutSpaces(string &str);

static bool isDigit(char ch);
static bool isLetter(char ch);

static void addMultiply(vector<string> &vect);
static void addClosingBracket(vector<string> &vect);
static void addOpenBracket(vector<string> &vect);
static void addUnaryOperator(vector<string> &vect);
static void addOperator(vector<string> &vect, char ch);
static void addFrac(vector<string> &vect, const string &str, size_t &pos);
static void addFactorial(vector<string> &vect, const string &str, size_t &pos);
static void addConstVariableFunction(vector<string> &vect, const string &str, size_t &pos);
static void addBinaryFunctions(vector<string> &vect);
static void addValue(const string &inStr, shared_ptr<Tree::Node> &root);

static bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end,
                    const string &oper1, const string &oper2);
static bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end,
                    const string &oper);
static bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end);
static void makeTreeRec(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t first, size_t last);

vector<string> Parser::makeVectOfTokens(const string &inStr) {
  string str = inStr;
  cutSpaces(str);
  vector<string> vect;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ')') {
      addClosingBracket(vect);
    } else if (str[i] == '(') {
      addOpenBracket(vect);
    } else if (isType::isOperator(string(1, str[i]))) {
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
  reverse(vect.begin(), vect.end());

  return vect;
}

Tree Parser::makeTree(const vector<string> &vectIOfTokens) {
  if (vectIOfTokens.empty()) {
    throw invalid_argument("Parser invalid input");
  }

  Tree tree;
  tree.root = std::make_shared<Tree::Node>();
  makeTreeRec(vectIOfTokens, tree.root->right, 0, vectIOfTokens.size() - 1);

  if (tree.root->right == nullptr) {
    throw invalid_argument("Parser invalid input");
  }

  return tree;
}

inline void cutSpaces(string &str) {
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

inline bool isDigit(char ch) {
  return (ch >= '0' && ch <= '9');
}

inline bool isLetter(char ch) {
  return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

inline void addMultiply(vector<string> &vect) {
  if (vect.empty()) {
    return;
  }
  if (vect.back() != "," && vect.back() != "(" && !isType::isOperator(vect.back()) &&
      !isType::isFunction(vect.back())) {
    vect.insert(vect.end(), "*");
  }
}

inline void addClosingBracket(vector<string> &vect) {
  vect.emplace_back(")");
}

inline void addOpenBracket(vector<string> &vect) {
  addMultiply(vect);
  vect.emplace_back("(");
}

inline void addUnaryOperator(vector<string> &vect) {
  if (vect.back() == "+") {
    vect.pop_back();
  } else if (vect.back() == "-") {
    vect.pop_back();
    vect.emplace_back("-1");
    vect.emplace_back("*");
  }
}

inline void addOperator(vector<string> &vect, char ch) {
  vect.emplace_back(1, ch);
  if (vect.size() == 1) {
    addUnaryOperator(vect);
    return;
  }
  if (*(vect.end() - 2) == "(") {
    addUnaryOperator(vect);
  }
}

inline void addFrac(vector<string> &vect, const string &str, size_t &pos) {
  addMultiply(vect);

  string fracStr;
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

inline void addFactorial(vector<string> &vect, const string &str, size_t &pos) {
  if (vect.empty()) {
    throw invalid_argument("Parser invalid input");
  }
  if (vect.front() == "!" || vect.front() == "!!") {
    throw invalid_argument("Parser invalid input");
  }

  string factor = "!";
  if (pos != str.size() - 1) {
    if (str[pos + 1] == '!') {
      factor += '!';
      ++pos;
    }
  }

  size_t numOfBrackets = 0;

  for (size_t i = vect.size() - 1; i > 0; --i) {
    if (vect[i] == ")") {
      ++numOfBrackets;
    } else if (vect[i] == "(") {
      if (numOfBrackets == 0) {
        throw invalid_argument("Parser invalid input");
      }
      --numOfBrackets;
    }
    if (numOfBrackets == 0) {
      if (isType::isFunction(vect[i - 1])) {
        throw invalid_argument("Parser invalid input");
      }
      vect.insert(vect.begin() + (int64_t)i, factor);
      return;
    }
  }

  if (vect.front() == "(") {
    if (numOfBrackets == 0) {
      throw invalid_argument("Parser invalid input");
    }
    --numOfBrackets;
  }
  if (numOfBrackets != 0) {
    throw invalid_argument("Parser invalid input");
  }

  vect.insert(vect.begin(), factor);
}

inline void addConstVariableFunction(vector<string> &vect, const string &str, size_t &pos) {
  if (str[pos] == '!') {
    addFactorial(vect, str, pos);
    return;
  }
  if (str[pos] == ',') {
    vect.emplace_back(",");
    return;
  }

  addMultiply(vect);

  string word;
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
    throw invalid_argument("Parser invalid input");
  }
}

inline void addBinaryFunctions(vector<string> &vect) { // NOLINT
  vector<size_t> numOfAdded;

  for (size_t i = 0; i < vect.size(); ++i) {
    if (isType::isBinaryFunction(vect[i])) {
      if (find(numOfAdded.begin(), numOfAdded.end(), i) == numOfAdded.end()) {
        string func = vect[i];
        vect.erase(vect.begin() + (int64_t)i);
        size_t numOfBrackets = 1;
        bool find = false;

        for (size_t j = i + 1; j < vect.size(); ++j) {
          if (numOfBrackets == 0) {
            throw invalid_argument("Parser invalid input");
          }
          if (vect[j] == "(") {
            ++numOfBrackets;
          } else if (vect[j] == ")") {
            --numOfBrackets;
          } else if (numOfBrackets == 1 && vect[j] == ",") {
            vect.erase(vect.begin() + (int64_t)j);
            vect.insert(vect.begin() + (int64_t)j, {")", func, "("});

            transform(numOfAdded.begin(), numOfAdded.end(), numOfAdded.begin(),
                      [j](size_t num) { return (num > j) ? num + 1 : num; });
            numOfAdded.push_back(j + 1);

            find = true;
            break;
          }
        }

        if (!find) {
          throw invalid_argument("Parser invalid input");
        }
      }
    }
  }
}

inline void addValue(const string &inStr, shared_ptr<Tree::Node> &root) {
  if (isType::isConstant(inStr)) {
    root->info = std::make_shared<Constant>(inStr);
  } else if (isType::isVariable(inStr)) {
    root->info = std::make_shared<Variable>(inStr);
  } else {
    try {
      root->info = std::make_shared<Fraction>(inStr);
    } catch (const invalid_argument &) {
      throw invalid_argument("Parser invalid input");
    }
  }
}

inline bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end,
                    const string &oper1, const string &oper2) {
  size_t numOfBrackets = 0;

  for (size_t i = begin; i <= end; ++i) {
    if (vectIOfTokens[i] == ")") {
      ++numOfBrackets;
    } else if (vectIOfTokens[i] == "(") {
      if (numOfBrackets == 0) {
        throw invalid_argument("Parser invalid input");
      }
      --numOfBrackets;
    }

    if (numOfBrackets == 0) {
      if (vectIOfTokens[i] == oper1 || vectIOfTokens[i] == oper2) {
        if (isType::isBinaryFunction(oper1)) {
          root->info = std::make_shared<Function>(vectIOfTokens[i]);
        } else {
          root->info = std::make_shared<Operator>(vectIOfTokens[i]);
        }
        makeTreeRec(vectIOfTokens, root->right, i + 1, end);
        makeTreeRec(vectIOfTokens, root->left, begin, i - 1);
        return true;
      }
    }
  }

  return false;
}

inline bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end,
                    const string &oper) {
  return descent(vectIOfTokens, root, begin, end, oper, "");
}

inline bool descent(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t begin, size_t end) {
  if (isType::isFunction(vectIOfTokens[end])) {
    root->info = std::make_shared<Function>(vectIOfTokens[end]);
    makeTreeRec(vectIOfTokens, root->right, begin, end - 1);
    return true;
  }
  return false;
}

inline void makeTreeRec(const vector<string> &vectIOfTokens, shared_ptr<Tree::Node> &root, size_t first, size_t last) {
  if (first > last) {
    throw invalid_argument("Parser invalid input");
  }
  if (first == SIZE_MAX || last == SIZE_MAX) {
    throw invalid_argument("Parser invalid input");
  }

  if (root == nullptr) {
    root = std::make_shared<Tree::Node>();
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
