template<typename T>
class Matrix {
public:
    int mod = 0;
    vector<vector<T> > A;
    int r, c;
    Matrix() { //Default Constructor
        this->r = 0,this->c = 0;
    }
    Matrix(int r, int c) { //Matrix with given dimensions and random values
        this->r = r,this->c = c;
        A.assign(r, vector<T>(c));
    }
    Matrix(int r, int c, const T &val) { //Matrix with given value and dimensions
        this->r = r,this->c = c;
        A.assign(r, vector<T>(c, val));
    }
    Matrix(int n) { //Identity matrix with given dimension
        this->r = this->c = n;
        A.assign(n, vector<T>(n));
        for (int i = 0; i < n; i++) A[i][i] = (T) 1;
    }
    void display() { //Print the matrix
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)cout << A[i][j] << " ";
            cout << endl;
        }
    }
    Matrix operator*(const Matrix<T> &B) {
        assert(c == B.r);
        int i, j, k, x = r, y = c,z = B.c;
        Matrix<T> C(x, z, 0);
        for (i = 0; i < x; i++){
            for (j = 0; j < z; j++){
                for (k = 0; k < y; k++) {
                    C[i][j] = (C[i][j] + ((long long) A[i][k] * (long long) B[k][j]));
                    if(mod) C[i][j] %= mod;
                }
            }
        }
        return C;
    }
    void operator*=(const Matrix<T> &B) {
        assert(c == B.r);
        int i, j, k, x = r, y = c, z = B.c;
        Matrix<T> C(x, z, 0);
        for (i = 0; i < x; i++) {
            for (j = 0; j < z; j++) {
                for (k = 0; k < y; k++) {
                    C[i][j] = (C[i][j] + ((long long) A[i][k] * (long long) B[k][j]));
                    if (mod) C[i][j] %= mod;
                }
            }
        }
        this->r = C.r,this->c = C.c,this->A = C.A;
    }
    Matrix operator+(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        Matrix<T> C(r, c, 0);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) {
                C[i][j] = A[i][j] + B[i][j];
                if(mod) C[i][j] %= mod;
            }
        }
        return C;
    }
    void operator+=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) {
                A[i][j] = A[i][j] + B[i][j];
                if(mod) A[i][j] %= mod;
            }
        }
    }
    Matrix operator-() {
        Matrix<T> C(r, c, 0);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) {
                C[i][j] = -A[i][j];
                if(mod) {
                    C[i][j] %= mod;
                    if(C[i][j] < 0)C[i][j] += mod;
                }
            }
        }
        return C;
    }
    Matrix operator-(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        Matrix<T> C(r, c, 0);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) {
                C[i][j] = A[i][j] - B[i][j];
                if(mod) {
                    C[i][j] %= mod;
                    if (C[i][j] < 0) C[i][j] += mod;
                }
            }
        }
        return C;
    }
    void operator-=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) {
                A[i][j] = A[i][j] - B[i][j];
                if(mod) {
                    A[i][j] %= mod;
                    if (A[i][j] < 0) A[i][j] += mod;
                }
            }
        }
    }
    Matrix operator^(long long n) {
        assert(r == c);
        int i, j;
        Matrix<T> C(r),X(r, c, 0);
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) X[i][j] = A[i][j];
        }
        while (n) {
            if (n & 1) C *= X;
            X *= X;
            n /= 2;
        }
        return C;
    }
    void operator^=(long long n) {
        assert(r == c);
        int i, j;
        Matrix<T> C(r),X(r, c, 0);
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) X[i][j] = A[i][j];
        }
        while (n) {
            if (n & 1) C *= (*this);
            (*this) *= (*this);
            n /= 2;
        }
        this->A = C.A;
    }
    Matrix transpose() {
        Matrix<T> C(c, r);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) C[j][i] = A[i][j];
        }
        return C;
    }
    void transposeInplace() {
        Matrix<T> C(c, r);
        int i, j;
        for (i = 0; i < r; i++){
            for (j = 0; j < c; j++) C[j][i] = A[i][j];
        }
        this->r = C.r,this->c = C.c,this->A = C.A;
    }
    vector<T> &operator[](int i) {
        assert(i < r);
        assert(i >= 0);
        return A[i];
    }
    const vector<T> &operator[](int i) const {
        assert(i < r);
        assert(i >= 0);
        return A[i];
    }
    friend ostream &operator<<(ostream &out, const Matrix<T> &M) {
        for (int i = 0; i < M.r; ++i) {
            for (int j = 0; j < M.c; ++j) out << M[i][j] << " ";
            out << '\n';
        }
        return out;
    }
};
