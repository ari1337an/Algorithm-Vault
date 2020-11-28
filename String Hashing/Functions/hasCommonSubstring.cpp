// O(logn * |a| * |b| )
bool hasCommonSubstring(StringHash a,StringHash b,ll length){
	unordered_map<ll,bool> hash_table;
	for (int i = 0; i + length - 1< b.size(); ++i) {
		int start = i;
		int end = i + length - 1;
		hash_table[b.forward_hash(start,end)] = true;
	}
	for (int i = 0; i + length - 1 < a.size(); ++i) {
		int start = i;
		int end = i + length - 1;
		if(hash_table[a.forward_hash(start,end)]){
			return true;
		}
	}
	return false;
}
