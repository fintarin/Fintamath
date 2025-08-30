#pragma once

#include <functional>
#include <tuple>
#include <unordered_map>

#include "fintamath/core/Hash.hpp"
#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath::detail {

template <typename Signature>
class MultiMethod;

template <typename ResBase, typename... ArgsBase>
class MultiMethod<ResBase(ArgsBase...)> final {
  template <typename>
  using ArgId = MathObjectClass;

  using CallbackId = std::tuple<ArgId<ArgsBase>...>;

  using CallbackBase = std::function<ResBase(ArgsBase...)>;

  using IdToCallbackMap = std::unordered_map<CallbackId, CallbackBase, Hash<CallbackId>>;

public:
  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  void add(auto func) {
    constexpr auto funcId = CallbackId(Args::getClassStatic()...);

    idToFunctionMap[funcId] = [func = std::move(func)](ArgsBase... args) -> ResBase {
      return func(cast<Args>(args)...);
    };
  }

  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  ResBase operator()(Args &&...args) const {
    const CallbackId funcId = getFunctionId(args...);

    if (auto iter = idToFunctionMap.find(funcId); iter != idToFunctionMap.end()) {
      return iter->second(std::forward<Args>(args)...);
    }

    return nullptr;
  }

private:
  template <typename... Args>
  static CallbackId getFunctionId(const Args &...args) {
    if constexpr (requires { CallbackId(args->getClass()...); }) {
      return CallbackId(args->getClass()...);
    }
    else {
      return CallbackId(args.getClass()...);
    }
  }

private:
  IdToCallbackMap idToFunctionMap;
};

}
