#include <bits/stdc++.h>
using namespace std;

// These are probabilistic method. Miller-Rabin is preferred over fermat's. 

/*
long long int mul(ll a, ll b, ll mod){
    long long int res = 0;
    a %= mod;
    while(b){
        if(b & 1) res = (res % mod + a % mod) % mod;
        a = ((a % mod) + (a % mod)) % mod;
        b >>= 1;
    }

    return res;
}
*/

/*
    Implementation of miller rabin primality test
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long int power(long long int a, long long int n, long long int mod) {
    long long int res = 1;
    a %= mod;
    while(n) {
        if(n & 1) res = ((res % mod) * (a % mod)) % mod; // Be careful of overflow. Use mul(a, b, mod) if needed. 
        a = ((a % mod) * (a % mod)) % mod;
        n >>= 1;
    }

    return res;
}

bool check_composite(long long int n, long long int a, long long int d, int s) {
    long long int x = power(a, d, n);
    if (x == 1 || x == n - 1) return false;
    
    for (int r = 1; r < s; r++) {
        x = ((x % n) * (x % n)) % n;
        if (x == n - 1) return false;
    }

    return true;
};

bool isPrime(long long int n, int k = 5) { // returns true if n is probably prime, else returns false.
    if(n < 4) return n == 2 || n == 3;

    int s = 0;
    long long int d = n - 1;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < k; i++) {
        long long int a = uniform_int_distribution<long long int>(2, n - 2)(rng);
        if (check_composite(n, a, d, s))
            return false;
    }

    return true;
}




/*
    Implementation of fermat's primarility test. 

    This test uses the fact that a^(n - 1) % p = 1

    But there are some composite number for whom every number 1 < a < n holds a^(n - 1) % p = 1, 
    These number are called carmichael numbers.
*/

/*
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long int power(long long int a, long long int n, long long int mod) {
    long long int res = 1;
    a %= mod;
    while(n) {
        if(n & 1) res = ((res % mod) * (a % mod)) % mod; // Be careful of overflow. Use mul(a, b, mod) if needed.
        a = ((a % mod) * (a % mod)) % mod;
        n >>= 1;
    }

    return res;
}

bool isPrime(int n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        long long int a = uniform_int_distribution<long long int>(2, n - 2)(rng);
        if (power(a, n - 1, n) != 1) return false;
    }

    return true;
}
*/