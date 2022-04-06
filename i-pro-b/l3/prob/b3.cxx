# include <iostream>
# include <iomanip>
# include <iostream>
# include <functional>
# include <vector>
# include <cmath>

using vec = std::vector<size_t>;
using Graph = std::vector<std::vector<size_t>>;

template <typename _T>
class SparseTable {
public:
    SparseTable (const std::vector<_T>& base,
        const std::function<bool (const _T&, const _T&)>& _cmp)
        : cmp (_cmp), logs (base.size ()) {
        size_t base_size = base.size ();
        size_t maxpow = std::ceil (std::log2 (base_size + 1));
        table = std::vector<std::vector<_T>> (maxpow, std::vector<_T> (base_size));

        table[0] = base;
        for (size_t k = 0; k + 1 < maxpow; ++k) {
            size_t d = (1ll << k);
            for (size_t ind = 0; ind + d < base_size; ++ind) {
                table[k + 1][ind] = min (table[k][ind], table[k][ind + d]);
            }
        }

        logs[1] = 0;
        for (size_t i = 2; i < base_size; ++i) {
            logs[i] = logs[i >> 1ll] + 1;
        }
    }

    const _T& find_min (size_t l, size_t r) {
        if (l > r) exit (1);
        if (r > logs.size ()) exit (2);
        size_t power = logs[r - l];
        return min (table[power][l], table[power][r - (1ll << power)]);
    }

private:
    std::vector<std::vector<_T>> table;
    std::function<bool (const _T&, const _T&)> cmp;
    vec logs;

    const _T& min (const _T& a, const _T& b) {
        return cmp (a, b) ? a : b;
    }
};

void euler_walker (size_t v, const Graph& graph, std::vector<bool>& used,
    std::vector<std::pair<size_t, size_t>>&euler, vec& euler_pos, size_t deep) {
    euler.push_back ({ v, deep });
    euler_pos[v] = euler.size () - 1;
    used[v] = true;

    for (auto u : graph[v]) {
        if (!used[u]) {
            euler_walker (u, graph, used, euler, euler_pos, deep + 1);
            euler.push_back ({ v, deep });
        }
    }
}

void euler_tour (const Graph& graph, std::vector<std::pair<size_t, size_t>>& _euler,
    vec& _euler_pos) {
    std::vector<std::pair<size_t, size_t>> euler {};
    vec euler_pos (graph.size ());
    std::vector<bool> used (graph.size (), false);

    euler_walker (0, graph, used, euler, euler_pos, 0);

    _euler = euler;
    _euler_pos = euler_pos;
}

std::size_t n, m, x, y, z;
Graph graph;
vec a, rank {}, parent {};

void init_a () {
    for (int i = 2; i <= m * 2; ++i) {
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }
}

void next_q (size_t& a1, size_t& a2, size_t v, size_t i) {
    std::cout << "q: " << a1 << ", " << a2 << '\n';
    a1 = (a[2 * i - 1] + v) % n;
    a2 = a[2 * i];
}

int main () {

    std::ios_base::sync_with_stdio (false);
    std::cin.tie (NULL);

    std::cin >> n >> m;

    graph = Graph (n, vec {});
    for (size_t i = 1; i < n; ++i) {
        size_t k; std::cin >> k;
        graph[k].push_back (i);
        graph[i].push_back (k);
    }

    size_t a1, a2;
    std::cin >> a1 >> a2 >> x >> y >> z;

    if (n < 2) {
        std::cout << "0\n";
        return 0;
    }

    a = vec (m * 2 + 1);

    a[0] = a1;
    a[1] = a2;
    init_a ();

    std::vector<std::pair<size_t, size_t>> euler;
    vec euler_pos;
    euler_tour (graph, euler, euler_pos);

    SparseTable<std::pair<size_t, size_t>> sparse (euler,
        [] (const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) { return a.second > b.second; });

    size_t it_u, it_v;
    size_t lca, ans = 0;

    for (int i = 1; i <= m; ++i) {
        if (a1 == a2) continue;

        it_u = euler_pos[a1];
        it_v = euler_pos[a2];
        if (it_u > it_v) std::swap (it_u, it_v);

        lca = sparse.find_min (it_u, it_v).first;
        std::cout << "lca: " << ans << " " << it_u << " " << it_v << '\n';

        ans += lca;
        next_q (a1, a2, lca, i);
    }

    std::cout << ans << '\n';

    return 0;
}