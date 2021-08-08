#include <bits/stdc++.h>
using namespace std;

/*
    This function can count prime numbers upto 10^11 really really fast. I do not undersatand it though. :(
    
    Source of this implementation: https://github.com/stbrumme/euler/blob/master/euler-0501.cpp

    Relevant references: 
        https://euler.stephan-brumme.com/toolbox/#primecount-lehmer
        https://euler.stephan-brumme.com/501/
        http://am-just-a-nobody.blogspot.com/2015/11/c-code-for-primepi-function.html
*/

vector<unsigned int> primes; // holds primes upto sqrt(n)
unsigned long long countPrimes(unsigned long long n)
{
    if(!primes.empty() && primes.back() > n)
    {
        auto i = upper_bound(primes.begin(), primes.end(), n);
        return distance(primes.begin(), i);
    }

    auto v = (unsigned int)sqrt(n);
    vector<unsigned long long> higher(v+2, 0);
    vector<unsigned int> lower(v+2, 0);
    vector<bool> used(v+2, false);

    unsigned long long result = n - 1;
    
    for(unsigned int p = 2; p <= v; p++)
    {
        lower [p] = p - 1;
        higher[p] = n / p - 1;
    }

    for(unsigned int p = 2; p <= v; p++)
    {
        if(lower[p] == lower[p - 1]) continue;

        if(primes.empty() || p > primes.back()) primes.push_back(p);

        auto temp  = lower[p - 1];
        result -= higher[p] - temp;

        auto pSquare = (unsigned long long)p * p;
        auto end = std::min<unsigned long long>(v, n / pSquare);
        auto j = 1 + (p & 1);

        for(auto i = p + j; i <= end + 1; i += j)
        {
            if(used[i]) continue;

            auto d = i * p;
            if(d <= v) higher[i] -= higher[d]    - temp;
            else higher[i] -= lower[n / d] - temp;
        }

        for(auto i = v; i >= pSquare; i--) lower[i] -= lower[i / p] - temp;

        for(auto i = pSquare; i <= end; i += p*j) used[i] = true;
    }

    return result;
}