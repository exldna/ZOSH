# include <i-pro-b/l3/l3.hxx>

# include <iostream>
# include <vector>
# include <cmath>

using uint = unsigned int;
using vec = std::vector<uint>;
using Graph = std::vector<std::vector<uint>>;

class SparseTable {
public:
    SparseTable (const vec& base)
        : logs (base.size()) 
    {
        size_t base_size = base.size ();
        int maxpow = std::ceil (std::log2 (base_size + 1));
        table = std::vector<vec> (maxpow, vec (base_size, 0));

        table[0] = base;
        for (int k = 0; k + 1 < maxpow; ++k) {
            uint d = (1 << k);
            for (int ind = 0; ind + d < base_size; ++ind) {
                table[k + 1][ind] = std::min (table[k][ind], table[k][ind + d]);
            }
        }

        logs[1] = 0;
        for (int i = 2; i < base_size; ++i) {
            logs[i] = logs[i >> 1] + 1;
        }
    }

    uint find_min (size_t l, size_t r) {
        uint power = logs[r - l];
        return std::min (table[power][l], table[power][r - (1 << power)]);
    }

private:
    std::vector<vec> table;
    vec logs;
};

void euler_walker (uint v, const Graph& graph, std::vector<bool>& used,
    vec&euler, vec& euler_pos) 
{
    euler.push_back (v);
    euler_pos[v] = euler.size () - 1;
    used[v] = true;

    for (auto u : graph[v]) {
        if (!used[u]) {
            euler_walker (u, graph, used, euler, euler_pos);
            euler.push_back (v);
        }
    }
}

void euler_tour (const Graph& graph, vec& _euler, vec& _euler_pos) {
    vec euler {};
    vec euler_pos (graph.size ());
    std::vector<bool> used (graph.size (), false);

    euler_walker (0, graph, used, euler, euler_pos);

    _euler = euler;
    _euler_pos = euler_pos;
}

void deep_walker (uint v, uint h, const Graph& graph, 
    std::vector<bool>& used, vec& deep) 
{
    deep[v] = h;
    used[v] = true;
    for (auto u : graph[v]) {
        if (!used[u]) {
            deep_walker (u, h + 1, graph, used, deep);
        }
    }
}

vec deeper (const Graph& graph) {
    vec deep (graph.size ());
    std::vector<bool> used (graph.size (), false);
    deep_walker (0, 0, graph, used, deep);
    return deep;
}

int i_pro_b::l3::a3_main () {

    uint n = 1, m = 0; std::cin >> n;
    Graph graph (n, vec {});

    {
        uint u, v;
        for (int _n = 0; _n < n - 1; ++_n) {
            std::cin >> u >> v; --u, --v;
            graph[u].push_back (v);
            graph[v].push_back (u);
        }
    }

    std::cin >> m;

    vec euler, euler_pos;
    euler_tour (graph, euler, euler_pos);
    SparseTable sparse (euler);
    auto deep = deeper (graph);

    for (int _m = 0; _m < m; ++_m) {

        uint u, v; std::cin >> u >> v; --u; --v;
        if (u == v) {
            std::cout << 0 << '\n';
            continue;
        }

        uint it_u = euler_pos[u], it_v = euler_pos[v];
        if (it_u > it_v) std::swap (it_u, it_v);

        uint lca = sparse.find_min (it_u, it_v);
        std::cout << deep[u] + deep[v] - deep[lca] * 2 << '\n';
    }

    return 0;
}