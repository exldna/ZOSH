# include <iostream>

# include <fstream>
# include <string>
# include <algorithm>

int main () {
    
    // std::fstream file {"input.txt"};
    std::string s;
    std::cin >> s;

    size_t max_l = 0;

    for (size_t i = 0; i < s.size (); ++i) {
        size_t c = s.find ('A');
        if (c == std::string::npos) {
            break;
        }

        size_t counter_E = 0;
        for (auto& _c : s.substr (0, c)) {
            if (_c == 'E') ++counter_E;
        }

        if (counter_E >= 3 && c > max_l) max_l = c;
        s = s.substr (c + 1, s.size() - c);
    }

    std::cout << max_l << '\n';

    return 0;
}
