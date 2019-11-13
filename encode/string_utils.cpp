#include "string_utils.h"

#include <bitset>

inline static vector<char> to_vector(const string &text, const size_t initial_size) {
    vector<char> characters(initial_size);
    std::copy(text.begin(), text.end(), characters.begin());

    return characters;
}

inline vector<char> to_vector(const string &text) {
    return to_vector(text, text.length());
}

inline static vector<char> from_vector(const string &text, const size_t initial_size) {
    vector<char> characters(initial_size);
    std::copy(text.begin(), text.end(), characters.begin());

    return characters;
}

inline vector<char> from_vector(const string &text) {
    return to_vector(text, text.length());
}

vector<vector<char>> split(const string &text, const size_t block_length) {
    const auto length = text.length(),
    full_blocks_count = length / block_length,
    full_blocks_length = full_blocks_count * block_length,
    extra_block_length = length - full_blocks_length,
    block_count = extra_block_length ? full_blocks_count + 1 : full_blocks_count;
    vector<vector<char>> blocks(block_count);

    for (size_t block_id = 0, text_index = 0; block_id < block_count;) {
        vector<char> block(block_length);
        for (size_t block_index = 0; block_index < block_length; block_index++) block[block_index] = text[text_index++];
        blocks[block_id++] = block;
    }

    return blocks;
}

vector<vector<char>> split(const vector<char> &text, const size_t block_length) {
    const auto size = text.size(),

    full_blocks_count = size / block_length,
    full_blocks_length = full_blocks_count * block_length,
    extra_block_length = size - full_blocks_length,
    block_count = extra_block_length ? full_blocks_count + 1 : full_blocks_count;
    vector<vector<char>> blocks(block_count);

    for (size_t block_id = 0, text_index = 0; block_id < block_count;) {
        vector<char> block(block_length);
        for (size_t block_index = 0; block_index < block_length; block_index++) block[block_index] = text[text_index++];
        blocks[block_id++] = block;
    }

    return blocks;
}
