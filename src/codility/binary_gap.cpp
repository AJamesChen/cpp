#include "codility/binary_gap.hpp"

#include <algorithm>

namespace codility {

int binary_gap(int number) {
    int max_gap = 0;
    int current_gap = 0;
    bool started = false;

    while (number > 0) {
        if ((number & 1) != 0) {
            if (started) {
                max_gap = std::max(max_gap, current_gap);
            }
            started = true;
            current_gap = 0;
        } else if (started) {
            ++current_gap;
        }

        number >>= 1;
    }

    return max_gap;
}

} // namespace codility
