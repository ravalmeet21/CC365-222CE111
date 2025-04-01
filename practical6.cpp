#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
private:
    string input;
    size_t index;

    bool match(char expected) {
        if (index < input.length() && input[index] == expected) {
            index++;
            return true;
        }
        return false;
    }

    bool parse_S() {
        if (match('a')) {
            return true;
        } else if (match('(')) {
            if (parse_L() && match(')')) {
                return true;
            }
        }
        return false;
    }

    bool parse_L() {
        if (parse_S()) {
            return parse_L_prime();
        }
        return false;
    }

    bool parse_L_prime() {
        if (match(',')) {
            if (parse_S()) {
                return parse_L_prime();
            }
            return false;
        }
        return true;
    }

public:
    RecursiveDescentParser(const string& str) : input(str), index(0) {}

    bool isValid() {
        return parse_S() && index == input.length();
    }
};

int main() {
    string input;
    cout << "Enter input string: ";
    cin >> input;

    RecursiveDescentParser parser(input);
    if (parser.isValid()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}