// Four russian+independent bitvectors, found using greedy clique
#include <bits/stdc++.h>
using namespace std;

#include "karleksbrev.h"

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

mt19937 rng((random_device())());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]

const int num_bits = 16;
vi code = { 0, 21, 161, 180, 546, 567, 643, 662, 1093, 1104, 1252, 1265, 1639, 1650, 1734, 1747, 4131, 4150, 4226, 4247, 4609, 4628, 4768, 4789, 5222, 5235, 5319, 5330, 5700, 5713, 5861, 5872, 8263, 8274, 8422, 8435, 8805, 8816, 8900, 8913, 9218, 9239, 9379, 9398, 9760, 9781, 9857, 9876, 12388, 12401, 12485, 12496, 12870, 12883, 13031, 13042, 13345, 13364, 13440, 13461, 13827, 13846, 13986, 14007, 16648, 16669, 16809, 16828, 17194, 17215, 17291, 17310, 17741, 17752, 17900, 17913, 18287, 18298, 18382, 18395, 20779, 20798, 20874, 20895, 21257, 21276, 21416, 21437, 21870, 21883, 21967, 21978, 22348, 22361, 22509, 22520, 24911, 24922, 25070, 25083, 25453, 25464, 25548, 25561, 25866, 25887, 26027, 26046, 26408, 26429, 26505, 26524, 29036, 29049, 29133, 29144, 29518, 29531, 29679, 29690, 29993, 30012, 30088, 30109, 30475, 30494, 30634, 30655, 32838, 32851, 32999, 33010, 33380, 33393, 33477, 33488, 33795, 33814, 33954, 33975, 34337, 34356, 34432, 34453, 36965, 36976, 37060, 37073, 37447, 37458, 37606, 37619, 37920, 37941, 38017, 38036, 38402, 38423, 38563, 38582, 40961, 40980, 41120, 41141, 41507, 41526, 41602, 41623, 42052, 42065, 42213, 42224, 42598, 42611, 42695, 42706, 45090, 45111, 45187, 45206, 45568, 45589, 45729, 45748, 46183, 46194, 46278, 46291, 46661, 46672, 46820, 46833, 49486, 49499, 49647, 49658, 50028, 50041, 50125, 50136, 50443, 50462, 50602, 50623, 50985, 51004, 51080, 51101, 53613, 53624, 53708, 53721, 54095, 54106, 54254, 54267, 54568, 54589, 54665, 54684, 55050, 55071, 55211, 55230, 57609, 57628, 57768, 57789, 58155, 58174, 58250, 58271, 58700, 58713, 58861, 58872, 59246, 59259, 59343, 59354, 61738, 61759, 61835, 61854, 62216, 62237, 62377, 62396, 62831, 62842, 62926, 62939, 63309, 63320, 63468, 63481


};

const int n = 100;

map<int, int> invert;
map<int, int> myplace;

void precomp()
{
    invert = map<int, int>();
    myplace = map<int, int>();
    repe(c, code)
    {
        myplace[c] = sz(myplace);
        invert[c] = c;
        rep(i, num_bits)
        {
            repp(j, i, num_bits)
            {
                bitset<num_bits> bset(c);
                repp(k, i, j + 1)
                {
                    bset[k] = !bset[k];
                }
                int v = bset.to_ullong();
                assert(invert.find(v) == invert.end());
                invert[v] = c;
            }
        }
    }
}

int numblocks = 13;
string encode(string x)
{
    if (invert.empty()) precomp();

    __int128_t v = 0;
    rep(i, n)
    {
        if (x[i] == '1') v += (__int128_t(1) << i);
    }

    string ret;
    //cout << "v: " << v << "\n";
    rep(i, numblocks)
    {
        int c = code[v % sz(code)];
        //cout << "c: " << c << ", v%24: " << (v%24) << "\n";
        //cout << "c,b: ";
        v /= sz(code);
        rep(i, num_bits)
        {
            if (c & (1 << i)) ret += "1";
            else ret += "0";
        }

    }

    return ret;
}



string decode(string x)
{
    if (invert.empty()) precomp();

    __int128_t t = 0;
    __int128_t m = 1;
    while (sz(x))
    {
        string c = x.substr(0, num_bits);
        rep(i, num_bits) x.erase(x.begin());
        __int128_t v = 0;
        rep(i, num_bits) if (c[i] == '1') v += 1 << i;
        int iv = invert[v];
        __int128_t cv = myplace[iv];
        t += m * cv;
        m *= sz(code);
    }

    string ret;
    rep(i, n)
    {
        if (t & (__int128_t(1) << i)) ret += "1";
        else ret += "0";
    }

    return ret;
}
