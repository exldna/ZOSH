# ifndef _PCH_HXX
# define _PCH_HXX

# include <iostream>
# include <iomanip>
# include <string>

# include <optional>
# include <random>

# include <vector>

// using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)
#define forn(i, n) for(int i = 1; i <= n; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define S second
#define F first

using ll = long long;
using db = double;
using ld = long double;
using vi = std::vector<ll>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vvi = std::vector<std::vector<ll>>;
using pi = std::pair<ll, ll>;
using vpi = std::vector <pi>;
using vps = std::vector <std::pair<std::string, std::string>>;
using vvpi = std::vector <std::vector<pi>>;
using vvc = std::vector <std::vector<char>>;

//random_device rd;
//mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int INF = 1e13;
const double DELTA = 1;
const int mod = 1e9 + 7;
const int MAXN = 3e5;
const int N = 3e5;

# endif // !_PCH_HXX