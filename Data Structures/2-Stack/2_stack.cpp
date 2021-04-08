struct stack{
    vector<ll> s,smin = {LLONG_MAX},smax = {LLONG_MIN};
    void push(ll x){
        s.push_back(x);
        smin.push_back(::min(smin.back(),x));
        smax.push_back(::max(smax.back(),x));
    }
    ll pop(){
        ll res = s.back();
        s.pop_back();
        smin.pop_back();
        smax.pop_back();
        return res;
    }
    bool empty(){
        return s.empty();
    }
    ll min(){
        return smin.back();
    }
    ll max(){
        return smax.back();
    }
};

::stack s1,s2;

auto good = [&](){
    ll mn = min(s1.min(),s2.min());
    ll mx = max(s1.max(),s2.max());
    return ((mx - mn) <= k);
};

auto add = [&](ll val){
    s2.push(val);
};

auto remove = [&](){
    if(s1.empty()){
        while(!s2.empty()){
            s1.push(s2.pop());
        }
    }
    s1.pop();
};
