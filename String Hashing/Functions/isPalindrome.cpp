// O(1)
bool isPalindrom(StringHash x){ // For full string
	return x.forward_hash() == x.reverse_hash();
}

// O(1)
bool isPalindrom(StringHash x,int l,int r){
	return x.forward_hash(l,r) == x.reverse_hash(l,r);
}

// USAGE
string s = "abcmadamyus";
cout << ((isPalindrom(StringHash(s),3,7))?"YES":"NO") close
