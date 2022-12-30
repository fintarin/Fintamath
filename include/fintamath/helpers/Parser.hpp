#pragma once

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath::helpers {

template <typename Return, typename... Args>
using Function = std::function<Return(const Args &...)>;

template <typename... Args>
using Comparator = std::function<bool(const Args &...)>;

template <typename Return>
using ParserMap = std::multimap<std::string, Function<Return>>;

template <typename Return, typename... Args>
using ParserVector = std::vector<Function<Return, Args...>>;

template <typename Parsed, typename Return>
void addParser(ParserMap<Return> &parserMap) {
  Function<Return> constructor = [] {
    return std::make_unique<Parsed>(); //
  };

  std::string name = std::make_unique<Parsed>()->toString();

  parserMap.insert({name, constructor});
}

template <typename Parsed, typename Return, typename... Args>
void addParser(ParserVector<Return, Args...> &parserVect) {
  Function<Return, Args...> constructor = [](const Args &...args) {
    try {
      return std::make_unique<Parsed>(args...);
    } catch (const InvalidInputException &) {
      return std::unique_ptr<Parsed>();
    }
  };

  parserVect.push_back(constructor);
}

template <typename Return, typename... Args>
void addParser(ParserVector<Return, Args...> &parserVect, const Function<Return, Args...> &parserFunc) {
  parserVect.push_back(parserFunc);
}

template <typename Return>
Return parse(const ParserMap<Return> &parserMap, const std::string &parsedStr, const Comparator<Return> &comp) {
  const auto &valuePairs = parserMap.equal_range(parsedStr);

  for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
    Return value = pair->second();
    if (comp(value)) {
      return value;
    }
  }

  return nullptr;
}

template <typename Return, typename... Args>
Return parse(const ParserVector<Return, Args...> &parserVect, const Args &...args) {
  for (const auto &constructor : parserVect) {
    if (Return value = constructor(args...)) {
      return value;
    }
  }

  return nullptr;
}

}
