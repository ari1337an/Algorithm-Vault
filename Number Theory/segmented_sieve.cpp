vector<bool> segmentSIEVE(ll L, ll R){
    ll sqrt_till = (ll)sqrt(R);
    vector<bool> isPrime(sqrt_till + 1, true);
    vector<ll> primes;
    isPrime[0] = isPrime[1] = false;
    for (ll i = 2; i <= sqrt_till; i++) {
        if(isPrime[i]){
            primes.push_back(i);
            for (int j = i * i; j <= sqrt_till; j = j + i) {
                isPrime[j] = false;
            }
        }
    }
    vector<bool> segments( R - L + 1 , true);
    if (L == 0) segments[0] = segments[1] = false;
    if(L == 1) segments[0] = false;
    for(ll i : primes){
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i){
            segments[j - L] = false;
        }
    }
    return segments;
}
