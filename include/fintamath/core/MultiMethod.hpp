#pragma once

#include <functional>
#include <map>
#include <tuple>

#include "fintamath/core/CoreUtils.hpp"

namespace fintamath {

template <typename Signature>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> {
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
    auto it = callbacks.find(CallbackId(args.getType()...));

    if (it != callbacks.end()) {
      return it->second(args...);
    }

    return {};
  }

private:
  Callbacks callbacks;
};

}
