/*

Uses rank heuristic

will create DSU with sets 0 to size+1
will create DSU with sets 0 to size+1 with proper ready if we add true to thr DSU(size,keep_ready)

get works in O(logn)
union works in O(logn)

/*
struct DSU{
    vector<int> p,r;
    DSU(int size) {p.resize(size+1);r.resize(size+1);}
    DSU(int size, bool keep_ready) {
        p.resize(size+1);r.resize(size+1);
        for (int i = 0; i < size+1 && keep_ready; ++i) this->make_set(i);
    }
    int get(int a) { return p[a] = (p[a] == a ? a : get(p[a])); }
    void make_set(int a) {p[a] = a,r[a] = 0;}
    void union_sets(int a, int b) {
        a = get(a),b = get(b);
        if(r[a] == r[b]) r[a]++;
        if(r[a] > r[b]){
            p[b] = a;
        }else{
            p[a] = b;
        }
    }
};
