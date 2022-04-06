# include <iostream>
# include <vector>


bool kuhn (size_t v, 
    std::vector<std::vector<int>>& graph, 
    std::vector<bool>& used,
    std::vector<int>& match) {
    /*
    if (used[v]) return false;
    used[v] = true;

    for (auto vt : graph[v]) {
        if (match[vt] == -1 || kuhn (match[vt], graph, used, match)) {
            match[vt] = v;
            return true;
        }
    }
    */

    return false;
}


int iprob_f1_main () {

    size_t n, m;
    std::cin >> n >> m;

    auto graph = std::vector<std::vector<int>> (n, std::vector<int>{});
    auto match = std::vector<int> (n, -1);

    int x, y;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> x >> y;
        graph[x - 1].push_back (y - 1);
    }

    for (size_t v = 0; v < n; ++v) {
        auto used = std::vector<bool> (n, false);
        kuhn (v, graph, used, match);
    }

    int l = 0;
    for (auto i : match) if (i == -1) ++l;

    std::cout << n - match.size () + l;

    return 0;
}