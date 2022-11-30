#include "validation.h"

int main(int argc, char **argv) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    int c, d;
    in >> c >> d;

    std::vector<std::string> items(d-c+1);
    for (auto &s: items) in >> s;

    int a = v.read_integer("a", 1, 1'000'000);
    v.space();
    int b = v.read_integer("b", 1, 1'000'000);
    v.newline();

    for (int i = c; i <= d; i++) {
        std::string str;
        if (i%a == 0) str += "Fizz";
        if (i%b == 0) str += "Buzz";
        if (str.empty()) str += std::to_string(i);
        
        v.check(str == items[i-c], "Mismatch at position ", i, ": expected ", items[i-c], ", got ", str);
    }
}
