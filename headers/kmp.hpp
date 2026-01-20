#pragma once

using ll = long long;
using namespace std;
using vl = vector<ll>;
const ll inf=1LL<<60;

// IGNORE ABOVE
vl find_all(string s, string m, ll start=0, ll end=inf) {
	// KMP Algorithm
	// Explanation: https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm#Example_of_the_search_algorithm

	// Preprocessing longest proper prefix
	ll lps[m.size()];
	ll p_len = 0;
	lps[0] = p_len;
	ll p_i = 1;
	while(p_i < m.size()) {
		if (m[p_i]==m[p_len]) {
			++p_len;
			lps[p_i] = p_len;
			++p_i;
		} else {
			if (p_len == 0) {
				lps[p_i]=0;
				++p_i;
			} else {
				p_len = lps[p_len-1];
			}
		}
	}

	// Finding all instances
	vl ans;
	ll i = start, len = 0;
	end = min<ll>(end, s.size());
	while (i<end) {
		if (s[i] == m[len]) {
			++len;
			if(len == m.size()) {
				ans.push_back(i-len+1);
				len = lps[len-1];
			}
			++i;
		} else {
			if (len==0) {
				++i;
			} else {
				len = lps[len-1];
			}
		}
	}
	return ans;
}

