# include <i-pro-b/l4/l4.hxx>

# include <iostream>
# include <algorithm>
# include <cmath>

# include <vector>

struct try_double {

    inline static const double eps = 0.000001;
    double x;

    try_double (): x (0) {}

    try_double (double _x): x (_x) {}

    bool operator== (const try_double& other) const {
        return std::abs (x - other.x) < eps;
    }

    bool operator<= (const try_double& other)const {
        return (x - eps) <= other.x;
    }

    bool operator>= (const try_double& other) const {
        return (x + eps) > other.x;
    }

    bool operator< (const try_double& other) const {
        return (x + eps) < other.x;
    }

    bool operator> (const try_double& other) const {
        return (x - eps) > other.x;
    }

    const try_double operator+(const try_double& other) const {
        return (x + other.x);
    }

    const try_double operator-(const try_double& other) const {
        return (x - other.x);
    }

    const try_double operator*(const try_double& other) const {
        return (x * other.x);
    }

    const try_double operator/(const try_double& other) const {
        return (x / other.x);
    }
};

using pos = std::pair<long long, long long>;
using Figure = std::vector<pos>;

const pos operator- (const pos& p1, const pos& p2) {
    return pos (p1.first - p2.first, p1.second - p2.second);
}

std::ostream& operator<< (std::ostream& stream, const pos& p) {
    return stream << p.first << ' ' << p.second;
}

try_double cross (const pos& a, const pos& b) {
    return static_cast<double>(a.first * b.second - a.second * b.first);
}

int i_pro_b::l4::a4_main () {

    size_t n; std::cin >> n;

    Figure fig (n, pos {});
    for (auto& p : fig) std::cin >> p.first >> p.second;

    size_t base_it = 0;

    for (size_t i = 1; i < n; ++i) {
        if (fig[base_it].first > fig[i].first) base_it = i;
        else if (fig[base_it].first == fig[i].first &&
            fig[base_it].second > fig[i].second)
            base_it = i;
    }

    std::vector<pos> convex (n);
    {
        size_t it = base_it, i = 0;

        while (it < n) {
            convex[i] = fig[it];
            ++it; ++i;
        }

        it = 0;

        while (it < base_it) {
            convex[i] = fig[it];
            ++it; ++i;
        }
    }

    bool is_convex = true;
    bool key = true;
    bool curr_is_r = false, last_is_r = false;

    for (size_t i = 2; i < n; ++i) {
        curr_is_r = convex[0].first <= convex[1].first;

        if (last_is_r != curr_is_r) {
            if (key) key = false;
            else {
                is_convex = false;
                break;
            }
        }

        if (cross (fig[i] - fig[i - 2], fig[i - 1] - fig[i - 2]) <= 0) {
            is_convex = false;
            break;
        }

        last_is_r = curr_is_r;
    }

    std::cout << (is_convex ? "YES" : "NO") << '\n';

    return 0;
}