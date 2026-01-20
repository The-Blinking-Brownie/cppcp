#pragma once

using ll = long long;
using namespace std;
using vl = vector<ll>;

// IGNORE ABOVE
const size_t max_prime=1e7;
vl primes; // contains all primes
bool isprime[max_prime+1]; // whether index is prime
void sieve() {
	for(ll i=2; i<=max_prime; ++i) {
		isprime[i]=true;
	}
	isprime[0]=isprime[1]=false;
	for(ll i=2; i<=max_prime; ++i) {
		if (!isprime[i]) continue;
		primes.push_back(i);
		for(ll j=2*i; j<=max_prime; j+=i)
			isprime[j]=false;
	}
}

