#include "encoder.h"

#include "shift_side.h"
#include "string_utils.h"
#include "debug.h"

#include <random>

using std::default_random_engine;

static vector<char> next_delta(default_random_engine &random_engine, size_t block_size);

static void encode_block(vector<char> &block, const vector<char> &delta,
                         shift_side shift_side, size_t shift_delta);

static void decode_block(vector<char> &block, const vector<char> &delta,
                         shift_side shift_side, size_t shift_delta);

vector<char> encoder::encode(const vector<char> &decoded) {
    debug_bits("Encoding: ", decoded);
    const auto size = decoded.size();
    vector<char> encoded(size % block_size ? size / block_size * block_size + block_size : size);
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
    debug_bits(" Encoded: ", encoded);

    return encoded;
}

vector<char> encoder::decode(const vector<char> &encoded) {
    debug_bits("Decoding: ", encoded);
    vector<char> decoded(encoded.size());
    {
        auto iterator = decoded.begin();
        default_random_engine random_engine(init_vector);
        for (auto &block : split(encoded, block_size)) {
            decode_block(
                    block, next_delta(random_engine, block_size),
                    shift_side, shift_delta
            );
            for (auto &character : block) *(iterator++) = character;
        }
    }
    debug_bits(" Decoded: ", decoded);

    return decoded;
}

static vector<char> next_delta(default_random_engine &random_engine, const size_t block_size) {
    vector<char> delta;
    for (size_t i = 0; i < block_size; i++) {
        std::uniform_int_distribution<> range{0, 0xFF - 1};

        char v = range(random_engine);
        delta.push_back(v);
    }

    debug_bits("\tGot delta: ", delta);

    return delta;
}

static void encode_block(vector<char> &block, const vector<char> &delta,
                         const shift_side shift_side, const size_t shift_delta) {
    debug_bits("\t Encoding block: ", block);
    debug_bits("\t     With delta: ", delta);
    {
        auto delta_iterator = delta.begin();
        for (auto &element : block) element = ((unsigned char) element) ^ ((unsigned char) *(delta_iterator++));
    }
    shift(block, shift_side, shift_delta);
    debug_bits("\t  Decoded block: ", block);
}

static void decode_block(vector<char> &block, const vector<char> &delta,
                         const shift_side shift_side, const size_t shift_delta) {
    debug_bits("\t Decoding block: ", block);
    debug_bits("\t     With delta: ", delta);
    shift(block, opposite_side(shift_side), shift_delta);
    {
        auto delta_iterator = delta.begin();
        for (auto &element : block) element = ((unsigned char) element) ^ ((unsigned char) *(delta_iterator++));
        debug_bits("\t  Decoded block: ", block);
    }
}