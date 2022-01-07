long long int power(long long a, long long n){
    long long res = 1;
    while(n){
        if(n & 1){
            res *= a;
        }
        a *= a;
        n >>= 1;
    }

    return res;
}


/***
 * if mod is a prime a^n = a^(n % (mod - 1)) 
 * ***/
long long int power(long long a, long long n, long long mod){
    long long res = 1;
    while(n){
        if(n & 1){
            res = (res * (a % mod)) % mod;
        }

        a = (a * a) % mod;
        n >>= 1;
    }

    return res;
}