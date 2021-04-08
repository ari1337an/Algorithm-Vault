// Time Complexity:
// For each generation: O(NlogN)
// For each RSQ: O(N)


const int MAXN = (int)1e7; // The maximum size of N
const int K = 25; // The ceil(logMAXN)
int st[MAXN][K + 1];
void generate_sparse_RSQ(vector<int> &array, int N){
    for (int i = 0; i < N; i++) st[i][0] = array[i];
    for (int j = 1; j <= K; j++) for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j - 1];
}

ll RSQ(int L,int R){
    ll sum = 0;
    for (int j = K; j >= 0; j--) {
        if ((1 << j) <= R - L + 1) {
            sum += st[L][j];
            L += 1 << j;
        }
    }
    return sum;
}
