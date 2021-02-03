/******** USAGE ********/
// st.init(n); // Build a "n" sized segment trees with all zeroes in O(logn)
// st.build(a); // Transform a vector into a segment tree in O(logn)
// st.set(x,v); // set index "x" to value "v" in O(logn)
// st.sum(l,r); // get sum on segment [l,r) in O(logn)

struct segtrees{
    int size;
    vector<ll> sums;

    void init(int n){
        size = 1;
        while(size < n) size<<=1;
        sums.assign(2*size,0LL);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int) a.size()) sums[x] = a[lx];
            return;
        }
        int m = lx + (rx - lx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }

    void build(vector<int> &a){ // O(n)
        build(a,0,0,size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            sums[x] = v;
            return;
        }
        int m = lx + (rx - lx)/2;
        if(i<m) set(i,v,2*x+1,lx,m);
        else set(i,v,2*x+2,m,rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void set(int i, int v){ // O(logn)
        set(i,v,0,0,size);
    }

    ll sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return sums[x];
        int m = lx + (rx - lx)/2;
        ll s1 = sum(l,r,2*x+1,lx,m);
        ll s2 = sum(l,r,2*x+2,m,rx);
        return s1 + s2;
    }

    ll sum(int l, int r){ // O(logn)
        return sum(l,r,0,0,size);
    }
};
