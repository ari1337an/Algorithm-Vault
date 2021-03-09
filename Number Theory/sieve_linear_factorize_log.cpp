class sieve{
public:
    int *lp;
    vector<int> primes;
    sieve(){
        int N = 1e7;
        lp = new int[N+1];
        for (int i=2; i<=N; ++i) {
            if (lp[i] == 0) lp[i] = i,primes.push_back(i);
            for (int j=0; j<(int)primes.size() && primes[j] <= lp[i] && i * primes[j] <= N; ++j) lp[i * primes[j]] = primes[j];
        }
    }
    ~sieve(){
        delete lp;
        primes.clear();
    }
    bool isPrime(int n){
        return lp[n] == n;
    }
    vector<int> factorize(int k) {
        vector <int> ans;
        while(k>1) {
            ans.push_back(lp[k]);
            k/=lp[k];
        }
        return ans;
    }
    unordered_map<int,int> factorize_freq(int k){ // O(logn)
        unordered_map<int,int> ans;
        while(k>1) {
            ans[lp[k]]++;
            k/=lp[k];
        }
        return ans;
    }
};
