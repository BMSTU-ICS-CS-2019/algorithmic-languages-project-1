#include "encoder.h"

#include "shift_side.h"
#include "string_utils.h"

#include <bitset>
#include <iostream>
#include <random>

using std::default_random_engine;

static vector<char> next_delta(const default_random_engine &random_engine, size_t block_size);

static void encode_block(vector<char> &block, const vector<char> &delta,
                         shift_side shift_side, size_t shift_delta);

static void decode_block(vector<char> &block, const vector<char> &delta,
                         shift_side shift_side, size_t shift_delta);

vector<char> encoder::encode(const vector<char> &decoded) {
    vector<char> encoded(decoded.size());
    {
        default_random_engine random_engine(init_vector);

        auto iterator = encoded.begin();
        for (auto &block : split(decoded, block_size)) {
            encode_block(
                    block, next_delta(random_engine, block_size),
                    shift_side, shift_delta
            );
            for (auto &character : block) *(iterator++) = character;
        }
    }

    for (char s : encoded) std::cout << std::bitset<8>(s) << "(" << s << ") ";
    std::cout << std::endl;

    return encoded;
}

vector<char> encoder::decode(const vector<char> &encoded) {
    for (char s : encoded) std::cout << std::bitset<8>(s) << "(" << s << ") ";
    std::cout << std::endl;

    vector<char> decoded(encoded.size());
    {
        auto iterator = decoded.begin();
        default_random_engine random_engine(init_vector);
        for (auto &block : split(encoded, block_size)) {
            // std::cout << "Decoding block <" << block << ">" << std::endl;
            decode_block(
                    block, next_delta(random_engine, block_size),
                    shift_side, shift_delta
            );
            for (auto &character : block) *(iterator++) = character;
        }
    }

    std::cout << std::endl;

    return decoded;
}

static vector<char> next_delta(const default_random_engine &random_engine, const size_t block_size) {
    vector<char> delta;
    for (size_t i = 0; i < block_size; i++) {
        std::uniform_int_distribution<> range{0, 0xFF};
        default_random_engine rng = random_engine; // FIXME
        char v = range(rng);
        std::cout << "\tv= " << (int) v << std::endl;
        delta.push_back(v);
    }

    return delta;
}

static void encode_block(vector<char> &block, const vector<char> &delta,
                         const shift_side shift_side, const size_t shift_delta) {
    {
        auto delta_iterator = delta.begin();
        for (auto &element : block) element ^= delta[*(delta_iterator++)];
    }
    block = shift(block, shift_side, shift_delta);
}

static void decode_block(vector<char> &block, const vector<char> &delta,
                         const shift_side shift_side, const size_t shift_delta) {
    block = shift(block, opposite_side(shift_side), shift_delta);
    {
        auto delta_iterator = delta.begin();
        for (auto &element : block) element ^= delta[*(delta_iterator++)];
    }
}