#pragma once
#include <bits/stdc++.h>

using namespace std;

// IGNORE ABOVE
/* Func must be associative, commutative and idempotent for all the values in source.
 * Examples: gcd, lcm, bitwise &, |
 * O(nlogn) precomputation memory and time complexity,
 * O(1) query memory and time complexity
 */
template<typename ValueType, typename Func>
class sparse_table {
private:
	vector<vector<ValueType>> lookup;

public:
	size_t size;

public:
	sparse_table(const vector<ValueType>& source) {
		lookup.emplace_back(source);
		size=source.size();
		auto func = Func{};
		for(size_t j=1, twopow=1; twopow*2 <= source.size(); j++, twopow*=2) {
			lookup.emplace_back(source.size());
			for(ll i=0; i+2*twopow <= source.size(); ++i) {
				lookup[j][i] = func(lookup[j-1][i], lookup[j-1][i+twopow]);
			}
		}
	}

	ValueType query(size_t l, size_t r) {
		size_t j=0, twopow = 1;
		while(l+2*twopow <= r) {
			j++;
			twopow*=2;
		}
		auto func = Func{};
		return func(lookup[j][l], lookup[j][r+1-twopow]);
	}
};

#ifndef QUOTE_IF_STRING
#define QUOTE_IF_STRING
string quoteIfString(string s) {
	stringstream ss;
	ss << std::quoted(s);
	return ss.str();
}
template<typename T>
string quoteIfString(T s) {
	stringstream ss;
	ss << s;
	return ss.str();
}
#endif

template<typename ValueType, typename Func>
ostream& operator<<(ostream& os, const sparse_table<ValueType, Func>& s) {
	return os << format("{}", s);
}

template<typename ValueType, typename Func>
struct formatter<sparse_table<ValueType, Func>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for sparse_table.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(sparse_table<ValueType, Func> st, FmtContext& ctx) const
    {
        string ret = "sparse_table[";
		bool first=true;
		for(size_t i = 0; i < st.size; ++i) {
			if(!first) ret += ", ";
			first=false;
			ret+=quoteIfString(st.query(i, i));
		}
		ret += "]";
        return ranges::copy(ret, ctx.out()).out;
    }
};

