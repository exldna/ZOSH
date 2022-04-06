# include <pch.hxx>

size_t n; ll W;

class Heap {
public:

    Heap() : t(1) {}

    Heap (const vi& other) : t(1) {
        for (auto& i : other) insert (i);
    }

    void insert (ll i) {
        t.push_back (pair (abs (static_cast<ll>(i - W)), i));
        _insert (t.size () - 1);
    }

    std::optional<pi> pop_max () {
        if (t.size () <= 1) return {};
        pi ans = t[1];
        _erase (1);
        return ans;
    }

    void show () {
        for (auto& i : t) {
            std::cout << i.first << ' ' << i.second << '\n';
        }
    }

private:

    vpi t;

    void _insert (size_t v) {
        if (v == 1) return;
        std::cout << "insert " << t[v / 2].F << ',' << t[v].F << ',' << t[v / 2].S << ',' << t[v].S << '\n';
        if (t[v / 2].F == t[v].F && t[v / 2].S < t[v].S) {
            std::swap (t[v / 2], t[v]);
            _insert (v / 2);
        }
        else if (t[v / 2].F < t[v].F) {
            std::swap (t[v / 2], t[v]);
            _insert (v / 2);
        }
    }

    void _erase (size_t v) {
        if (v >= t.size ()) return;
        else if (v >= t.size () / 2) {
            t.erase (t.begin () + v);
            return;
        }
        else if (t[v * 2].F == t[v * 2 + 1].F) {
            if (t[v * 2].S > t[v * 2 + 1].S) {
                t[v] = t[v * 2];
                _erase (v * 2);
            } else {
                t[v] = t[v * 2 + 1];
                _erase (v * 2 + 1);
            }
        }
        else if (t[v * 2].F > t[v * 2 + 1].F) {
            t[v] = t[v * 2];
            _erase (v * 2);
        } else {
            t[v] = t[v * 2 + 1];
            _erase (v * 2 + 1);
        }
    }

};

int main () {

    cin.tie (0);
    ios_base::sync_with_stdio (false);

    std::cin >> n >> W;

    Heap heap {};

    for (size_t i = 0; i < n; ++i) {
        size_t q;
        std::cin >> q;

        if (q == 1) {
            auto a = heap.pop_max ();
            if (a.has_value ()) {
                std::cout << a.value ().S << '\n';
            } else {
                std::cout << "-1\n";
            }
        }
        else if (q == 3) {
            heap.show ();
        } else {
            ll m, k;
            std::cin >> k >> m;

            for (size_t j = 0; j < k; ++j) {
                heap.insert (m);
            }
        }
        cout.flush ();
    }

    return 0;
}