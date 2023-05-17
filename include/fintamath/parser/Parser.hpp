#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class Parser {
public:
  template <typename Return, typename... Args>
  using Function = std::function<Return(Args...)>;

  template <typename... Args>
  using Comparator = std::function<bool(Args...)>;

  template <typename Return, typename... Args>
  using Map = std::multimap<std::string, Function<Return, Args...>>;

  template <typename Return, typename... Args>
  using Vector = std::vector<Function<Return, Args...>>;

  template <typename Type, typename BasePtr, typename... Args>
  static void add(Map<BasePtr, Args...> &parserMap) {
    Function<BasePtr, Args...> constructor = [](const Args &...args) {
      return std::make_unique<Type>(args...);
    };

    std::string name = std::make_unique<Type>()->toString();
    parserMap.insert({name, constructor});

    Tokenizer::registerToken(name);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void add(Map<BasePtr, Args...> &parserMap, Function<BasePtr, Args...> &&parserFunc) {
    std::string name = std::make_unique<Type>()->toString();
    parserMap.insert({name, std::move(parserFunc)});

    Tokenizer::registerToken(name);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void add(Vector<BasePtr, Args...> &parserVect) {
    Function<BasePtr, Args...> constructor = [](const Args &...args) {
      try {
        return std::make_unique<Type>(args...);
      }
      catch (const InvalidInputException &) {
        return std::unique_ptr<Type>();
      }
    };

    parserVect.emplace_back(constructor);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void add(Vector<BasePtr, Args...> &parserVect, Function<BasePtr, Args...> &&parserFunc) {
    parserVect.emplace_back(std::move(parserFunc));
  }

  template <typename Return, typename... Args>
  static Return parse(const Map<Return, const Args &...> &parserMap, const std::string &parsedStr,
                      const Args &...args) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
      if (Return value = pair->second(args...)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Return, typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
  static Return parse(const Map<Return, Args &&...> &parserMap, const std::string &parsedStr, Args &&...args) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
      if (Return value = pair->second(move(args)...)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Return, typename... Args>
  static Return parse(const Map<Return, const Args &...> &parserMap, const Comparator<const Return &> &comp,
                      const std::string &parsedStr, const Args &...args) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
      if (Return value = pair->second(args...); value && comp(value)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Return, typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
  static Return parse(const Map<Return, Args &&...> &parserMap, const Comparator<const Return &> &comp,
                      const std::string &parsedStr, Args &&...args) {
    const auto &valuePairs = parserMap.equal_range(parsedStr);

    for (auto pair = valuePairs.first; pair != valuePairs.second; pair++) {
      if (Return value = pair->second(move(args)...); value && comp(value)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Return, typename... Args>
  static Return parse(const Vector<Return, const Args &...> &parserVect, const Args &...args) {
    for (const auto &constructor : parserVect) {
      if (Return value = constructor(args...)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Return, typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
  static Return parse(const Vector<Return, Args &&...> &parserVect, Args &&...args) {
    for (const auto &constructor : parserVect) {
      if (Return value = constructor(move(args)...)) {
        return value;
      }
    }

    return nullptr;
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void registerType(Map<BasePtr, Args...> &parserMap) {
    add<Type>(parserMap);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void registerType(Map<BasePtr, Args...> &parserMap, const Function<BasePtr, Args...> &parserFunc) {
    add<Type>(parserMap, parserFunc);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void registerType(Vector<BasePtr, Args...> &parserVect) {
    add<Type>(parserVect);
  }

  template <typename Type, typename BasePtr, typename... Args>
  static void registerType(Vector<BasePtr, Args...> &parserVect, Function<BasePtr, Args...> &&parserFunc) {
    add<Type>(parserVect, std::move(parserFunc));
  }
};

}
