#pragma once

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace fintamath::helpers {
  template <typename Value>
  using ParserFunction = std::function<Value()>;

  template <typename Value>
  using ParserStringFunction = std::function<Value(const std::string &str)>;

  template <typename Value>
  using ParserComparator = std::function<bool(const Value &)>;

  template <typename Value>
  using ParserMap = std::multimap<std::string, ParserFunction<Value>>;

  template <typename Value>
  using ParserVector = std::vector<ParserStringFunction<Value>>;

  template <typename Parser, typename Value>
  bool addParser(ParserMap<Value> &parserMap) {
    ParserFunction<Value> constructor = [] {
      return std::make_unique<Parser>(); //
    };

    std::string name = std::make_unique<Parser>()->toString();

    parserMap.insert({name, constructor});
    return true;
  }

  template <typename Parser, typename Value>
  bool addParser(ParserVector<Value> &parserVect) {
    ParserStringFunction<Value> constructor = [](const std::string &str) {
      try {
        return std::make_unique<Parser>(str);
      } catch (const std::invalid_argument &) {
        return std::unique_ptr<Parser>();
      }
    };

    parserVect.push_back(constructor);
    return true;
  }

  template <typename Value>
  bool addParser(ParserVector<Value> &parserVect, const ParserStringFunction<Value> &parserFunc) {
    parserVect.push_back(parserFunc);
    return true;
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

  template <typename Value>
  Value parse(const ParserVector<Value> &parserVect, const std::string &parsedStr) {
    for (const auto &constructor : parserVect) {
      if (Value value = constructor(parsedStr)) {
        return value;
      }
    }

    return nullptr;
  }
}
