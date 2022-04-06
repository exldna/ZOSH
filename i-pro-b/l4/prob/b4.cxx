# include <i-pro-b/l4/l4.hxx>

# include <iostream>
# include <algorithm>
# include <cmath>

# include <vector>

struct try_double {

    inline static const double eps = 0.000001;
    double x;

    try_double() : x(0)
    {}

    try_double (double _x): x (_x)
    {}

    bool operator== (const try_double& other) const {
        return std::abs(x - other.x) < eps;
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

double len (const pos& b, const pos& e) {
    long long lx = b.first - e.first;
    long long ly = b.second - e.second;
    return std::sqrt (lx * lx + ly * ly);
}

int i_pro_b::l4::b4_main () {

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

    pos base = fig[base_it];
    Figure graham(n - 1);

    for (size_t i = 0; i < n; ++i) {
        if (i != base_it) {
            if (i < base_it) graham[i] = fig[i];
            else graham[i - 1] = fig[i];
        }
    }

    std::sort (graham.begin (), graham.end (),
        [&base] (const pos& f, const pos& s) {
            try_double c = cross (f - base, s - base);
            if (c < 0) return true;
            if (c == 0) return len (f, base) < len (s, base);
            return false;
        });

    Figure convex {};

    convex.push_back (base);
    convex.push_back (graham[0]);

    for (size_t i = 1; i < n - 1; ++i) {
        size_t l = convex.size ();
        while (l >= 2 && cross (graham[i] - convex[l - 2],
                                convex[l - 1] - convex[l - 2]) <= 0) 
        {
            convex.pop_back ();
            --l;
        }
        convex.push_back (graham[i]);
    }

    std::cout << convex.size () << '\n';
    for (auto& v : convex) std::cout << v << '\n';

    return 0;
}