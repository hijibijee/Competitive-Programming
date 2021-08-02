#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
    This function returns gcd(a, b) and
    sets values of x, y such that: a * x + b * y = gcd(a, b) 
*/


// Recursive way
ll egcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    
    ll currX, currY;

    ll ret = egcd(b, a % b, currX, currY);

    x = currY;
    y = currX - currY * (a / b);

    return ret;
}


//Iterative way
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