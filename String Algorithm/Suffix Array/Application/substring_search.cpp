// Time Complexty: |P|
int isMatching(int pos, SuffixArray &arr, string const &pattern){
    return arr.str[0].substr(pos,min((int)pattern.size(),arr.get_suffix_size(pos))).compare(pattern);
}

// Time Complexity: |P|log|S|
bool isFound(SuffixArray &arr, string const &pattern){
    int left = 0;
    int right = arr.str->size()-1;
    while(left <= right){
        int mid = left + (right - left)/2;
        int check = isMatching(arr.suffix_array[mid], arr, pattern);
        if(check == 0) return true;
        else if(check < 0) left = mid + 1;
        else if(check > 0) right = mid - 1;
    }
    return false;
}
