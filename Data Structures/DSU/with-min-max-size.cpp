struct DSU{
    vector<int> p,r,mn,mx,sz;
    DSU(int size) {
        p.resize(size+1);r.resize(size+1);
        mn.resize(size+1);mx.resize(size+1);sz.resize(size+1);
        for (int i = 0; i < size+1; ++i) {
            p[i] = i,r[i] = 0;
            sz[i] = 1;mn[i] = i;mx[i] = i;
        }
    }
    int get(int a) { return p[a] = (p[a] == a ? a : get(p[a])); }
    void join(int a, int b) {
        a = get(a),b = get(b);
        if(a == b) return;
        if(r[a] == r[b]) r[a]++;
        if(r[a] > r[b]) swap(a,b);
        else{
            p[a] = b;
            sz[b]+=sz[a];
            mn[b] = min(mn[a],mn[b]);
            mx[b] = max(mx[a],mx[b]);
        }
    }
};
