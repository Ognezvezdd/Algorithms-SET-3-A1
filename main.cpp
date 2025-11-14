#include <iostream>
#include <stack>
#include <deque>
#include <random>
#include <map>
#include <cmath>
#include <numeric>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
#define all(a) a.begin(), a.end()
#define pb push_back
#define get(v) for (int & iq : v) cin >> iq
#define give(vv) for (int & iqq : vv) cout << iqq << " "
#define vi vector <int>
#define pii pair <int, int>
#define SOLVE int t; cin >> t; while (t--) {solve();}
typedef __int128 lll;
typedef long long ll;
typedef long double ld;
#define int ll
ll inf = 1e9 + 7, mod = 1e6 + 3;
int N = 1e6;

struct rectangle {
    ld x_min, x_max, y_min, y_max;
    ld area() const { return (x_max - x_min) * (y_max - y_min); }
};

struct Circle {
    ld cx, cy, r;

    bool inside(ld x, ld y) const {
        return (x - cx) * (x - cx) + (y - cy) * (y - cy)
               <= r * r + 1e-12;
    }
};

Circle C1{1.0, 1.0, 1.0};
Circle C2{1.5, 2.0, sqrt(5.0) / 2.0};
Circle C3{2.0, 1.5, sqrt(5.0) / 2.0};

auto S_TRUE = [] { return 0.25 * M_PI + 1.25 * asin(0.8) - 1.0; };

bool inside_aint(ld x, ld y) {
    return C1.inside(x, y) and C2.inside(x, y) and C3.inside(x, y);
}

rectangle wide_rectangle() {
    ld x_min = min({C1.cx - C1.r, C2.cx - C2.r, C3.cx - C3.r});
    ld x_max = max({C1.cx + C1.r, C2.cx + C2.r, C3.cx + C3.r});
    ld y_min = min({C1.cy - C1.r, C2.cy - C2.r, C3.cy - C3.r});
    ld y_max = max({C1.cy + C1.r, C2.cy + C2.r, C3.cy + C3.r});
    return {x_min, x_max, y_min, y_max};
}

static rectangle small_rectangle() {
    ld r = std::sqrt(5.0) / 2.0;
    ld lo = 2.0 - r - 1e-12;
    return {lo, 2.0, lo, 2.0};
}

ld one_more_try(rectangle &R, int N, mt19937_64 &rng) {
    uniform_real_distribution<ld> ux(R.x_min, R.x_max);
    uniform_real_distribution<ld> uy(R.y_min, R.y_max);
    int M = 0;
    for (int i = 0; i < N; ++i) {
        ld x = ux(rng), y = uy(rng);
        M += inside_aint(x, y);
    }
    return (static_cast<ld>(M) / static_cast<ld>(N)) * R.area();
}

signed main() {
#ifdef _LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N_MIN = 100, N_MAX = 100100, STEP = 500;
    int smoothing = 1;

    mt19937_64 rng_a(19);
    mt19937_64 rng_b(19 * 19 * 19);

    rectangle Rw = wide_rectangle();
    rectangle Rn = small_rectangle();

    cout << fixed << setprecision(8);
    cout << "N, S_est_wide, rel_err_wide, S_est_small, rel_err_small\n";

    auto run_N = [&](int N) {
        ld acc_w = 0.0L, acc_n = 0.0L;
        for (int r = 0; r < smoothing; ++r) {
            acc_w += one_more_try(Rw, N, rng_a);
            acc_n += one_more_try(Rn, N, rng_b);
        }
        auto S_wide = (ld) acc_w / (ld) smoothing;
        auto S_small = (ld) acc_n / (ld) smoothing;
        auto err_wide = abs(S_wide - S_TRUE()) / S_TRUE();
        auto err_small = abs(S_small - S_TRUE()) / S_TRUE();
        cout << N << ", " << S_wide << ", " << err_wide << ", " << S_small << ", " << err_small << "\n";
    };

    for (int n = N_MIN; n <= N_MAX; n += STEP) {
        run_N(n);
    }

    return 0;
}
