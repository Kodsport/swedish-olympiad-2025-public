// Testing tool for the task Love Letter.
//
// Usage:
//
//   bash unix_compile.sh
//   bash unix_run.sh
//
// input.txt uses the following format:
//
// N K
// S
// L R
// Where N is the length of S,
// K is the maximum length of a message that the encoder may produce,
// S is the message that should be sent,
// L and R denote the interval that should be flipped.
// More precisely, the judge will corrupt m[L], m[L+1], ..., m[R]
//
// Example input:
//
// 5 10
// 01011
// 1 3
//
//
// If --silent is passed, the communication output will not be printed.
//
// The tool is provided as-is, and you should feel free to make
// whatever alterations or augmentations you like to it. Notably,
// this is not the grader used in Kattis. This grader is also more informative
// as to how your program failed compared to Kattis.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#include "karleksbrev.h"


int main(int argc, char* argv[]) {
    bool silent = false;

    if (argc > 1 && string(argv[1]) == "--silent") {
        silent = true;
    }

    if (argc > 1 && string(argv[1]) == "-h") {
        cout << "Usage: program [--silent] < input.txt" << endl;
        return 0;
    }

    int N, K, L, R;
    string S;

    cin >> N >> K;
    cin >> S;
    cin >> L >> R;

    if (S.size() != N) {
        cerr << "[X] Error: length(S)=" << S.size() << " does not match N=" << N << endl;
        return 1;
    }

    for (char c : S) {
        if (c != '0' && c != '1') {
            cerr << "[X] Error: S=" << S << " contains character \"" << c << "\", which is not 0 or 1" << endl;
            return 1;
        }
    }

    if (!silent) {
        cout << "[*] Running with N=" << N << ", K=" << K << ", S=" << S << ", L=" << L << ", R=" << R << endl;
    }

    // Encode S
    string E = encode(S);
    if (!silent) {
        cout << "[*] S=" << S << ", encode(S)=" << E << endl;
    }

    // Sanity check E
    if (E.empty()) {
        cerr << "[X] Error: encoder gave an empty E for S=" << S << endl;
        return 1;
    }
    if (E.length() > K) {
        cerr << "[X] Error: encoder gave too long E. length(E)=" << E.size() << " > K=" << K << endl;
        return 1;
    }
    for (char c : E) {
        if (c != '0' && c != '1') {
            cerr << "[X] Error: encoder gave E containing character \"" << c << "\", which is not 0 or 1" << endl;
            return 1;
        }
    }

    if (L < 0 || R < 0 || L >= E.length() || R >= E.length()) {
        cerr << "L=" << L << " or R=" << R << " is out of bounds for length(E)=" << E.length() << endl;
        return 1;
    }

    // Corrupt E by flipping bits from L to R
    for (int i = L; i <= R; ++i) {
        E[i] = (E[i] == '0') ? '1' : '0';
    }

    if (!silent) {
        cout << "[*] E=" << E << " after corrupting" << endl;
    }

    // Check that the decoder can decode flipped E
    string decoded = decode(E);
    if (decoded != S) {
        cerr << "[X] Error: decoder did not find S. E after corrupting=" << E << ", S=" << S << ", decode(E)=" << decoded << endl;
        return 1;
    }

    if (!silent) {
        cout << "[*] decode(E)=" << decoded << endl;
    }

    cout << "Success! N=" << N << " len(E)=" << E.length() << endl;
    return 0;
}
