// O(logn * |a| * |b| ) <--- TOTAL

// O( |a| * |b| )
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

string a = "campbapconsite";
string b = "bapsonline";

if(a.size() < b.size()) swap(a,b);

auto h1 = StringHash(a);
auto h2 = StringHash(b);

int left = 1;
int right = min(a.size(),b.size());
int longest_common_substring_length = -1;
while(left <= right){
  int mid = left + (right-left)/2;
  if(hasCommonSubstring(h1,h2,mid)){
    left = mid + 1;
    longest_common_substring_length = mid;
  }else{
    right = mid - 1;
  }
}
cout << longest_common_substring_length close
