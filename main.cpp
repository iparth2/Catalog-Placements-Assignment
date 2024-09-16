#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <json/json.h>

using namespace std;

// Function to decode a value from a given base to decimal
int decode(int base, const string& value) {
    int result = 0;
    int power = 1;

    for (int i = value.length() - 1; i >= 0; --i) {
        char c = value[i];
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else {
            cerr << "Invalid character in base value: " << c << endl;
            return -1;
        }

        if (digit >= base) {
            cerr << "Digit " << digit << " out of range for base " << base << endl;
            return -1;
        }

        result += digit * power;
        power *= base;
    }

    return result;
}

// Function to calculate the Lagrange polynomial to find the constant term
int lagrange(const vector<pair<int, int>>& points, int x) {
    int result = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        int xi = points[i].first;
        int yi = points[i].second;
        int term = yi;

        for (size_t j = 0; j < points.size(); ++j) {
            if (i != j) {
                int xj = points[j].first;
                term *= (x - xj);
                term /= (xi - xj);
            }
        }

        result += term;
    }

    return result;
}

int processTestCase(const Json::Value& data) {
    int n, k;
    try {
        n = data["keys"]["n"].asInt();
        k = data["keys"]["k"].asInt();
    } catch (const exception& e) {
        cerr << "Error accessing JSON keys: " << e.what() << endl;
        return 1;
    }

    vector<pair<int, int>> points;

    for (int i = 1; i <= n; ++i) {
        try {
            int base = stoi(data[to_string(i)]["base"].asString());
            string value = data[to_string(i)]["value"].asString();

            int decodedValue = decode(base, value);
            if (decodedValue == -1) return 1; // Error during decoding
            points.emplace_back(i, decodedValue);
        } catch (const exception& e) {
            cerr << "Error processing JSON entry for index " << i << ": " << e.what() << endl;
            return 1;
        }
    }

    // Calculate the constant term (c) using the first k points
    vector<pair<int, int>> selectedPoints(points.begin(), points.begin() + k);
    int secret = lagrange(selectedPoints, 0);

    cout << "Secret (c): " << secret << endl;

    return 0;
}

int main() {
    // Read the test cases from a JSON file
    ifstream inputFile("test_cases.json");
    if (!inputFile) {
        cerr << "Error opening test cases file" << endl;
        return 1;
    }

    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    string errs;

    if (!Json::parseFromStream(readerBuilder, inputFile, &root, &errs)) {
        cerr << "Error parsing JSON file: " << errs << endl;
        return 1;
    }

    const Json::Value testCases = root["test_cases"];
    for (const auto& testCase : testCases) {
        if (processTestCase(testCase) != 0) {
            cerr << "Error processing test case" << endl;
            return 1;
        }
    }

    return 0;
}
