# include <i-pro-b/l2/l2.hxx>

# include <cstdio>
# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <locale>
# include <map>
# include <algorithm>

class SuffixAutomata {

    struct node {
        int len = 0, link = 0;
        bool is_clone = false;
        std::map<char, size_t> next {};
    };

public:
    SuffixAutomata ();
    void construct (const std::string& base);
    bool contains (const std::string& base);

    std::vector<int> occurrence ();

private:
    std::vector<node> states;
    size_t size, last;

    void extend (char c);
};

SuffixAutomata::SuffixAutomata ()
    : size (0), last (0), states (200000) {

    states[0].len = 0;
    states[0].link = -1;
    states[0].is_clone = true;
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

std::vector<int> SuffixAutomata::occurrence () {
    std::vector<int> cnt (size, 0);

    for (size_t i = 0; i < size; ++i) {
        if (!states[i].is_clone) {
            cnt[i] = 1;
        }
    }

    std::vector<node> copy_states {};
    for (int i = 0; i < size; ++i) {
        copy_states.push_back (states[i]);
    }

    std::sort (copy_states.begin (), copy_states.end (), 
    [] (node a, node b) {
        return a.len > b.len;
    });

    for (int i = 0; i < size; ++i) {
        if (copy_states[i].link != -1) {
            cnt[copy_states[i].link] += cnt[i];
        }
    }

    return cnt;
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
            states[clone].is_clone = true;

            for (; p != -1 && states[p].next[c] == q; p = states[p].link) {
                states[p].next[c] = clone;
            }

            states[q].link = states[curr].link = clone;
        }
    }

    last = curr;
}


int i_pro_b::l2::b2_main () {

    SuffixAutomata automata {};
    std::locale loc;

    std::ios_base::sync_with_stdio (false);
    std::cin.tie (NULL);

    automata.construct ("123123");
    std::vector<int> cnt = automata.occurrence ();

    for (auto& c : cnt) {
        std::cout << c << '\n';
    }

    return 0;
}