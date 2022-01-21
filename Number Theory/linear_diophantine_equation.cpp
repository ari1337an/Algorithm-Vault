int ext_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool lde_find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = ext_gcd(abs(a), abs(b), x0, y0);
    if (c % g) return false;
    x0 *= c / g; if (a < 0) x0 = -x0;
    y0 *= c / g; if (b < 0) y0 = -y0;
    return true;
}

bool lde_find_any_positive_solution(int a,int b, int c, int &xk, int &yk, int &g){
    // ax + by = c; this function finds solution for x > 0 && y > 0, or we can also include zero
    // find any solution first
    int x0, y0; g = ext_gcd(abs(a), abs(b), x0, y0);
    if (c % g) return false;
    x0 *= c / g; if (a < 0) x0 = -x0; 
    y0 *= c / g; if (b < 0) y0 = -y0;
    // arrange the range for the positive solution so that we can shift
    int l = ((-x0*g)/b), r = (y0*g/a);
    for(int k = l; k <= r; ++k){
        xk = x0 + k*b/g, yk = y0 - k*a/g; // shift the solution
        if(!(xk >= 0 && yk >= 0 && a*xk + b*yk == c)) continue; // WARNING!!! EDIT: here xk >= 0 for including zero 
        return true; // found a positive solution
    }
    return false; // no positive solution found
}

template<class T>
bool lde_three_variable_solver(int a, int b, int c, int d, int up_limit, int &xk, int &yk, int &zk, int &g, T standard_solver){
    // solves ax + by + cz = d where a,b,c,d <= up_limit
    int gcd = __gcd(a,b);
    for(int gc = (-1)*up_limit*c + d; gc <= d; gc+=gcd){
        if((gc-d)%c != 0) continue;
        zk = (d-gc)/c;
        int tmp_n = d - c*zk;
        if(tmp_n < 0) continue;
        if(standard_solver(a,b,tmp_n,xk,yk,g)) return true;
    }
    return false;
}
