// O(|s|)
bool isSubstring(StringHash s_hash, StringHash p_hash){
	int size_of_p = p_hash.size();
	bool possible = false;
	for (int i = 0; i < s_hash.size(); ++i) {
		int start = i;
		int end = start + size_of_p - 1;
		if(s_hash.forward_hash(start,end) == p_hash.forward_hash()){ // O(1)
			possible = true;
			break;
		}
	}
	return possible;
}


// Brute Force -> O( |s| * |p| )
// Hashing     -> O( |s| )
