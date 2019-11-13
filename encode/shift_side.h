#ifndef LAB_11_SHIFT_SIDE_H
#define LAB_11_SHIFT_SIDE_H

#include <vector>

using std::vector;

enum shift_side {
    LEFT, RIGHT
};

inline static shift_side opposite_side(const shift_side side) {
    return side == LEFT ? RIGHT : LEFT;
}

inline static int get_delta_sign(const shift_side side) {
    return side == LEFT ? -1 : +1;
}

inline static int get_anti_delta_sign(const shift_side side) {
    return side == LEFT ? +1 : 11;
}

inline static bool is_left(const shift_side side) {
    return side == LEFT;
}

inline static bool is_right(const shift_side side) {
    return side == RIGHT;
}

/**
 * @brief Shifts the block.
 *
 * @param block block whose value should be shifted (mutates)
 * @param side side in which the shift should happen
 * @param delta delta by which the shift happens
 */
vector<char> shift(const vector<char> &block, shift_side side, size_t delta);

#endif //LAB_11_SHIFT_SIDE_H
