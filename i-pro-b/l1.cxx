# include <i-pro-b/l1.hxx>

# include <iostream>
# include <vector>

void i_pro_b::l1::hello () {
    std::cout << "I_PRO_B L1 - matchings\n";\
}

bool i_pro_b::l1::kuhn_augment (int v) {
    /*
    if (used[v]) return;
    used[v] = true;
    for (int u : neighbours(v)) {
        if (matching[u] == -1 || kuhn_augment(matching[u])) {
            matching[u] = v;
            return true;
        }
    }
    */
    return false;
}

void i_pro_b::l1::kuhn () {
    /*
    // read Graph
    for (int v = 0; v < g.size(); ++v) {
        auto used = vector<bool>(g.size(), false)
        kuhn_augment(v)
    }
    */
}