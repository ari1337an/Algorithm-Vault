const int bignumlen = 2200;
const int Blen = 8;
const ll base = 100000000;
struct BigInteger {
    int len;
    ll data[bignumlen];

    ll &operator[](int x) { return (data[x]); }

    const ll &operator[](int x) const { return (data[x]); }

    BigInteger() {
        memset(data, 0, sizeof(data));
        len = 0;
    }

    void clear() {
        for (int i = len; i >= 1; --i)data[i] = 0;
        len = 0;
    }

    int check(const BigInteger &a, const BigInteger &b) {
        if (a.len > b.len)return (0);
        if (b.len > a.len)return (1);
        for (int i = a.len; i >= 1; --i) {
            if (a.data[i] < b.data[i])return (1);
            if (b.data[i] < a.data[i])return (0);
        }
        return 2;
    }

    bool operator<(const BigInteger &b) { return (check(*this, b) == 1); }

    bool operator>(const BigInteger &b) { return (check(*this, b) == 0); }

    bool operator<=(const BigInteger &b) { return (check(*this, b) >= 1); }

    bool operator>=(const BigInteger &b) { return (check(*this, b) % 2 == 0); }

    bool operator!=(const BigInteger &b) { return (check(*this, b) != 2); }

    bool operator==(const BigInteger &b) { return (check(*this, b) == 2); }

    BigInteger operator=(const BigInteger &x) {
        for (int i = x.len + 1; i <= len; ++i)data[i] = 0;
        for (int i = 1; i <= x.len; ++i)data[i] = x.data[i];
        len = x.len;
        return *this;
    }

    BigInteger operator=(ll x) {
        for (int i = len; i >= 0; --i)data[i] = 0;
        len = 0;
        while (x) {
            data[++len] = x % base;
            x /= base;
        }
        return *this;
    }

    BigInteger(ll x) {
        memset(data, 0, sizeof(data));
        len = 0;
        (*this) = x;
    }

    BigInteger operator*(const BigInteger &b) {
        int i, j;
        BigInteger tmp;
        for (i = 1; i <= len; ++i)
            if (data[i] != 0)
                for (j = 1; j <= b.len; ++j)
                    if (b.data[j] != 0) {
                        tmp.data[i + j - 1] += data[i] * b.data[j];
                        tmp.data[i + j] += tmp.data[i + j - 1] / base;
                        tmp.data[i + j - 1] %= base;
                    }
        tmp.len = len + b.len - 1;
        while (tmp.data[tmp.len + 1])tmp.len++;
        return tmp;
    }

    BigInteger operator*(ll x) {
        int i;
        BigInteger tmp;
        for (i = 1; i <= len; ++i)tmp[i] = data[i] * x;
        tmp.len = len;
        for (i = 1; i <= len; ++i) {
            tmp[i + 1] += tmp[i] / base, tmp[i] %= base;
            if (tmp[i + 1] && i + 1 > tmp.len)tmp.len++;
        }
        return tmp;
    }

    BigInteger operator/(ll x) {
        int i;
        BigInteger tmp;
        ll y = 0;
        for (i = len; i >= 1; --i) {
            y = y * base + data[i];
            tmp[i] = y / x;
            y %= x;
        }
        tmp.len = len;
        while (tmp[tmp.len] == 0 && tmp.len > 1)tmp.len--;
        return tmp;
    }

    BigInteger operator/(const BigInteger &b) {
        if (b.len <= 1 && b[1] == 0) {
            printf("error!");
            for (;;);
        }
        int i, l1 = (len - 1) * Blen, l2 = (b.len - 1) * Blen;
        ll x = data[len], y = b[b.len];
        while (x)x /= 10, l1++;
        while (y)y /= 10, l2++;
        BigInteger tmp, chu, B;
        chu = *this;
        B = b;

        for (i = 1; i * Blen <= l1 - l2; ++i)B *= base;
        for (i = 1; i <= (l1 - l2) % Blen; ++i)B *= 10;
        for (i = l1 - l2; i >= 0; --i) {
            x = 0;
            while (chu >= B)chu -= B, x++;
            tmp[i / Blen + 1] = tmp[i / Blen + 1] * 10 + x;
            B /= 10;
        }
        tmp.len = (l1 - l2) / Blen + 1;
        while (tmp.len >= 1 && !tmp[tmp.len])tmp.len--;
        return tmp;
    }

    BigInteger operator+(const BigInteger &b) {
        BigInteger tmp;
        int i, l = max(len, b.len);
        for (i = 1; i <= l; ++i)tmp[i] = data[i] + b[i];
        for (i = 1; i <= l; ++i)tmp[i + 1] += tmp[i] / base, tmp[i] %= base;
        tmp.len = l;
        if (tmp[tmp.len + 1])tmp.len++;
        return tmp;
    }

    BigInteger operator+(ll x) {
        BigInteger tmp;
        tmp = *this;
        tmp[1] += x;
        for (int i = 1; i <= len && tmp[i] >= base; ++i)tmp[i + 1] += tmp[i] / base, tmp[i] %= base;
        while (tmp[tmp.len + 1])tmp.len++;
        return tmp;
    }

    BigInteger operator-(const BigInteger &b) {
        int i;
        BigInteger tmp;
        for (i = 1; i <= len; ++i)tmp.data[i] = data[i] - b.data[i];
        for (i = 1; i <= len; ++i) {
            if (tmp[i] < 0)tmp.data[i] += base, tmp.data[i + 1]--;
        }
        tmp.len = len;
        while (tmp[tmp.len] == 0 && tmp.len > 1)tmp.len--;
        return tmp;
    }

    BigInteger operator-(ll x) {
        BigInteger tmp;
        tmp = *this;
        tmp[1] -= x;
        for (int i = 1; i <= len && tmp[i] < 0; ++i) {
            tmp[i + 1] += (tmp[i] + 1) / base - 1;
            tmp[i] = (tmp[i] + 1) % base + base - 1;
        }
        while (!tmp[tmp.len] && tmp.len > 1)tmp.len--;
        return tmp;
    }

    ll operator%(ll x) {
        int i;
        ll y = 0;
        for (i = len; i >= 1; --i)y = (y * base + data[i]) % x;
        return y;
    }

    BigInteger operator%(const BigInteger &b) {
        if (b.len <= 1 && b[1] == 0) {
            printf("error! 0 mod!");
            for (;;);
        }
        int i, l1 = (len - 1) * Blen, l2 = (b.len - 1) * Blen;
        ll x = data[len], y = b[b.len];
        while (x)x /= 10, l1++;
        while (y)y /= 10, l2++;
        BigInteger chu, B;
        chu = *this;
        B = b;

        for (i = 1; i * Blen <= l1 - l2; ++i)B *= base;
        for (i = 1; i <= (l1 - l2) % Blen; ++i)B *= 10;
        for (i = l1 - l2; i >= 0; --i) {
            while (chu >= B)chu -= B;
            B /= 10;
        }
        return chu;
    }

    static BigInteger bigMod(BigInteger a, BigInteger p) {
        BigInteger res = BigInteger(1);
        BigInteger x = BigInteger(a);
        while (p > 0) {
            if ((p%2) > 0) res = (res * x);
            x = (x * x);
            p /= BigInteger(2);
        }
        return res;
    }

    BigInteger operator+=(const BigInteger &b) { return *this = (*this + b); }

    BigInteger operator*=(const BigInteger &b) { return *this = (*this * b); }

    BigInteger operator-=(const BigInteger &b) { return *this = (*this - b); }

    BigInteger operator/=(const BigInteger &b) { return *this = (*this / b); }

    BigInteger operator%=(const BigInteger &b) { return *this = (*this % b); }

    BigInteger operator*=(ll x) { return (*this = (*this * x)); }

    BigInteger operator+=(ll x) { return (*this = (*this + x)); }

    BigInteger operator-=(ll x) { return (*this = (*this - x)); }

    BigInteger operator/=(ll x) { return (*this = (*this / x)); }

    void read() {
        char c[bignumlen * Blen + 10];
        cin >> (c+1);
        int l = strlen(c + 1);
        (*this).clear();
        ll x;
        for (int i = 1; i <= (l - 1) / Blen + 1; ++i) {
            x = 0;
            for (int j = l - Blen * i + 1; j <= l - Blen * i + Blen; ++j)if (j >= 1)x = x * 10 + c[j] - 48;
            data[++len] = x;
        }
    }

    void write() {
        cout << data[len];
        for (int i = len - 1; i >= 1; --i){
            int total = (int)(log10(data[i]) + 1 + EPS);
            cout << data[i];
            while(total < Blen){
                cout << 0;
                total++;
            }
        }
    }
};
BigInteger gcd(const BigInteger &A,const BigInteger &B){
    BigInteger a=A,b=B,res=1;
    while(!(a[1]&1)  && !(b[1]&1))a/=2,b/=2,res*=2;
    for(;;){
        if(a.len==1 && a[1]==0)return b*res;
        if(b.len==1 && b[1]==0)return a*res;
        while(!(a[1]&1))a/=2;
        while(!(b[1]&1))b/=2;
        if(a>b)a-=b;
        else b-=a;
    }
}
void YF(BigInteger &A,BigInteger &B){
    BigInteger tmp=gcd(A,B);
    A/=tmp; B/=tmp;
}
