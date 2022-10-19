#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

namespace fintamath::meta {
  template <typename Value>
  using ParserMap = std::multimap<std::string, std::function<Value()>>;

  template <typename Parser, typename Value>
  bool addParser(ParserMap<Value> &parserMap) {
    Value value = std::make_unique<Parser>();
    std::string name = value->toString();

    auto constructor = [] {
      return std::make_unique<Parser>();
    };

    constructor();
    parserMap.insert({name, constructor});

    return true;
  }

  template <typename Value>
  Value parse(const ParserMap<Value> &parserMap, const std::string &parsedStr,
              const std::function<bool(const Value &)> &comp) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto valuePair = valuePairs.first; valuePair != valuePairs.second; valuePair++) {
      Value value = valuePair->second();

      if (comp(value)) {
        return value;
      }
    }

    return {};
  }
}
