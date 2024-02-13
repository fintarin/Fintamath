#pragma once

#include <functional>
#include <tuple>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/MathObjectTypes.hpp"

namespace fintamath::detail {

template <typename Signature>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> final {
  template <typename>
  using ArgId = MathObjectType;

  using CallbackId = std::tuple<ArgId<ArgsBase>...>;

  using Callback = std::function<Res(ArgsBase...)>;

  using IdToCallbackMap = std::unordered_map<CallbackId, Callback, boost::hash<CallbackId>>;

public:
  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  void add(const auto &func) {
    idToCallbackMap[CallbackId(Args::getTypeStatic()...)] = [func](const ArgsBase &...args) {
      return func(cast<Args>(args)...);
    };
  }

  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  Res operator()(Args &&...args) const {
    if (auto iter = idToCallbackMap.find(CallbackId(args.getType()...)); iter != idToCallbackMap.end()) {
      return iter->second(std::forward<Args>(args)...);
    }

    return {};
  }

  template <typename... Args>
    requires(sizeof...(Args) == sizeof...(ArgsBase))
  bool contains(const Args &...args) const {
    return idToCallbackMap.contains(CallbackId(args.getType()...));
  }

private:
  IdToCallbackMap idToCallbackMap;
};

}
