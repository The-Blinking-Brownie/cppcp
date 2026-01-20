#pragma once

using ll = long long;
using namespace std;

// IGNORE ABOVE
tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
	// Extended Euclidean Algorithm
	// Explanation: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Description

	ll s0=1, t0=0, s1=0, t1=1;
    while(b) {
        ll q=a/b;
        a-=q*b;
        s0-=q*s1;
        t0-=q*t1;
        swap(a,b);
        swap(s0,s1);
        swap(t0,t1);
    }
	if(a<0) {
		a*=-1;
		s0*=-1;
		t0*=-1;
	}
    return {a, s0, t0}; // gcd, x, y such that ax+by=gcd
}

