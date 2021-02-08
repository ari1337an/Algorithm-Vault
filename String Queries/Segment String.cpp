// st.build(string s); // O( s.size())
// st.set(int i, char c); // O(1)
// st.is_palindrome(); // O(1) // IMPORTANT

struct segment_string{
    string s;
    int n, how_many_pairs_equal = 0;;
    vector<bool> is_palin_semi;
    unordered_map<int,int> mapss;
    bool current_palin = false;

    void build(string &str){ // O(n)
        n = str.size();
        s = str;
        is_palin_semi.resize(n);

        // Build the paired characters palindromic bools
        for (int i = 0; i < n/2; ++i) {
            is_palin_semi[i] = (int)pair_palin(i);
            is_palin_semi[n-1-i] = is_palin_semi[i];
            mapss[i] = n-1-i;
            mapss[n-1-i] = i;
            how_many_pairs_equal += (int)pair_palin(i);
        }

        if(how_many_pairs_equal == n/2) current_palin = true;

    }

    bool pair_palin(int i){
        if(!(i < n/2)) return s[i] == s[mapss[i]];
        return s[i] == s[n-i-1];
    }

    void turn_off_palin(int i){
        is_palin_semi[i] = false;
        is_palin_semi[mapss[i]] = false;
    }

    void turn_on_palin(int i){
        is_palin_semi[i] = true;
        is_palin_semi[mapss[i]] = true;
    }

    void set(int x, char c){ // O(1)
        current_palin = false;
        x--;
        s[x] = c;
        if(n%2 == 0 || x != (n/2)){
            if(how_many_pairs_equal == n/2){
                if(pair_palin(x)){
                    current_palin = true;
                    turn_on_palin(x);
                }else{
                    how_many_pairs_equal--;
                    turn_off_palin(x);
                }
            }else{
                if(pair_palin(x)){
                    if(!is_palin_semi[x]){
                        turn_on_palin(x);
                        how_many_pairs_equal++;
                    }
                    if(how_many_pairs_equal == n/2) current_palin = true;
                }else{
                    if(is_palin_semi[x]){
                        turn_off_palin(x);
                        how_many_pairs_equal--;
                    }
                }
            }
        }else if(how_many_pairs_equal == n/2){
            current_palin = true;
        }
    }

    bool is_palindrom(){ // O(1)
        return current_palin;
    }

};
