mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define get_random(x) uniform_int_distribution<int>(0, x-1)(rng)

vector<ull> PRIMES = {2147462393, 2147462419, 2147462587, 2147462633, 2147462747, 2147463167, 2147463203, 2147463569, 2147463727, 2147463863, 2147464211, 2147464549, 2147464751, 2147465153, 2147465563, 2147465599, 2147465743, 2147465953, 2147466457, 2147466463, 2147466521, 2147466721, 2147467009, 2147467057, 2147467067, 2147467261, 2147467379, 2147467463, 2147467669, 2147467747, 2147468003, 2147468317, 2147468591, 2147468651, 2147468779, 2147468801, 2147469017, 2147469041, 2147469173, 2147469229, 2147469593, 2147469881, 2147469983, 2147470027, 2147470081, 2147470177, 2147470673, 2147470823, 2147471057, 2147471327, 2147471581, 2147472137, 2147472161, 2147472689, 2147472697, 2147472863, 2147473151, 2147473369, 2147473733, 2147473891, 2147473963, 2147474279, 2147474921, 2147474929, 2147475107, 2147475221, 2147475347, 2147475397, 2147475971, 2147476739, 2147476769, 2147476789, 2147476927, 2147477063, 2147477107, 2147477249, 2147477807, 2147477933, 2147478017, 2147478521, 2147478563, 2147478649, 2147479447, 2147479589, 2147480707, 2147480837, 2147480927, 2147480971, 2147481263, 2147481311, 2147481337, 2147481367, 2147481997, 2147482021, 2147482063, 2147482081, 2147482343, 2147482591, 2147483069, 2147483123};

const ull BASE1 = PRIMES[get_random(PRIMES.size()-1)];
const ull MOD1  = PRIMES[get_random(PRIMES.size()-1)];
const ull BASE2 = PRIMES[get_random(PRIMES.size()-1)];
const ull MOD2  = PRIMES[get_random(PRIMES.size()-1)];

struct SingleHash{
	ull base,mod;
	bool onlyPrefix;
	vector<ull> basepow, prefix_hash, suffix_hash;
	SingleHash(){}
	SingleHash(string str, ull base, ull mod,bool onlyPrefix = false): base(base), mod(mod), onlyPrefix(onlyPrefix){
		int len = str.size();
		basepow.resize(len + 3, 1), prefix_hash.resize(len + 3, 0), suffix_hash.resize(len + 3, 0);

		for (int i = 1; i <= len; i++){
			basepow[i] = basepow[i - 1] * base % mod;
			prefix_hash[i] = (prefix_hash[i - 1] * base + str[i - 1]) % mod;
		}

		if(!onlyPrefix){
			for (int i = len; i >= 1; i--){
				suffix_hash[i] = (suffix_hash[i + 1] * base + str[i - 1]) % mod;
			}
		}
	}

	ull forward_hash(int l,int r){
		ull h = (prefix_hash[r+1] -  ((ull)basepow[r-l+1] * prefix_hash[l] % MOD) );
		return h < 0 ? h+mod : h;
	}

	ull reverse_hash(int l,int r){
		ull h = (suffix_hash[r+1] -  ((ull)basepow[r-l+1] * suffix_hash[l] % MOD) );
		return h < 0 ? h+mod : h;
	}
};

struct StringHash{
	SingleHash h1,h2;
	string str;
	int size_str;
	bool onlyPrefix;

	StringHash(string str, bool onlyPrefix = false ): str(str), size_str(str.size()), onlyPrefix(onlyPrefix) {
		h1 = SingleHash(str,BASE1,MOD1,onlyPrefix);
		h2 = SingleHash(str,BASE2,MOD2,onlyPrefix);
	}

	ull forward_hash(){
		return ((ull)h1.forward_hash(0,size_str-1) << 32) ^ h2.forward_hash(0,size_str-1);
	}

	ull forward_hash(int l,int r){
		return ((ull)h1.forward_hash(l,r) << 32) ^ h2.forward_hash(l,r);
	}

	ull reverse_hash(){
		if(!onlyPrefix) return ((ull)h1.reverse_hash(0,size_str-1) << 32) ^ h2.reverse_hash(0,size_str-1);
		else{
			cerr << "Reverse Hash Was Not Calculated Upon Hashing!" close
			return 0;
		}
	}

	ull reverse_hash(int l,int r){
		if(!onlyPrefix) return ((ull)h1.reverse_hash(l,r) << 32) ^ h2.reverse_hash(l,r);
		else{
			cerr << "Reverse Hash Was Not Calculated Upon Hashing" close
			return 0;
		}
	}

	unsigned int size() const{
		return size_str;
	}

	string toString() const{
		return str;
	}

};
