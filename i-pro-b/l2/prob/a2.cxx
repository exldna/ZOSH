# include <i-pro-b/l2/l2.hxx>

# include <cstdio>
# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <locale>
# include <map>

class SuffixAutomata {

    struct node {
        int len = 0, link = 0;
        std::map<char, size_t> next {};
    };

public:
    SuffixAutomata ();
    void construct (const std::string& base);
    bool contains (const std::string& base);

private:
    std::vector<node> states;
    size_t size, last;

    void extend (char c);
};

SuffixAutomata::SuffixAutomata ()
    : size (0), last (0), states(200000) {

    states[0].len = 0;
    states[0].link = -1;
    ++size;
}

void SuffixAutomata::construct (const std::string& base) {
    for (char c : base) {
        extend (c);
    }
}

bool SuffixAutomata::contains (const std::string& base) {
    int p = 0;
    for (int i = 0; i < base.size (); ++i) {
        if (states[p].next.find (base[i]) != states[p].next.end ()) {
            p = states[p].next[base[i]];
        } else {
            return false;
        }
    }
    return true;
}

void SuffixAutomata::extend (char c) {

    int curr = size++, p;
    states[curr] = states[size - 1];
    states[curr].len = states[last].len + 1;

    for (p = last; p != -1 && !(states[p].next.count (c)); p = states[p].link) {
        states[p].next[c] = curr;
    }

    if (p == -1) {
        states[curr].link = 0;
    } else {
        int q = states[p].next[c];
        if (states[p].len + 1 == states[q].len) {
            states[curr].link = q;
        } else {

            int clone = size++;

            states[clone].len = states[p].len + 1;
            states[clone].next = states[q].next;
            states[clone].link = states[q].link;

            for (; p != -1 && states[p].next[c] == q; p = states[p].link) {
                states[p].next[c] = clone;
            }

            states[q].link = states[curr].link = clone;
        }
    }

    last = curr;
}


int i_pro_b::l2::a2_main () {

    SuffixAutomata automata {};
    std::locale loc;

    char operation;
    std::string answer, base;

    std::ios_base::sync_with_stdio (false);
    std::cin.tie (NULL);

    while (getline(std::cin, answer)) {
        operation = answer[0];
        base = "";

        for (auto c : answer.substr (2, answer.size () - 2)) {
            base += std::tolower (c, loc);
        }

        switch (operation) {
            case 'A':
                automata.construct (base);
                break;
            case '?':
                std::cout << (automata.contains (base) ? "YES" : "NO") << '\n';
                break;
            default:
                std::cerr << "unknown operation " << operation << '\n';
        }
    }

    return 0;
}