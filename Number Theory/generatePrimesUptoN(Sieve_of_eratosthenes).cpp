#include <bits/stdc++.h>
using namespace std;

/*
    General Implementation
    Time Complexity: O(N log log N)
*/

vector<long long int> primes;

void generateP(long long int n){
    vector<bool>a(n+1,0);
    for(int i = 3; i*i <= n; i+=2){
        if(a[i] == 0){
            for(int j = i*i; j <= n; j+=i+i){
                a[j] = true;
            }
        }
    }
    
    primes.push_back(2);
    for(int i = 3; i <= n; i+=2){
        if(a[i] == 0) primes.push_back(i);
    }
}

bool checkP(long long int n){
    bool p = true;
    for(int i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            p = false;
            break;
        }
    }
    
    return p;
}



/*
    Super memory efficient implementation
    i.e. Yarin's sieve

bool isPrime(long long int n, vector<char> &a){
    if(n % 2 == 0) return n == 2;

    return (a[(n) >> 4] & (1 << (((n) >> 1) & 7)));
}  

vector<long long int> sieve(long long int N)
{
    vector<long long int> primes;
    long long int MAXSQRT = sqrt(double(N)) / 2;
	long long int MAXSIEVEHALF = (N/2);
    long long int i, j; 
    vector<char> a(N/16 + 2, 255);

	a[0] = 0xFE; 
	for(i = 1; i < MAXSQRT; i++) 
		if (a[i >> 3] & (1 << (i & 7))) 
			for(j = i + i + i + 1; j < MAXSIEVEHALF; j += i + i + 1) 
				a[j >> 3] &= ~(1 << (j & 7));

    primes.push_back(2);
    for(i = 3; i <= N; i += 2) if(isPrime(i, a)) primes.push_back(i);

    return primes;
}

*/