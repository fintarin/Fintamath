#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath::detail {

template <typename T, typename... Args>
concept StringConstructable = requires(const std::string &str, Args &&...args) {
  T(str, args...);
};

template <typename Signature>
class Parser;

template <typename Return, typename... Args>
class Parser<Return(Args...)> final {
public:
  using Validator = std::function<bool(const Return &)>;

  using StringConstructor = std::function<Return(const std::string &, Args...)>;

  using Constructor = std::function<Return(Args...)>;

  using ConstructorVector = std::vector<StringConstructor>;

  using ConstructorMap = std::unordered_multimap<std::string, Constructor>;

public:
  template <typename... ConstructorArgs>
    requires(SameAsUnqual<ConstructorArgs, Args> && ...)
  Return parse(const std::string &str, ConstructorArgs &&...args) const {
    constexpr auto trueValidator = [](const Return &) { return true; };
    return parse(trueValidator, str, std::forward<ConstructorArgs>(args)...);
  }

  template <typename... ConstructorArgs>
    requires(SameAsUnqual<ConstructorArgs, Args> && ...)
  Return parse(const Validator &validator, const std::string &str, ConstructorArgs &&...args) const {
    for (const auto &valuePairs = constructorMap.equal_range(str);
         const auto &pair : stdv::iota(valuePairs.first, valuePairs.second)) {

      if (Return value = pair->second(std::forward<ConstructorArgs>(args)...);
          value && validator(value)) {

        return value;
      }
    }

    for (const auto &constructor : extraConstructors) {
      if (Return value = constructor(str, std::forward<ConstructorArgs>(args)...);
          value && validator(value)) {

        return value;
      }
    }

    return Return{};
  }

  template <typename Type>
    requires(!StringConstructable<Type, Args...>)
  void registerType() {
    Constructor constructor = []<typename... ConstructorArgs>(ConstructorArgs &&...args) -> Return {
      return std::make_unique<Type>(std::forward<ConstructorArgs>(args)...);
    };

    registerType<Type>(std::move(constructor));
  }

  template <typename Type>
    requires(!StringConstructable<Type, Args...>)
  void registerType(Constructor constructor) {
    static const std::string name = Type{}.toString();
    constructorMap.emplace(name, std::move(constructor));

    Tokenizer::registerToken(name);
  }

  template <typename Type>
    requires(StringConstructable<Type, Args...>)
  void registerType() {
    StringConstructor constructor = []<typename... ConstructorArgs>(const std::string &str, ConstructorArgs &&...args) -> Return {
      try {
        return std::make_unique<Type>(str, std::forward<ConstructorArgs>(args)...);
      }
      catch (const InvalidInputException &) {
        return std::unique_ptr<Type>{};
      }
    };

    registerType(std::move(constructor));
  }

  void registerType(StringConstructor constructor) {
    extraConstructors.emplace_back(std::move(constructor));
  }

private:
  ConstructorMap constructorMap;

  ConstructorVector extraConstructors;
};

}
