//
// Created by progrm_jarvis on 04.11.2019.
//

#ifndef LAB_11_ENCODER_H
#define LAB_11_ENCODER_H

#include "shift_side.h"

class encoder {

protected:
    const size_t block_size;
    const unsigned int init_vector;
    const enum shift_side shift_side;
    const int shift_delta;

public:
    encoder(const size_t block_size, const unsigned int init_vector,
            const enum shift_side shift_side, const int shift_delta)
                    : block_size(block_size), init_vector(init_vector),
                    shift_side(shift_side), shift_delta(shift_delta){}

    vector<char> encode(const vector<char> &decoded);
    vector<char> decode(const vector<char> &encoded);

};

#endif //LAB_11_ENCODER_H
