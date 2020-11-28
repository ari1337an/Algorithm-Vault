bool isPalindrom(StringHash x){
	return x.forward_hash() == x.reverse_hash();
}
