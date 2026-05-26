# Binary Gap

## Problem

Given a positive integer, return the longest sequence of consecutive zero bits that is surrounded by one bits in the integer's binary representation.

Examples:

- `9` is `1001`, so the longest binary gap is `2`.
- `529` is `1000010001`, so the longest binary gap is `4`.
- `20` is `10100`, so the longest binary gap is `1`.
- `15` is `1111`, so the longest binary gap is `0`.
- `32` is `100000`, so the longest binary gap is `0`.

## Complexity

The implementation scans the bits of the input once.

- Time complexity: `O(log n)`, proportional to the number of bits in `n`.
- Space complexity: `O(1)`.

## Testing

Correctness tests live in `tests/codility/test_binary_gap.cpp`.

Run them with:

```bash
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

## Benchmarking

Performance measurement code belongs in `benchmarks/`, not in normal unit tests.

Run the binary gap benchmark with:

```bash
cmake -S . -B build-bench -G Ninja -DBUILD_BENCHMARKS=ON -DBUILD_TESTING=OFF
cmake --build build-bench --target binary_gap_benchmark
./build-bench/binary_gap_benchmark
```
