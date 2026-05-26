#pragma once

namespace codility {

// Returns the longest run of zero bits surrounded by one bits in number.
// Time complexity: O(log n), proportional to the number of bits inspected.
// Space complexity: O(1).
int binary_gap(int number);

} // namespace codility
