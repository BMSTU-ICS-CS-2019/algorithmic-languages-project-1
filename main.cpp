#include <iostream>

#include "encode/encoder.h"
#include "encode/string_utils.h"
#include "encode/base16encoder.h"

using std::cin;
using std::cout;
using std::dec;
using std::endl;
using std::hex;
using std::string;

// true for continue
// false for exit
static bool do_encoding();

int main() {
    while (true) if (do_encoding()) cout << "Resetting encoder settings..." << endl;
    else { // NOLINT(readability-misleading-indentation)
        cout << "Thanks for using encoder, have a nice day!" << endl;
        return 0;
    }
}

bool do_encoding() {
    cout << "Configure the encoder..." << endl;

    size_t block_size;
    {
        // read non-negative block size
        while (true) {
            cout << "Enter block size: ";
            cin >> block_size;
            if (block_size == 0) cout << "Block-size should be positive" << endl;
            else break;
        }
    }

    unsigned int init_vector;
    cout << "Enter init-vector (HEX): ";
    cin >> std::hex >> init_vector >> std::dec;

    shift_side shift_side;
    {
        string shift_side_string;
        while (true) {
            cout << "Enter shift side (`left` (`l`) or `right` (`r`)): ";
            cin >> shift_side_string;
            if (shift_side_string == "l" || shift_side_string == "left") {
                shift_side = LEFT;
                break;
            }
            if (shift_side_string == "r" || shift_side_string == "right") {
                shift_side = RIGHT;
                break;
            }

            cout << "Unknown shift side `" << shift_side_string << "`" << endl;
        }
    }

    int shift_delta;
    cout << "Enter shift delta: ";
    cin >> shift_delta;

    encoder encoder(block_size, init_vector, shift_side, shift_delta);

    string action;
    while (true) {
        cout << "Enter your action (`encode` (`e`), `decode` (`d`), `reset` (`r`) or `exit` (`x`)): ";
        cin >> action;
        if (action == "e" || action == "encode") {
            cout << "Enter string to encode: ";
            string text;
            cin.ignore();
            getline(cin, text);
            // put into a constant to perform the operation safely
            const auto encoded = to_base_16(encoder.encode(string_to_char_vector(text)));
            cout << "Encoded: \"" << encoded << "\"" << endl;
            continue;
        }
        if (action == "d" || action == "decode" ) {
            cout << "Enter string to decode: ";
            string text;
            cin.ignore();
            getline(cin, text);
            // put into a constant to perform the operation safely
            const auto decoded = char_vector_to_string(encoder.decode(string_to_char_vector(from_base_16(text))));
            cout << "Decoded: \"" << decoded << "\"" << endl;
            continue;
        }
        if (action == "r" || action == "reset") return true;
        if (action == "x" || action == "exit") return false;

        cout << "Unknown action `" << action << "`" << endl;
    }
}