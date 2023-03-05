#pragma once

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IIncremental;
using IncrementalPtr = std::unique_ptr<IIncremental>;

class IIncremental : virtual public IArithmetic {
public:
  friend inline IIncremental &operator++(IIncremental &rhs) {
    return rhs.increaseAbstract();
  }

  friend inline IIncremental &operator--(IIncremental &rhs) {
    return rhs.decreaseAbstract();
  }

  friend inline IncrementalPtr operator++(IIncremental &lhs, int) {
    auto res = cast<IIncremental>(lhs.clone());
    lhs.increaseAbstract();
    return res;
  }

  friend inline IncrementalPtr operator--(IIncremental &lhs, int) {
    auto res = cast<IIncremental>(lhs.clone());
    lhs.decreaseAbstract();
    return res;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IIncremental, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static IncrementalPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual IIncremental &increaseAbstract() = 0;

  virtual IIncremental &decreaseAbstract() = 0;

private:
  static Parser::Vector<IncrementalPtr, const std::string &> parserVector;
};

template <typename Derived>
class IIncrementalCRTP : virtual public IArithmeticCRTP<Derived>, virtual public IIncremental {
public:
  Derived &operator++() {
    return increase();
  }

  Derived &operator--() {
    return decrease();
  }

  Derived operator++(int) {
    auto res = Derived(cast<Derived>(*this));
    increase();
    return res;
  }

  Derived operator--(int) {
    auto res = Derived(cast<Derived>(*this));
    decrease();
    return res;
  }

protected:
  virtual Derived &increase() = 0;

  virtual Derived &decrease() = 0;

  IIncremental &increaseAbstract() final {
    increase();
    return *this;
  }

  IIncremental &decreaseAbstract() final {
    decrease();
    return *this;
  }
};

}
