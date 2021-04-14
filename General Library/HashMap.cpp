// O(1) Checking, Default 0, Faster than unordered_map

// Usage:
// HashMap<int, bool> strokes(100000);
// strokes.add(key, val);
// To checkL strokes[key];


template<typename TKey, typename TValue>
class HashMap {
private:
    const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
    uint64_t rnd = mt19937_64(seed)();
    const uint64_t salt = (rnd & 1) ? rnd : rnd--;
    int cur_id, _size, hash_mod;
    vector<int> id;
    vector<TKey> keys;
    vector<TValue> values;
    inline int get_pos(TKey x) {
        int i = ((x ^ (x >> 33)) * salt) & hash_mod;
        while (id[i] == cur_id && keys[i] != x) i++;
        return i;
    }
public:
    HashMap(int max_len) {
        int buffer = 4 * sqrt(max_len);
        int max_bits = 32 - __builtin_clz(max_len);
        hash_mod = (1 << (max_bits + 1)) - 1;
        _size = 0, cur_id = 1;
        id.resize(hash_mod + buffer, 0);
        keys.resize(hash_mod + buffer, 0);
        values.resize(hash_mod + buffer, 0);
    }
    void set(TKey x, TValue v) {
        int i = get_pos(x);
        if (id[i] == cur_id) {
            values[i] = v;
            return;
        }
        keys[i] = x, values[i] = v, id[i] = cur_id;
        _size++;
    }
    void add(TKey x, TValue v) {
        int i = get_pos(x);
        if (id[i] == cur_id) {
            values[i] = values[i] + v;
            return;
        }
        keys[i] = x, values[i] = v, id[i] = cur_id;
        _size++;
    }
    TValue get(TKey x) {
        int i = get_pos(x);
        return id[i] == cur_id ? values[i] : 0;
    }
    void erase(TKey x) {
        int i = get_pos(x);
        if (id[i] == cur_id) {
            keys[i] = 0, values[i] = 0, id[i] = 0;
            _size--;
        }
    }
    bool contains(TKey x) {
        int i = get_pos(x);
        return id[i] == cur_id;
    }
    void clear() {
        _size = 0;
        cur_id++;
    }
    int size() {
        return _size;
    }
    TValue operator[](TKey x) {
        int i = get_pos(x);
        return id[i] == cur_id ? values[i] : 0;
    }
};
