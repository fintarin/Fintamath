#pragma once

#include <functional>
#include <map>
#include <tuple>

#include "fintamath/helpers/TypeInfo.hpp"

namespace fintamath::helpers {

template <typename Signature>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> {
  template <typename>
  using ArgId = TypeInfo;
  using CallbackId = std::tuple<ArgId<ArgsBase>...>;
  using Callback = std::function<Res(const ArgsBase &...)>;
  using Callbacks = std::map<CallbackId, Callback>;

public:
  template <typename... Args, typename Func>
  void add(const Func &func) {
    callbacks[CallbackId(TypeInfo(typeid(Args))...)] = [func](const ArgsBase &...args) {
      return func(dynamic_cast<const Args &>(args)...);
    };
  }

  template <typename... Args>
  Res operator()(const Args &...args) const {
    auto it = callbacks.find(CallbackId(TypeInfo(typeid(args))...));
    if (it != callbacks.end()) {
      return it->second(args...);
    }
    return {};
  }

private:
  Callbacks callbacks;
};

}
