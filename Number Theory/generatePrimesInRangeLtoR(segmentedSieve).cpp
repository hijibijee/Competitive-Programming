#include <bits/stdc++.h>
using namespace std;

/*
    generates all prime numbers in range (L, R)
*/

vector<long long int> segmentedSieveNoPreGen(long long L, long long R) {
    vector<char> isPrime(R - L + 1, true);
    long long lim = sqrt(R);
    vector<long long int> primes;

    for(long long i = 2; i <= lim; ++i)
        for(long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    
    for(long long i = 0, j = L; j <= R; i++, j++){
        if(isPrime[i]) primes.push_back(j);
    }

    return primes;
}