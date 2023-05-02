#ifndef AVX512_BENCH_COMMON
#define AVX512_BENCH_COMMON

#include <benchmark/benchmark.h>
#include "rand_array.h"
#include "cpuinfo.h"
#include "avx512-16bit-qsort.hpp"
#include "avx512-32bit-qsort.hpp"
#include "avx512-64bit-qsort.hpp"

#define MY_BENCHMARK_CAPTURE(func, T, test_case_name, ...) \
    BENCHMARK_PRIVATE_DECLARE(func) \
            = (::benchmark::internal::RegisterBenchmarkInternal( \
                    new ::benchmark::internal::FunctionBenchmark( \
                            #func "/" #test_case_name "/" #T, \
                            [](::benchmark::State &st) { \
                                func<T>(st, __VA_ARGS__); \
                            })))

#define BENCH(func, type) \
    MY_BENCHMARK_CAPTURE( \
            func, type, random_10000, 10000, std::string("random")); \
    MY_BENCHMARK_CAPTURE( \
            func, type, random_100000, 100000, std::string("random")); \
    MY_BENCHMARK_CAPTURE( \
            func, type, sorted_10000, 10000, std::string("sorted")); \
    MY_BENCHMARK_CAPTURE( \
            func, type, constant_10000, 10000, std::string("constant")); \
    MY_BENCHMARK_CAPTURE( \
            func, type, reverse_10000, 10000, std::string("reverse"));


#endif
