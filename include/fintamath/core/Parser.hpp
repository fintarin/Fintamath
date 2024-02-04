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

namespace fintamath {

template <typename Return, typename... Args>
class Parser final {
public:
  using Validator = std::function<bool(const Return &)>;

  using Constructor = std::function<Return(const std::string &, Args...)>;

  using TypeConstructor = std::function<Return(Args...)>;

  using ConstructorVector = std::vector<Constructor>;

  using ConstructorMap = std::unordered_multimap<std::string, TypeConstructor>;

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
  void registerType() {
    TypeConstructor constructor = []<typename... ConstructorArgs>(ConstructorArgs &&...args) -> Return {
      return std::make_unique<Type>(std::forward<ConstructorArgs>(args)...);
    };

    registerType<Type>(std::move(constructor));
  }

  template <typename Type>
  void registerType(TypeConstructor constructor) {
    static const std::string name = Type{}.toString();
    constructorMap.emplace(name, std::move(constructor));

    Tokenizer::registerToken(name);
  }

  template <typename Type>
  void registerConstructor() {
    Constructor constructor = []<typename... ConstructorArgs>(const std::string &str, ConstructorArgs &&...args) -> Return {
      try {
        return std::make_unique<Type>(str, std::forward<ConstructorArgs>(args)...);
      }
      catch (const InvalidInputException &) {
        return std::unique_ptr<Type>{};
      }
    };

    registerConstructor(std::move(constructor));
  }

  void registerConstructor(Constructor constructor) {
    extraConstructors.emplace_back(std::move(constructor));
  }

private:
  ConstructorMap constructorMap;

  ConstructorVector extraConstructors;
};

}
