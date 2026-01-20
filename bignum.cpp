#include <bits/stdc++.h>
#ifdef DETCHOCO_ENV
#include "headers/format_containers.hpp"
#endif

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using namespace std;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
const ll inf=1LL<<60;

template<typename T>
void print(T x) {
	print("{}", x);
}

template<typename T>
void println(T x) {
	println("{}", x);
}

void precalc() {
}

class bigint {
public:
	bool sign = 0;
	vector<uint32_t> num;

public:
	bigint() {
		num.push_back(0);
	}

	bigint(int64_t n) {
		if(n<0) {
			sign = 1;
			n*=-1;
		}
		num.push_back(n & UINT32_MAX);
		if (n>>32 > 0) {
			num.push_back(n>>32);
		}
	}

	bool operator>(const bigint& n) const {
		if(num.size() > n.num.size()) return true;
		if(num.size() < n.num.size()) return false;
		for(size_t i=num.size(); i>0; --i) {
			if(num[i-1] > n.num[i-1]) return true;
			if(num[i-1] < n.num[i-1]) return false;
		}
		return false;
	}

	bool operator<(const bigint& n) const {
		if(num.size() < n.num.size()) return true;
		if(num.size() > n.num.size()) return false;
		for(size_t i=num.size(); i>0; --i) {
			if(num[i-1] < n.num[i-1]) return true;
			if(num[i-1] > n.num[i-1]) return false;
		}
		return false;
	}

	bool operator==(const bigint& n) const {
		if(num.size() != n.num.size()) return false;
		for(size_t i=0; i<num.size(); ++i) {
			if(num[i] != n.num[i]) return false;
		}
		return true;
	}

	bigint& operator=(const bigint& n) {
		if(this == &n) return *this;
		sign=n.sign;
		num=n.num;
		return *this;
	}

	friend bool operator>(int64_t n, const bigint& me) {
		return me < n;
	}

	friend bool operator<(int64_t n, const bigint& me) {
		return me > n;
	}

	friend bool operator==(int64_t n, const bigint& me) {
		return me == n;
	}

public:
	void erase_leading_zeroes() {
		while(num.size()>1 && *num.rbegin()==0)
			num.pop_back();
	}

	void increment(const bigint& n) {
		size_t i;
		uint32_t carry=0;
		for(i = 0; i<n.num.size(); ++i) {
			uint64_t sum = n.num[i]+carry;
			if (i<num.size()) {
				sum+=num[i];
				num[i]=sum & UINT32_MAX;
			} else {
				num.push_back(sum & UINT32_MAX);
			}
			carry = sum >> 32;
		}
		while(carry > 0) {
			if(i<num.size()) {
				uint64_t sum = num[i]+carry;
				num[i]=sum & UINT32_MAX;
				carry = sum >> 32;
			} else {
				num.push_back(carry);
				return;
			}
			++i;
		}
	}

	void decrement(const bigint& n) {
		if (n > *this) {
			bigint temp = *this;
			*this = n;
			sign |= 1;
			decrement(temp);
			return;
		}
		uint32_t carry=0;
		for(size_t i = 0; i<num.size(); ++i) {
			uint64_t sum = num[i] + carry - n.num[i];
			num[i] = sum & UINT64_MAX;
			carry = sum >> 32;
		}
		erase_leading_zeroes();
	}

public:

	bigint operator%(const bigint& divisor) const {
		if(divisor.num.size()==1) {
			int32_t d = divisor.num[0];
			if(d==0)
				throw std::runtime_error("Division by zero");
			int32_t carry = 0;
			for(size_t i=num.size(); i>0; --i) {
				int64_t sum = carry;
				sum<<=32;
				sum+=num[i-1];
				carry = sum%d;
			}
			return carry;
		}
		return 1;
	}

	bigint& operator++() {
		increment(1);
		return *this;
	}

	bigint operator++(int) {
		bigint old = *this;
		operator++();
		return old;
	}

	bigint& operator/=(const bigint& divisor) {
		if(divisor.num.size()==1) {
			int32_t d = divisor.num[0];
			if(d==0)
				throw std::runtime_error("Division by zero");
			int32_t carry = 0;
			for(size_t i=num.size(); i>0; --i) {
				int64_t sum = carry;
				sum<<=32;
				sum+=num[i-1];
				num[i-1]= sum/d;
				carry = sum%d;
			}
			erase_leading_zeroes();
		}
		return *this;
	}

	/*
    // prefix decrement
    X& operator--()
    {
        // actual decrement takes place here
        return *this; // return new value by reference
    }
 
    // postfix decrement
    X operator--(int)
    {
        X old = *this; // copy old value
        operator--();  // prefix decrement
        return old;    // return old value
    }
	*/
};

template<>
struct formatter<bigint, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it!= ctx.end() && *it != '}')
			throw std::format_error("Invalid format args for bigint.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(bigint n, FmtContext& ctx) const
    {
        string ret;
		while(n>0) {
			ret+=std::format("{}", (n%10).num[0]);
			n/=10;
		}
		if(ret == "") ret = "0";
		reverse(ret.begin(), ret.end());
        return ranges::copy(ret, ctx.out()).out;
    }
};


ostream& operator<<(ostream& os, const bigint& n) {
	return os << format("{}", n);
}


void solve() {
	bigint a = 1779979416004714189LL;
	bigint b = 1100087778366101931LL;
	while(b>0) {
		a.decrement(b);
		swap(a, b);
		println(a);
	}
}

int main() {
	ios_base::sync_with_stdio(false); // Slight io speed increase
	// But disables sync between different io streams so I only use std::print() for output.
	cin.tie(NULL); // cout must be manually flushed
	// I don't use cout though, so it might be useless.
	cout<<fixed<<setprecision(6); // floats/doubles correct to 5sf.

	precalc();
#ifdef MULTIPLE_TESTS
	ll t;cin >> t;
	while(t--)
#endif
	solve();
    
	return 0;
}
