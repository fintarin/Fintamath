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
  template <typename Value, typename... Args>
  using ParserFunction = std::function<Value(const Args &...)>;

  template <typename Value>
  using ParserComparator = std::function<bool(const Value &)>;

  template <typename Value>
  using ParserMap = std::multimap<std::string, ParserFunction<Value>>;

  template <typename Value, typename... Args>
  using ParserVector = std::vector<ParserFunction<Value, Args...>>;

  template <typename Parser, typename Value>
  void addParser(ParserMap<Value> &parserMap) {
    ParserFunction<Value> constructor = [] {
      return std::make_unique<Parser>(); //
    };

    std::string name = std::make_unique<Parser>()->toString();

    parserMap.insert({name, constructor});
  }

  template <typename Parser, typename Value, typename... Args>
  void addParser(ParserVector<Value, Args...> &parserVect) {
    ParserFunction<Value, Args...> constructor = [](const Args &...args) {
      try {
        return std::make_unique<Parser>(args...);
      } catch (const InvalidInputException &) {
        return std::unique_ptr<Parser>();
      }
    };

    parserVect.push_back(constructor);
  }

  template <typename Value, typename... Args>
  void addParser(ParserVector<Value, Args...> &parserVect, const ParserFunction<Value, Args...> &parserFunc) {
    parserVect.push_back(parserFunc);
  }

  template <typename Value>
  Value parse(const ParserMap<Value> &parserMap, const std::string &parsedStr, const ParserComparator<Value> &comp) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
      Value value = pair->second();
      if (comp(value)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Value, typename... Args>
  Value parse(const ParserVector<Value, Args...> &parserVect, const Args &...args) {
    for (const auto &constructor : parserVect) {
      if (Value value = constructor(args...)) {
        return value;
      }
    }

    return nullptr;
  }
}
