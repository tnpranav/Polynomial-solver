#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// Convert number string in given base to decimal (as long long)
long long convertToDecimal(const string &value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = 10 + (tolower(c) - 'a');
        result = result * base + digit;
    }
    return result;
}

int main() {
    ifstream inFile("input.json");
    if (!inFile) {
        cerr << "Error: input.json not found!" << endl;
        return 1;
    }

    json j;
    inFile >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<long long> roots;

    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "keys") continue;
        int base = stoi(it.value()["base"].get<string>());
        string value = it.value()["value"].get<string>();
        long long root = convertToDecimal(value, base);
        roots.push_back(root);
    }

    // Sort roots by key order
    sort(roots.begin(), roots.end());

    // Use first k roots
    long long constant = 1;
    for (int i = 0; i < k; i++) {
        constant *= roots[i];
    }
    if (k % 2 == 1) constant = -constant; // (-1)^k

    cout << constant << endl;

    return 0;
}
