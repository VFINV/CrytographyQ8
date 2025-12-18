#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>

using namespace std;

// DES Inverse Initial Permutation (IP^-1) table
static const int IP_INV[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

// Apply IP^-1 to 64-bit input
uint64_t inverseInitialPermutation(uint64_t in) {
    uint64_t out = 0;
    for (int i = 0; i < 64; ++i) {
        uint64_t bit = (in >> (64 - IP_INV[i])) & 1ULL; // select bit
        out |= (bit << (63 - i));                       // place bit
    }
    return out;
}

// Read a hex string (accepts "0x..." or without prefix)
uint64_t readHex(const string& prompt) {
    cout << prompt;
    string s;
    cin >> s;
    return stoull(s, nullptr, 16);
}

int main() {
    cout << "DES Q8 - Inverse Initial Permutation (IP^-1)\n";
    cout << "Choose input mode:\n";
    cout << "  1) Enter L32 and R32 (program will form preoutput = R||L)\n";
    cout << "  2) Enter 64-bit preoutput directly (R||L)\n";
    cout << "Your choice (1/2): ";

    int choice;
    cin >> choice;

    uint64_t preoutput = 0;

    if (choice == 1) {
        uint32_t L = static_cast<uint32_t>(readHex("Enter Left 32-bit (hex):  "));
        uint32_t R = static_cast<uint32_t>(readHex("Enter Right 32-bit (hex): "));
        preoutput = (static_cast<uint64_t>(R) << 32) | static_cast<uint64_t>(L);
    } else if (choice == 2) {
        preoutput = readHex("Enter 64-bit preoutput (R||L) in hex: ");
    } else {
        cout << "Invalid choice.\n";
        return 1;
    }

    uint64_t ciphertext = inverseInitialPermutation(preoutput);

    cout << "\nPreoutput: 0x"
         << uppercase << hex << setw(16) << setfill('0') << preoutput << "\n";

    cout << "Ciphertext (after IP^-1): 0x"
         << uppercase << hex << setw(16) << setfill('0') << ciphertext << "\n";

    return 0;
}
