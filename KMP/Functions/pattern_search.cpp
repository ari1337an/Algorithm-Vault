int number_of_matches(string text,string pattern){
    vector<int> LPS = prefix_function(text);
    int matches = 0;
    for (int i = 0, q = 0; i < (int)text.size(); ++i) {
        while(q > 0 && pattern[q] != text[i]) q = LPS[q-1];
        if(pattern[q] == text[i]) q++;
        if(q == pattern.size()){
            matches++;
            q = LPS[q-1];
        }
    }
    return matches;
}
