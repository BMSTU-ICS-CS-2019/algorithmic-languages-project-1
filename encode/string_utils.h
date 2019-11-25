#ifndef LAB_11_STRING_UTILS_H
#define LAB_11_STRING_UTILS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<char> string_to_char_vector(const string &text, size_t initial_size);

inline vector<char> string_to_char_vector(const string &text) {
    return string_to_char_vector(text, text.length());
}

string char_vector_to_string(const vector<char> &text, size_t initial_size);

inline static string char_vector_to_string(const vector<char> &text) {
    return char_vector_to_string(text, 0);
}

inline static vector<vector<char>> split(const string &text, size_t block_length);

vector<vector<char>> split(const vector<char> &text, size_t block_length);

#endif //LAB_11_STRING_UTILS_H
