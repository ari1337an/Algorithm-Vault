// Only change the NEUTRAL_ELEMENT, merge, and single function according to the associative function wanted
// Everything is in O(logn) except the build which is in O(n)

struct item{
    int value,count;
};

struct segtrees{
    int size;
    vector<item> values;

    item NEUTRAL_ELEMENT = {INT_MAX, 0};

    item merge(item a, item b){
        if(a.value < b.value) return a;
        if(a.value > b.value) return b;
        return {a.value, a.count + b.count};
    }

    item single(int value){
        return {value, 1};
    }

    void init(int n){
        size = 1;
        while(size < n) size<<=1;
        values.resize(2*size);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int) a.size()) {
                values[x] = single(a[lx]);
            }
            return;
        }
        int m = lx + (rx - lx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        values[x] = merge(values[2*x+1],values[2*x+2]);
    }

    void build(vector<int> &a){ // O(n)
        build(a,0,0,size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            values[x] = single(v);
            return;
        }
        int m = lx + (rx - lx)/2;
        if(i<m) set(i,v,2*x+1,lx,m);
        else set(i,v,2*x+2,m,rx);
        values[x] = merge(values[2*x+1],values[2*x+2]);
    }

    void set(int i, int v){
        set(i,v,0,0,size);
    }

    item calc(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = lx + (rx - lx)/2;
        item s1 = calc(l,r,2*x+1,lx,m);
        item s2 = calc(l,r,2*x+2,m,rx);
        return merge(s1,s2);
    }

    item calc(int l, int r){
        return calc(l,r,0,0,size);
    }
};
