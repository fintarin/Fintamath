#pragma once

#include <memory>

#include "fintamath/exceptions/NullPointerException.hpp"

namespace fintamath {

template <typename T>
class Pointer;

template <typename Ptr>
class Reference {
public:
  using ElementType = Ptr::element_type;

private:
  Reference(const Ptr &inPtr) : ptr(inPtr) {}

  Reference(Ptr &&inPtr) : ptr(std::move(inPtr)) {}

public:
  template <typename T>
  Reference(const Reference<T> &rhs) noexcept : ptr(rhs.ptr) {}

  template <typename T>
  Reference(Reference<T> &&rhs) noexcept : ptr(std::move(rhs).ptr) {}

  Reference(const Reference &rhs) noexcept = default;

  Reference(Reference &&) noexcept = default;

  Reference &operator=(const Reference &) noexcept = default;

  Reference &operator=(Reference &&) noexcept = default;

  decltype(auto) operator*() const noexcept {
    return *ptr;
  }

  decltype(auto) operator->() const noexcept {
    return ptr.operator->();
  }

  decltype(auto) get() const noexcept {
    return ptr.get();
  }

  template <typename Lhs, typename Rhs>
  friend bool operator==(const Reference<Lhs> &lhs, const Reference<Rhs> &rhs) noexcept;

  template <typename Lhs, typename Rhs>
  friend bool operator==(const Pointer<Lhs> &lhs, const Reference<Rhs> &rhs) noexcept;

  template <typename To, typename From>
  friend Reference<std::shared_ptr<To>> staticPointerCast(const Reference<From> &from) noexcept;

  template <typename T, typename... Args>
  friend Reference<std::unique_ptr<T>> makeUnique(Args &&...args);

  template <typename T, typename... Args>
  friend Reference<std::shared_ptr<T>> makeShared(Args &&...args);

private:
  template <typename T>
  friend class Reference;

  template <typename T>
  friend class Pointer;

private:
  Ptr ptr;
};

template <typename Ptr>
class Pointer {
public:
  using ElementType = Ptr::element_type;

private:
  Pointer(const Ptr &inPtr) : ptr(inPtr) {}

  Pointer(Ptr &&inPtr) : ptr(std::move(inPtr)) {}

public:
  Pointer() noexcept = default;

  Pointer(std::nullptr_t) noexcept : ptr(nullptr){};

  template <typename T>
  Pointer(const Pointer<T> &rhs) noexcept : ptr(rhs.ptr) {}

  template <typename T>
  Pointer(Pointer<T> &&rhs) noexcept : ptr(std::move(rhs).ptr) {}

  template <typename T>
  Pointer(const Reference<T> &rhs) noexcept : ptr(rhs.ptr) {}

  template <typename T>
  Pointer(Reference<T> &&rhs) noexcept : ptr(std::move(rhs).ptr) {}

  Pointer(const Pointer &rhs) noexcept = default;

  Pointer(Pointer &&) noexcept = default;

  Pointer &operator=(const Pointer &) noexcept = default;

  Pointer &operator=(Pointer &&) noexcept = default;

  decltype(auto) operator*() const noexcept {
    return *ptr;
  }

  decltype(auto) operator->() const noexcept {
    return ptr.operator->();
  }

  decltype(auto) get() const noexcept {
    return ptr.get();
  }

  operator bool() const noexcept {
    return ptr.operator bool();
  }

  Reference<Ptr> toRef() const & {
    if (!ptr) {
      throw NullPointerException();
    }
    return ptr;
  }

  Reference<Ptr> toRef() && {
    if (!ptr) {
      throw NullPointerException();
    }
    return std::move(ptr);
  }

  template <typename Lhs, typename Rhs>
  friend bool operator==(const Pointer<Lhs> &lhs, const Pointer<Rhs> &rhs) noexcept;

  template <typename Lhs, typename Rhs>
  friend bool operator==(const Pointer<Lhs> &lhs, const Reference<Rhs> &rhs) noexcept;

  template <typename To, typename From>
  friend Pointer<std::shared_ptr<To>> staticPointerCast(const Pointer<From> &from) noexcept;

private:
  template <typename Self>
  static Reference<Ptr> toRef(Self &&self) {
    if (!self.ptr) {
      throw NullPointerException();
    }
    return std::forward<Self>(self).ptr;
  }

  template <typename T>
  friend class Reference;

  template <typename T>
  friend class Pointer;

private:
  Ptr ptr;
};

template <typename Lhs, typename Rhs>
inline bool operator==(const Reference<Lhs> &lhs, const Reference<Rhs> &rhs) noexcept {
  return lhs.ptr == rhs.ptr;
}

template <typename Lhs, typename Rhs>
bool operator==(const Pointer<Lhs> &lhs, const Pointer<Rhs> &rhs) noexcept {
  return lhs.ptr == rhs.ptr;
}

template <typename Lhs, typename Rhs>
inline bool operator==(const Pointer<Lhs> &lhs, const Reference<Rhs> &rhs) noexcept {
  return lhs.ptr == rhs.ptr;
}

template <typename To, typename From>
inline Reference<std::shared_ptr<To>> staticPointerCast(const Reference<From> &from) noexcept {
  return std::static_pointer_cast<To>(from.ptr);
}

template <typename To, typename From>
inline Pointer<std::shared_ptr<To>> staticPointerCast(const Pointer<From> &from) noexcept {
  return std::static_pointer_cast<To>(from.ptr);
}

template <typename T, typename... Args>
inline Reference<std::unique_ptr<T>> makeUnique(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline Reference<std::shared_ptr<T>> makeShared(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using UniqueRef = Reference<std::unique_ptr<T>>;

template <typename T>
using UniquePtr = Pointer<std::unique_ptr<T>>;

template <typename T>
using SharedRef = Reference<std::shared_ptr<const T>>;

template <typename T>
using SharedPtr = Pointer<std::shared_ptr<const T>>;

}
