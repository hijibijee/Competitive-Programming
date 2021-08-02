#define ll long long 
#include <bits/stdc++.h>
using namespace std;


//Thid gcd function is actually the extended euclidean gcd version
ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// If ax + by = c equation has any solution it finds one of them, else return false, which means there is no solution
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}


//shifting the available solution to get another solution
/*
    I personally prefer not to use this function. Calculate required solutions from the solution that's been found using the fact that, 
    x + k * b, y - k * a is other solutions for any x, y. 
*/

void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

// find number of solutions in the range minx <= x <= maxx && miny <= y <= maxy. we can modify it to use however we want to use it.
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;

    a /= g;
    b /= g;

    /*
        Here the x, y is one solution for given equation. 
    */

    /*
        If we want to use our own egcd function.
            1. get g = __gcd(a, b), if(c % g) -> there is no solution.
            2. divide the equation by g. [ a /= g, b /= g, c /= g ]
               Now __gcd(a, b) = 1
            4. find any solution for ax + by = 1
            5. multiplying this with c will give us our required solution for ax + by = c   
            6. shift it as necessary using the fact that every solution is in (x + k * b, y - k * a) form. 
    */

    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    ll lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);

    if (lx > rx)
        return 0;

    return (rx - lx) / abs(b) + 1;
}



/* Own implementation for number of solutions 
For: LOJ - 1306

ll gcd(ll a, ll b, ll &x, ll &y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

void getGreaterOrEqual(ll x, ll b, ll y, ll a, ll tar, ll &nx, ll &ny){
    ll k = abs(x - tar) / abs(b);
    ll sign = (b > 0 ? 1 : -1);

    if(tar < x){
        if(x - sign * (k + 1) * b >= tar) nx = x - sign * (k + 1) * b, ny = y + sign * (k + 1) * a;
        else nx = x - sign * k * b, ny = y + sign * k * a;
    }
    else{
        if(x + sign * k * b < tar) nx = x + sign * (k + 1) * b, ny = y - sign *(k + 1) * a;
        else nx = x + sign * k * b, ny = y - sign * k * a;
    }
}

void getLesserOrEqual(ll x, ll b, ll y, ll a, ll tar, ll &nx, ll &ny){
    ll k = abs(x - tar) / abs(b);
    ll sign = (b > 0 ? 1 : -1);
    
    if(tar < x){
        if(x - sign * (k) * b > tar) nx = x - sign * (k + 1) * b, ny = y + sign * (k + 1) * a;
        else nx = x - sign * k * b, ny = y + sign * k * a;
    }
    else{
        if(x + sign * (k + 1) * b < tar) nx = x + sign * (k + 1) * b, ny = y - sign * (k + 1) * a;
        else nx = x + sign * k * b, ny = y - sign * k * a;
    }
}

ll cal(ll lx1, ll lx2, ll rx1, ll rx2, ll b){
    if(lx2 < rx1 || rx2 < lx1) return 0;
    
    ll l = max(lx1, rx1);
    ll r = min(lx2, rx2);
    b = abs(b);

    if(l > r) return 0;

    return (r - l + b) / b;
}

ll count_solutions(ll a, ll b, ll c, ll minX, ll maxX, ll minY, ll maxY){
    if(c < 0) c = -c, a = -a, b = -b;
    if(a == 0 && b == 0) return (c == 0) * (maxX - minX + 1) * (maxY - minY + 1);
    if(a == 0) return (abs(c) % abs(b) == 0) * (c / b >= minY && c / b <= maxY) * (maxX - minX + 1);
    if(b == 0) return (abs(c) % abs(a) == 0) * (c / a >= minX && c / a <= maxX) * (maxY - minY + 1);

    ll g = __gcd(abs(a), abs(b));

    if(c % g) return 0;

    a /= g, b /= g, c /= g;

    ll x, y;

    gcd(abs(a), abs(b), x, y);

    x *= c, y *= c;
    
    if(a < 0) x = -x;
    if(b < 0) y = -y;

    ll lx1, lx2, rx1, rx2, ly1, ly2, ry1, ry2;

    getGreaterOrEqual(x, b, y, a, minX, lx1, ly1);
    getLesserOrEqual(x, b, y, a, maxX, lx2, ly2);

    if(lx1 > lx2) return 0;

    getGreaterOrEqual(y, a, x, b, minY, ry1, rx1);
    getLesserOrEqual(y, a, x, b, maxY, ry2, rx2);

    if(ry1 > ry2) return 0;

    if(rx1 > rx2) swap(rx1, rx2);
    if(lx1 > lx2) swap(lx1, lx2);

    if(rx1 < lx1) swap(lx1, rx1), swap(lx2, rx2);

    return cal(lx1, lx2, rx1, rx2, b);
}

*/