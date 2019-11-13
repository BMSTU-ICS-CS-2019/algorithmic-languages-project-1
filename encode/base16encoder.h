#ifndef LAB_11_BASE16ENCODER_H
#define LAB_11_BASE16ENCODER_H

#include <string>
#include <vector>

#include "stdexcept"

using std::invalid_argument;

using std::string;
using std::vector;

const static int DICTIONARY_SIZE = 0x10;

static const unsigned char DICTIONARY_ROOT = 'A',
DICTIONARY[DICTIONARY_SIZE] = {
        DICTIONARY_ROOT + 0x0, DICTIONARY_ROOT + 0x1,
        DICTIONARY_ROOT + 0x2, DICTIONARY_ROOT + 0x3,
        DICTIONARY_ROOT + 0x4, DICTIONARY_ROOT + 0x5,
        DICTIONARY_ROOT + 0x6, DICTIONARY_ROOT + 0x7,
        DICTIONARY_ROOT + 0x8, DICTIONARY_ROOT + 0x9,
        DICTIONARY_ROOT + 0xA, DICTIONARY_ROOT + 0xB,
        DICTIONARY_ROOT + 0xC, DICTIONARY_ROOT + 0xD,
        DICTIONARY_ROOT + 0xE, DICTIONARY_ROOT + 0xF,
},
DICTIONARY_FIRST_ELEMENT = DICTIONARY[0],
DICTIONARY_LAST_ELEMENT = DICTIONARY[DICTIONARY_SIZE - 1];

inline static unsigned char dictionary_code_of_char(const unsigned char character) {
    if (character & 0xF0u) throw invalid_argument("Character should have the maximal value of 0xF");

    return DICTIONARY[character];
}

inline static unsigned char char_of_dictionary_code(const unsigned char character) {
    if (character < DICTIONARY_FIRST_ELEMENT || character > DICTIONARY_LAST_ELEMENT) throw invalid_argument(
            "Base-16 cannot contain the given character"
    );

    return character - DICTIONARY_ROOT;
}

/**
 * @brief Converts the given string into base-16 representation from its normal representation.
 * @param original string
 * @return base-16 encoded string
 */
string to_base_16(const string &original);

/**
 * @brief Converts the given string into base-16 representation from its normal representation.
 * @param original string
 * @return base-16 encoded string
 */
string to_base_16(const vector<char> &original);

/**
 * @brief Converts the given string from base-16 representation into a normal one.
 * @param base-16 encoded string
 * @return decoded string
 */
string from_base_16(const string &encoded);

/**
 * @brief Converts the given string from base-16 representation into a normal one.
 * @param base-16 encoded string
 * @return decoded string
 */
string from_base_16(const vector<char> &encoded);

#endif //LAB_11_BASE16ENCODER_H
