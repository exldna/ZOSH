#include <pch.hxx>
#include <fstream>
#define FAST1 ios_base::sync_with_stdio(0);
#define FAST2 cin.tie(0), cout.tie(0);

using namespace std;

int main () {
    FAST1 FAST2
        size_t h, w, k; cin >> h >> w >> k;
    size_t r = 0;
    size_t mi = min (h + 1, k / 2), qq = 0;
    for (size_t i = 1; i < mi; ++i) {
        qq = (h - i + 1);
            for (size_t j = 1; j < min (k / 2 - i + 1, w + 1); ++j) {
                r += qq * (w - j + 1);
            }
    }
    cout << r;
    return 0;
}