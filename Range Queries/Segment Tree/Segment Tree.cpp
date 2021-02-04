/******** USAGE ********/
// st.init(n); // Build a "n" sized segment trees with all zeroes in O(logn)
// st.build(a); // Transform a vector into a segment tree in O(logn)
// st.set(x,v); // set index "x" to value "v" in O(logn)
// st.sum(l,r); // get sum on segment [l,r) in O(logn)
// st.calc_min(l,r) // get min on segment [l,r) in O(logn)
// st.calc_max(l,r) // get max on segment [l,r) in O(logn)

struct segtrees{
    int size;
    vector<ll> sums;
    vector<int> mins;
    vector<int> maxs;

    void init(int n){
        size = 1;
        while(size < n) size<<=1;
        sums.assign(2*size,0LL);
        mins.assign(2*size,0);
        maxs.assign(2*size,0);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int) a.size()) {
                sums[x] = a[lx];
                mins[x] = a[lx];
                maxs[x] = a[lx];
            }
            return;
        }
        int m = lx + (rx - lx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
        mins[x] = min(mins[2*x+1],mins[2*x+2]);
        maxs[x] = max(maxs[2*x+1],maxs[2*x+2]);
    }

    void build(vector<int> &a){ // O(n)
        build(a,0,0,size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            sums[x] = v;
            mins[x] = v;
            maxs[x] = v;
            return;
        }
        int m = lx + (rx - lx)/2;
        if(i<m) set(i,v,2*x+1,lx,m);
        else set(i,v,2*x+2,m,rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
        mins[x] = min(mins[2*x+1],mins[2*x+2]);
        maxs[x] = max(maxs[2*x+1],maxs[2*x+2]);
    }

    void set(int i, int v){
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

    ll sum(int l, int r){
        return sum(l,r,0,0,size);
    }

    int calc_min(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return INT_MAX;
        if(lx >= l && rx <= r) return mins[x];
        int m = lx + (rx - lx)/2;
        int s1 = calc_min(l,r,2*x+1,lx,m);
        int s2 = calc_min(l,r,2*x+2,m,rx);
        return min(s1,s2);
    }

    int calc_min(int l, int r){
        return calc_min(l,r,0,0,size);
    }

    int calc_max(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return INT_MIN;
        if(lx >= l && rx <= r) return maxs[x];
        int m = lx + (rx - lx)/2;
        int s1 = calc_max(l,r,2*x+1,lx,m);
        int s2 = calc_max(l,r,2*x+2,m,rx);
        return max(s1,s2);
    }

    int calc_max(int l, int r){
        return calc_max(l,r,0,0,size);
    }
};
