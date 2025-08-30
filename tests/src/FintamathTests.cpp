#include <fmt/core.h>
#include <gtest/gtest.h>

#include <fstream>
#include <thread>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

TEST(FintamathTests, fintamathTest1) {
  static const Real step("0.001");
  static const Real start("-5");
  static const Real end("5");
  static constexpr size_t threadNum = 16;

  std::vector<std::thread> threads;
  threads.reserve(threadNum);

  std::vector<std::vector<std::string>> allResults(threadNum);

  for (size_t i = 0; i < threadNum; i++) {
    threads.emplace_back([i, &allResults] {
      std::vector<std::string> results;
      Real newStart = start + (end - start) * i / threadNum;
      Real newEnd = start + (end - start) * (i + 1) / threadNum;
      for (Real r = newStart; r <= newEnd; r += step) {
        if (r < step) {
          r = 0;
        }

        Real value = sin(r);
        results.emplace_back(fmt::format(R"({}, {})", r.toString(), value.toString()));
      }

      allResults[i] = std::move(results);
    });
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::ofstream stream("/home/fintarin/Projects/Fintamath/data.txt");

  for (const auto &results : allResults) {
    for (const auto &result : results) {
      stream << result << '\n';
    }
  }
}

TEST(FintamathTests, fintamathTest2) {
  static const Real step("0.001");
  static const Real start("-5");
  static const Real end("5");
  static constexpr size_t threadNum = 16;

  std::vector<std::thread> threads;
  threads.reserve(threadNum);

  std::vector<std::vector<std::string>> allResults(threadNum);

  for (size_t i = 0; i < threadNum; i++) {
    threads.emplace_back([i, &allResults] {
      std::vector<std::string> results;
      Real newStart = start + (end - start) * i / threadNum;
      Real newEnd = start + (end - start) * (i + 1) / threadNum;
      for (Real r = newStart; r <= newEnd; r += step) {
        if (r < step) {
          r = 0;
        }

        Expression expr = {Sin::make({r.clone()})};

        std::string value = approximate(expr).toString();
        results.emplace_back(fmt::format(R"({}, {})", r.toString(), value));
      }

      allResults[i] = std::move(results);
    });
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::ofstream stream("/home/fintarin/Projects/Fintamath/data.txt");

  for (const auto &results : allResults) {
    for (const auto &result : results) {
      stream << result << '\n';
    }
  }
}
