#pragma once

#define INJECT_PARSER(PARSER, STRING)                                                                                  \
  {                                                                                                                    \
    if (auto res = PARSER::parse(STRING); res) {                                                                       \
      return res;                                                                                                      \
    }                                                                                                                  \
  }

#define INJECT_CONSTRUCTOR(CLASS_TYPE, STRING)                                                                         \
  {                                                                                                                    \
    try {                                                                                                              \
      return std::make_unique<CLASS_TYPE>(STRING);                                                                     \
    } catch (const std::invalid_argument &) {                                                                          \
      /* do nothing */                                                                                                 \
    }                                                                                                                  \
  }
