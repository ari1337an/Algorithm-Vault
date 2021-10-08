/*
Uses rank heuristic

will create DSU with sets 0 to size+1

get works in O(logn)
union works in O(logn)
/*

struct DSU{
    vector<int> p,r;
    DSU(int size) {
        p.resize(size+1);r.resize(size+1);
        for (int i = 0; i < size+1; ++i) {p[i] = i,r[i] = 0;}
    }
    int get(int a) { return p[a] = (p[a] == a ? a : get(p[a])); }
    void union_sets(int a, int b) {
        a = get(a),b = get(b);
        if(a == b) return;
        if(r[a] == r[b]) r[a]++;
        if(r[a] > r[b]){
            p[b] = a;
        }else{
            p[a] = b;
        }
    }
};
