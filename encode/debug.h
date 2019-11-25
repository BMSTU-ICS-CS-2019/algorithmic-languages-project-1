
#ifndef LAB_11_TOS_H
#define LAB_11_TOS_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using std::clog;
using std::endl;
using std::vector;
using std::string;
using std::bitset;

void debug_bits(const string &prefix, const vector<char> &characters) {
#ifdef DEBUG
    clog << prefix;
    for (const auto &character : characters) clog << bitset<sizeof(char) * 8>(character) << " ";
    clog << endl;
#endif // DEBUG
}

#endif //LAB_11_TOS_H
