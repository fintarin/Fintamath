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
  using ArgId = MathObjectTypeId;

  using CallbackId = std::tuple<ArgId<ArgsBase>...>;

  using Callback = std::function<Res(const ArgsBase &...)>;

  using Callbacks = std::map<CallbackId, Callback>;

public:
  template <typename... Args, typename Func>
  void add(const Func &func) {
    callbacks[CallbackId(Args::getTypeIdStatic()...)] = [func](const ArgsBase &...args) {
      return func(cast<Args>(args)...);
    };
  }

  template <typename... Args>
  Res operator()(const Args &...args) const {
    auto it = callbacks.find(CallbackId(args.getTypeId()...));

    if (it != callbacks.end()) {
      return it->second(args...);
    }

    return {};
  }

private:
  Callbacks callbacks;
};

}
