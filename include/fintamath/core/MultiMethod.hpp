#pragma once

#include <functional>
#include <optional>
#include <tuple>
#include <unordered_map>

#include "fintamath/core/Hash.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath::detail {

template <typename Signature>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> final {
  template <typename>
  using ArgId = MathObjectClass;

  using CallbackId = std::tuple<ArgId<ArgsBase>...>;

  using Callback = std::function<Res(ArgsBase...)>;

  using IdToCallbackMap = std::unordered_map<CallbackId, Callback, Hash<CallbackId>>;

public:
  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  void add(auto callback) {
    constexpr CallbackId callbackId = {Args::getClassStatic()...};

    idToCallbackMap[callbackId] = [callback = std::move(callback)](ArgsBase... args) {
      return callback(cast<Args>(std::forward<ArgsBase>(args))...);
    };
  }

  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  std::optional<Res> operator()(Args &&...args) const {
    constexpr CallbackId callbackId = {Args::getClassStatic()...};

    if (auto iter = idToCallbackMap.find(callbackId); iter != idToCallbackMap.end()) {
      return iter->second(std::forward<Args>(args)...);
    }

    return {};
  }

private:
  IdToCallbackMap idToCallbackMap;
};

}
