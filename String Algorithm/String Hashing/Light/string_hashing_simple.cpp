vector<ll> basepow1, basepow2;
const ull BASE1 = 2147462393;
const ull MOD1 = 2147462419;

void build_powers(int n) {
    basepow1.resize(n + 3, 1);
    for (int i = 1; i <= n; i++) {
        basepow1[i] = basepow1[i - 1] * BASE1 % MOD1;
    }
}

struct SingleHash {
    ull base, mod;
    bool onlyPrefix;
    vector<ll> prefix_hash, suffix_hash;
    SingleHash() {}
    SingleHash(string str, ull base, ull mod, bool onlyPrefix = false) : base(base), mod(mod), onlyPrefix(onlyPrefix) {
        int len = str.size();
        prefix_hash.resize(len + 3, 0), suffix_hash.resize(len + 3, 0);
        for (int i = 1; i <= len; i++) prefix_hash[i] = (prefix_hash[i - 1] * base + str[i - 1]) % mod;
        //for (int i = len; i >= 1; i--) suffix_hash[i] = (suffix_hash[i + 1] * base + str[i - 1]) % mod;
    }
    ull forward_hash(int l, int r) {
        ll h;
        if (base == BASE1) h = prefix_hash[r + 1] - ((ull) basepow1[r - l + 1] * prefix_hash[l] % mod);
        else h = prefix_hash[r + 1] - ((ull) basepow2[r - l + 1] * prefix_hash[l] % mod);
        return h < 0 ? h + mod : h;
    }
    ull reverse_hash(int l, int r) {
        ll h;
        if (base == BASE1)h = (suffix_hash[l + 1] - ((ull) basepow1[r - l + 1] * suffix_hash[r + 2] % mod));
        else h = (suffix_hash[l + 1] - ((ull) basepow2[r - l + 1] * suffix_hash[r + 2] % mod));
        return h < 0 ? h + mod : h;
    }
};
