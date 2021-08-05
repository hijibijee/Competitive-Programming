#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long int n){
    if(n == 1) return false;

    for(long long int x = 2; x * x <= n; x++){
        if(x % n == 0) return false;
    }

    return true;
}

// Some optimizations to make it 3 times faster
/*
    -> all primes greater than 3 are of the form 6k ± 1, where k is any integer greater than 0.
*/

bool isPrime(long long int n)
{
    if(n == 2 || n == 3) return true;

    if(n <= 1 || n % 2 == 0 || n % 3 == 0) return false;

    for(long long int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}