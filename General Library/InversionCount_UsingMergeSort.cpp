ll inversion_cnt = 0;

void merge(vector<int> &A, int p, int q, int r){
    int n1 = q-p+1;     // segment A[p...q]
    int n2 = r-(q+1)+1; // segment A[q+1...r]
    vector<int> L(n1+1), R(n2+1);
    for (int i = 0; i < n1; ++i) L[i] = A[p+i];
    for (int i = 0; i < n2; ++i) R[i] = A[q+1+i];
    L[n1] = R[n2] = INT_MAX;
    int i = 0, j = 0; 
    for (int k = p; k <= r; ++k) {
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }else{
            inversion_cnt += (ll)(n1-i);
            A[k] = R[j];
            j++;
        }
    }
    L.clear(); R.clear();
}

void merge_sort(vector<int>&A, int p, int r){
    if(p < r){ // has atleast 2 elements in the subarray
        int q = (p+r)/2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

void merge_sort(vector<int>&A){
    merge_sort(A,0,A.size()-1);
}
