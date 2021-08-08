#include <bits/stdc++.h>
using namespace std;

vector<int> myPrimes;
int pi;
 
const int L1D_CACHE_SIZE = 32768;
void segmented_sieve(int limit)
{
  int sqrt = (int) std::sqrt(limit);
  int segment_size = std::max(sqrt, L1D_CACHE_SIZE);
  int count = (limit < 2) ? 0 : 1;
 
  // we sieve primes >= 3
  int i = 3;
  int n = 3;
  int s = 3;
  myPrimes.push_back(2);
 
  std::vector<char> sieve(segment_size);
  std::vector<char> is_prime(sqrt + 1, true);
  std::vector<int> primes;
  std::vector<int> multiples;
 
  for (int low = 0; low <= limit; low += segment_size)
  {
    std::fill(sieve.begin(), sieve.end(), true);
 
    // current segment = [low, high]
    int high = low + segment_size - 1;
    high = std::min(high, limit);
 
    // generate sieving primes using simple sieve of Eratosthenes
    for (; i * i <= high; i += 2)
      if (is_prime[i])
        for (int j = i * i; j <= sqrt; j += i)
          is_prime[j] = false;
 
    // initialize sieving primes for segmented sieve
    for (; s * s <= high; s += 2)
    {
      if (is_prime[s])
      {
           primes.push_back(s);
           multiples.push_back(s * s - low);
      }
    }
 
    // sieve the current segment
    for (std::size_t i = 0; i < primes.size(); i++)
    {
      int j = multiples[i];
      for (int k = primes[i] * 2; j < segment_size; j += k)
        sieve[j] = false;
      multiples[i] = j - segment_size;
    }
 
    for (; n <= high; n += 2)
      if (sieve[n - low]) // n is a prime
        myPrimes.push_back(n);
  }
}


/*
    sieve with wheel optimization: https://paste.ubuntu.com/p/q3Kp8y5FgT/
*/