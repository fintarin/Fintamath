#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <cppcoro/generator.hpp>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath::detail {

template <typename T>
concept EmptyConstructable = requires {
  T().toString();
};

template <typename T>
concept StringConstructable = requires(std::string str) {
  T(str).toString();
};

template <typename Signature>
FINTAMATH_API class Parser;

template <typename Return>
FINTAMATH_API class Parser final {
public:
  using Generator = cppcoro::generator<Return>;

private:
  using Constructor = std::function<Return()>;

  using StringToConstructorsMap = std::unordered_map<std::string, std::vector<Constructor>>;

  using GeneratorConstructor = std::function<Generator(std::string)>;

  using GeneratorConstructorVector = std::vector<GeneratorConstructor>;

public:
  Generator parse(std::string str) const {
    if (const auto stringToConstructors = stringToConstructorsMap.find(str); stringToConstructors != stringToConstructorsMap.end()) {
      for (const auto &constructor : stringToConstructors->second) {
        co_yield constructor();
      }
    }

    for (const auto &generatorConstructor : generatorConstructors) {
      for (auto &value : generatorConstructor(str)) {
        co_yield std::move(value);
      }
    }
  }

  std::optional<Return> parseFirst(std::string str) const {
    auto gener = parse(std::move(str));

    if (auto iter = gener.begin(); iter != gener.end()) {
      return std::move(*iter);
    }

    return {};
  }

  template <typename Type>
    requires(!std::is_abstract_v<Type> && !StringConstructable<Type> && EmptyConstructable<Type>)
  void registerType() {
    static const std::string name = Type{}.toString();

    stringToConstructorsMap[name].emplace_back([]() -> Return {
      return std::make_unique<Type>();
    });

    Tokenizer::registerToken(name);
  }

  template <typename Type>
    requires(!std::is_abstract_v<Type> && StringConstructable<Type>)
  void registerType() {
    generatorConstructors.emplace_back([](std::string str) -> Generator {
      try {
        co_yield std::make_unique<Type>(std::move(str));
      }
      catch (const InvalidInputException &) {
        // Go to the next constructor
      }
    });
  }

  template <typename Type>
    requires(std::is_abstract_v<Type>)
  void registerType() {
    generatorConstructors.emplace_back([](std::string str) -> Generator {
      for (auto &value : Type::parse(std::move(str))) {
        co_yield std::move(value);
      }
    });
  }

  template <typename Type>
  void registerType() const {
    // No object of this type can be constructed
  }

private:
  StringToConstructorsMap stringToConstructorsMap;

  GeneratorConstructorVector generatorConstructors;
};

}
