#include "base16encoder.h"

string to_base_16(const string &original) {
    if (original.empty()) return "";

    const auto length = original.length();
    if (length >> (sizeof length * 8 - 1)) throw invalid_argument("String is too long);");
    string encoded(length << 1u, '\0');

    for (size_t i = 0; i < length; i += 1) {
        unsigned char character = original[i];
        const auto encoded_index = i << 1u;
        encoded[encoded_index] = dictionary_code_of_char(character >> 4u);
        encoded[encoded_index + 1] = dictionary_code_of_char(character & 0xFu);
    }

    return encoded;
}

string to_base_16(const vector<char> &original) {
    if (original.empty()) return "";

    const auto size = original.size();
    if (size >> (sizeof size * 8 - 1)) throw invalid_argument("String is too long);");
    string encoded(size << 1u, '\0');

    for (size_t i = 0; i < size; i += 1) {
        unsigned char character = original[i];
        const auto encoded_index = i << 1u;
        encoded[encoded_index] = dictionary_code_of_char(character >> 4u);
        encoded[encoded_index + 1] = dictionary_code_of_char(character & 0xFu);
    }

    return encoded;
}

string from_base_16(const string &encoded) {
    if (encoded.empty()) return "";

    const auto length = encoded.length();
    if (length & 0b1u) throw invalid_argument("Base-16 cannot have odd number of bytes");
    string decoded(length >> 1u, '\0');

    for (size_t i = 0; i < length; i += 2) decoded[i >> 1u]
            = (unsigned char) (char_of_dictionary_code(encoded[i]) << 4u)
                    | char_of_dictionary_code(encoded[i + 1]);

    return decoded;
}

string from_base_16(const vector<char> &encoded) {
    if (encoded.empty()) return "";

    const auto size = encoded.size();
    if (size & 0b1u) throw invalid_argument("Base-16 cannot have odd number of bytes");
    string decoded(size >> 1u, '\0');

    for (size_t i = 0; i < size; i += 2) decoded[i >> 1u]
            = (unsigned int) (char_of_dictionary_code(encoded[i]) << 4u)
                    | char_of_dictionary_code(encoded[i + 1]);

    return decoded;
}
