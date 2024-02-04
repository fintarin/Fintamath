#pragma once

#include <functional>
#include <map>
#include <tuple>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/MathObjectTypes.hpp"

namespace fintamath {

template <typename Signature>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> final {
  template <typename>
  using ArgId = MathObjectType;

  using CallbackId = std::tuple<ArgId<ArgsBase>...>;

  using Callback = std::function<Res(const ArgsBase &...)>;

  using Callbacks = std::map<CallbackId, Callback>;

public:
  template <typename... Args>
  void add(const auto &func) {
    callbacks[CallbackId(Args::getTypeStatic()...)] = [func](const ArgsBase &...args) {
      return func(cast<Args>(args)...);
    };
  }

  Res operator()(const auto &...args) const {
    if (auto iter = callbacks.find(CallbackId(args.getType()...)); iter != callbacks.end()) {
      return iter->second(args...);
    }

    return {};
  }

  bool contains(const auto &...args) const {
    return callbacks.contains(CallbackId(args.getType()...));
  }

private:
  Callbacks callbacks;
};

}
