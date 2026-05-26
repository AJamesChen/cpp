#include "codility/binary_gap.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

namespace {

std::vector<int> make_inputs() {
    constexpr int input_count = 1'000'000;
    constexpr std::int64_t multiplier = 1'103'515'245;
    constexpr std::int64_t increment = 12'345;
    constexpr std::int64_t modulus = 1LL << 31;

    std::vector<int> inputs;
    inputs.reserve(input_count);

    std::int64_t value = 1;
    for (int index = 0; index < input_count; ++index) {
        value = (value * multiplier + increment) % modulus;
        inputs.push_back(static_cast<int>(value));
    }

    return inputs;
}

} // namespace

int main() {
    const auto inputs = make_inputs();

    const auto start = std::chrono::steady_clock::now();
    const auto checksum =
        std::accumulate(inputs.begin(), inputs.end(), 0LL,
                        [](long long sum, int value) { return sum + codility::binary_gap(value); });
    const auto stop = std::chrono::steady_clock::now();

    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "binary_gap inputs=" << inputs.size() << " checksum=" << checksum
              << " elapsed_us=" << elapsed.count() << '\n';
}
