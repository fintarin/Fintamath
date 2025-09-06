#pragma once

#include <functional>
#include <tuple>
#include <unordered_map>

#include "fintamath/core/Hash.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath::detail {

template <typename Signature>
class MultiMethod;

template <typename ResBase, typename... ArgsBase>
class MultiMethod<ResBase(ArgsBase...)> final {
  template <typename>
  using ArgId = MathObjectClass;

  using FunctionId = std::tuple<ArgId<ArgsBase>...>;

  using FunctionBase = std::function<ResBase(ArgsBase...)>;

  using IdToFunctionMap = std::unordered_map<FunctionId, FunctionBase, Hash<FunctionId>>;

public:
  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  void add(auto func) {
    constexpr auto funcId = FunctionId(Args::getClassStatic()...);

    idToFunctionMap[funcId] = [func = std::move(func)](ArgsBase... args) -> ResBase {
      return func(cast<Args>(args)...);
    };
  }

  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  ResBase operator()(Args &&...args) const {
    const auto funcId = FunctionId(args.getClass()...);

    if (auto iter = idToFunctionMap.find(funcId); iter != idToFunctionMap.end()) {
      return iter->second(std::forward<Args>(args)...);
    }

    return nullptr;
  }

private:
  IdToFunctionMap idToFunctionMap;
};

}
