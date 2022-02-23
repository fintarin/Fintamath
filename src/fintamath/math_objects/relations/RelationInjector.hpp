#pragma once

#define INJECT_UNARY_RELATION(TYPE, SET)                                                                               \
  {                                                                                                                    \
    auto rhs = std::dynamic_pointer_cast<TYPE>((SET).at(0));                                                           \
    if (rhs) {                                                                                                         \
      return {(*this)(*rhs)};                                                                                          \
    }                                                                                                                  \
  }

#define INJECT_UNARY_RELATION_PRECISION(TYPE, SET, PRECISION)                                                          \
  {                                                                                                                    \
    auto rhs = std::dynamic_pointer_cast<TYPE>((SET).at(0));                                                           \
    if (rhs) {                                                                                                         \
      return {(*this)(*rhs, PRECISION)};                                                                               \
    }                                                                                                                  \
  }

#define INJECT_BINARY_RELATION(LHS_TYPE, RHS_TYPE, SET)                                                                \
  {                                                                                                                    \
    auto lhs = std::dynamic_pointer_cast<LHS_TYPE>((SET).at(0));                                                       \
    auto rhs = std::dynamic_pointer_cast<RHS_TYPE>((SET).at(1));                                                       \
    if (lhs && rhs) {                                                                                                  \
      return {(*this)(*lhs, *rhs)};                                                                                    \
    }                                                                                                                  \
  }

#define INJECT_BINARY_RELATION_PRECISION(LHS_TYPE, RHS_TYPE, SET, PRECISION)                                           \
  {                                                                                                                    \
    auto lhs = std::dynamic_pointer_cast<LHS_TYPE>((SET).at(0));                                                       \
    auto rhs = std::dynamic_pointer_cast<RHS_TYPE>((SET).at(1));                                                       \
    if (lhs && rhs) {                                                                                                  \
      return {(*this)(*lhs, *rhs, PRECISION)};                                                                         \
    }                                                                                                                  \
  }
