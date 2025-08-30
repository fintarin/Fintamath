// #include <fmt/core.h>
// #include <gtest/gtest.h>

// #include <fstream>

// #include "fintamath/numbers/Real.hpp"
// #include "fintamath/numbers/RealFunctions.hpp"

// using namespace fintamath;

// TEST(FintamathTests, fintamathTest) {
//   Real::setPrecisionStatic(20);
//   static const Real step("0.000001");
//   static const Real start("-5");
//   static const Real end("5");
//   static const size_t threadNum = 1;

//   static std::mutex mtx;

//   static std::ofstream stream("/home/fintarin/Projects/Fintamath/data.txt");

//   std::vector<std::thread> threads;

//   for (size_t i = 0; i < threadNum; i++) {
//     threads.emplace_back([i] {
//       std::vector<std::string> results;
//       Real newStart = start + (end - start) * i / threadNum;
//       Real newEnd = start + (end - start) * (i + 1) / threadNum;
//       for (Real r = newStart; r <= newEnd; r += step) {
//         try {
//           Real value = sin(r);
//           results.emplace_back(fmt::format(R"({}, {})", r.toString(), value.toString()));
//         }
//         catch (...) {
//           results.emplace_back(fmt::format(R"({}, {})", r.toString(), "---"));
//         }
//       }

//       std::lock_guard<std::mutex> lock(mtx);

//       for (const auto &result : results) {
//         stream << result << std::endl;
//       }
//     });
//   }

//   for (auto &thread : threads) {
//     thread.join();
//   }
// }
