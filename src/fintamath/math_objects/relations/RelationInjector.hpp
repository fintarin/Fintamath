#pragma once

#define INJECT_UNARY_RELATION(RHS_TYPE, SET)                                                                           \
  {                                                                                                                    \
    auto rhs = std::dynamic_pointer_cast<RHS_TYPE>((SET).at(0));                                                       \
    if (rhs) {                                                                                                         \
      return (*this)(*rhs);                                                                                            \
    }                                                                                                                  \
  }

#define INJECT_BINARY_RELATION(LHS_TYPE, RHS_TYPE, SET)                                                                \
  {                                                                                                                    \
    auto lhs = std::dynamic_pointer_cast<LHS_TYPE>((SET).at(0));                                                       \
    auto rhs = std::dynamic_pointer_cast<RHS_TYPE>((SET).at(1));                                                       \
    if (lhs && rhs) {                                                                                                  \
      return (*this)(*lhs, *rhs);                                                                                      \
    }                                                                                                                  \
  }
