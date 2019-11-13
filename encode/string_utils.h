#ifndef LAB_11_STRING_UTILS_H
#define LAB_11_STRING_UTILS_H

#include <string>
#include <vector>

using std::vector;
using std::string;

vector<char> to_vector(const string& source);

vector<char> from_vector(const string& source);

vector<vector<char>> split(const string &text, size_t block_length);

vector<vector<char>> split(const vector<char> &text, size_t block_length);

#endif //LAB_11_STRING_UTILS_H
