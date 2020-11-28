vector<string> a = {"abc","edf","sdf","bacs","home"};
vector<string> q = {"edf","bacs","sdx"};


// PRE PROCESS
vector<ll> a_hash((int)a.size());
for (int i = 0; i < a.size(); ++i) {
	a_hash[i] = StringHash(a[i]).forward_hash();
}
// Dont Forget
sort(all(a_hash));


// QUERIES
// O(|q|)
int cnt = 0;
for (int i = 0; i < q.size(); ++i) {
	if(binary_search(all(a_hash),StringHash(q[i]).forward_hash())) cnt++; // O(logn)
}

// ANSWER
cout << cnt close
