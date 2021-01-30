// Time Complexity:
// For each generation: O(NlogN)
// For each RMQ: O(1)

const int MAXN = (int)1e7; // The maximum size of N
const int K = 25; // The ceil(logMAXN)
int st[MAXN][K + 1];
int log_val[MAXN+1];

void generate_sparse_RMQ(vector<int> &array, int N){
    log_val[1] = 0;
    for (int i = 2; i <= MAXN; i++) log_val[i] = log_val[i/2] + 1;
    for (int i = 0; i < N; i++) st[i][0] = array[i];
    for (int j = 1; j <= K; j++) for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j - 1]); // change the max to in for Range Min Query
}

int RMQ(int L, int R){
    int j = log_val[R - L + 1];
    int minimum = max(st[L][j], st[R - (1 << j) + 1][j]); // change the max to in for Range Min Query
    return minimum;
}
