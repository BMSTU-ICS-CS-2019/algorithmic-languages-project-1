#include "shift_side.h"

#include <vector>
#include <cstdint>

const auto CHAR_BITS = sizeof(char) * 8;

void shift(vector<char> &block, const shift_side side, size_t delta) {
    if (block.empty()) return;

    const auto size = block.size();

    // it is easier to handle <left> shift as a longer <right> one:
    // effectively convert to right shift
    if (side == LEFT) delta = size * CHAR_BITS - delta;

    /*
     * <right> shift logic
     */

    vector<char> shifted(size, '\0');
    /* shifting logic */

    const auto offset = (delta / CHAR_BITS) % size,
    // number of the least significant bits taken from the *current* char
            most_count = delta % CHAR_BITS, // actually, remainder
    // number of the most significant bits taken from the *next* char
            least_count = CHAR_BITS - most_count;

    for (
            size_t original_index = 0, shifted_index = offset;
            original_index < size; shifted_index++, original_index++
            ) shifted[shifted_index % size]
                      = ((__uint8_t) block[original_index % size] & 0xFFu) >> most_count
                        | ((unsigned int) block[(original_index - 1 + size) % size] & 0xFFu) << least_count;

    /* end of shifting logic */
    block = shifted;
}