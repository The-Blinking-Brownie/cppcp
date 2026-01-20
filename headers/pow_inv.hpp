#pragma once

using ll = long long;

// IGNORE ABOVE
ll powModM(ll x, ll n, ll m) {
	ll ans=1;
	while ( n!=0 ) {
		if (n%2) {
			ans = (ans * x) % m;
		}
		n/=2;
		x = (x * x) % m;
	}
	return ans;
}

ll inv(ll x, ll p) {
	return powModM(x, p-2, p);
}
