const int MAXLEN = 1000010; // Maximum size of string 
constexpr uint64_t mod = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);
int64_t base_pow[MAXLEN];
uint64_t modmul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}
void init() {
    base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++) {
        base_pow[i] = modmul(base_pow[i - 1], base);
    }
}
struct StringHash {
    vector<int64_t> pref;
    int size = -1;
    StringHash() {}
    template<typename T>
    StringHash(const vector<T> &ar) {
        if (!base_pow[0]) init();
        int n = ar.size();
        this->size = n;
        assert(n < MAXLEN);
        pref.resize(n + 3, 0);
        for (int i = 1; i <= n; i++) {
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= mod) pref[i] -= mod;
        }
    }
    StringHash(string &str) : StringHash(vector<char>(str.begin(), str.end())) {}
    uint64_t forward_hash() {
        int64_t h = pref[size-1] - modmul(base_pow[size-1], pref[0]);
        return h < 0 ? h + mod : h;
    }
    uint64_t forward_hash(int l, int r) {
        int64_t h = pref[r + 1] - modmul(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + mod : h;
    }
};
