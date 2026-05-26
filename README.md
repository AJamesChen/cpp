# cpp

Modern C++ practice project using CMake, GoogleTest, clang-format, clang-tidy, and GitHub Actions.

Problem notes and complexity documentation live under `docs/`.

## Requirements

Install the build tools:

```bash
sudo apt-get update
sudo apt-get install -y cmake g++ ninja-build
```

Optional tools for local formatting and static analysis:

```bash
sudo apt-get install -y clang-format clang-tidy clang-tools
```

## Configure

Configure the project with CMake:

```bash
cmake -S . -B build -G Ninja
```

CMake downloads GoogleTest automatically during configuration.

## Build

Build the project:

```bash
cmake --build build
```

## Run Tests

Run the GoogleTest suite through CTest:

```bash
ctest --test-dir build --output-on-failure
```

Unit tests should only verify correctness. Performance measurement code belongs under `benchmarks/`.

## Run Benchmarks

Configure with benchmark targets enabled:

```bash
cmake -S . -B build-bench -G Ninja -DBUILD_BENCHMARKS=ON -DBUILD_TESTING=OFF
```

Build and run the benchmark executable:

```bash
cmake --build build-bench --target binary_gap_benchmark
./build-bench/binary_gap_benchmark
```

## Format Check

Check formatting without changing files:

```bash
find include src tests benchmarks \( -name '*.h' -o -name '*.hpp' -o -name '*.cpp' \) -print0 \
  | xargs -0 clang-format --dry-run --Werror
```

Format files in place:

```bash
find include src tests benchmarks \( -name '*.h' -o -name '*.hpp' -o -name '*.cpp' \) -print0 \
  | xargs -0 clang-format -i
```

## Static Analysis

Configure a compile database without tests:

```bash
cmake -S . -B build-tidy -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTING=OFF
```

Run clang-tidy on project sources:

```bash
clang-tidy -p build-tidy src/codility/binary_gap.cpp
```

## Continuous Integration

GitHub Actions runs separate workflows for:

- Build and unit tests
- clang-format
- clang-tidy
