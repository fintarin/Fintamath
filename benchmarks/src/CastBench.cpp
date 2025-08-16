#include <benchmark/benchmark.h>

#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

static void BM_FintamathCast(benchmark::State &state) {
  Integer integ = 1;
  IMathObject* obj = &integ;

  for (auto _ : state) {
    benchmark::DoNotOptimize(cast<Integer>(obj));
    benchmark::DoNotOptimize(cast<INumber>(obj));
    benchmark::DoNotOptimize(cast<IArithmetic>(obj));
  }
}

static void BM_DynamicCast(benchmark::State &state) {
  Integer integ = 1;
  IMathObject* obj = &integ;

  for (auto _ : state) {
    benchmark::DoNotOptimize(dynamic_cast<Integer*>(obj));
    benchmark::DoNotOptimize(dynamic_cast<INumber*>(obj));
    benchmark::DoNotOptimize(dynamic_cast<IArithmetic*>(obj));
  }
}

BENCHMARK(BM_FintamathCast);
BENCHMARK(BM_DynamicCast);

BENCHMARK_MAIN();
