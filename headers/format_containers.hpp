// Allows easy printing of common data types
#pragma once
#include <bits/stdc++.h>

using ll = long long;
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
	return os << format("{}", s);
}
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& s) {
	return os << format("{}", s);
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& s) {
	return os << format("{}", s);
}
template<typename T>
ostream& operator<<(ostream& os, const list<T>& s) {
	return os << format("{}", s);
}
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const map<T1, T2>& s) {
	return os << format("{}", s);
}

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

template<typename T>
struct formatter<set<T>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for set.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(set<T> s, FmtContext& ctx) const
    {
        string ret = "set{";
		bool first=true;
		for(const auto& element : s) {
			if(!first) ret += ", ";
			first=false;
			ret+=quoteIfString(element);
		}
		ret += "}";
        return ranges::copy(ret, ctx.out()).out;
    }
};

template<typename T1, typename T2>
struct formatter<map<T1, T2>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for map.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(map<T1, T2> m, FmtContext& ctx) const
    {
        string ret = "map{";
		bool first=true;
		for(const auto& [key, value] : m) {
			if(!first) ret += ", ";
			first=false;
			ret+="[";
			ret+=quoteIfString(key);
			ret+=": ";
			ret+=quoteIfString(value);
			ret+="]";
		}
		ret += "}";
        return ranges::copy(ret, ctx.out()).out;
    }
};

template<typename T>
struct formatter<multiset<T>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for multiset.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(multiset<T> m, FmtContext& ctx) const
    {
        string ret = "mset{";
		bool first=true;
		for(const auto& element : m) {
			if(!first) ret += ", ";
			first=false;
			ret+=quoteIfString(element);
		}
		ret += "}";
        return ranges::copy(ret, ctx.out()).out;
    }
};

template<typename T>
struct formatter<list<T>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for list.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(list<T> l, FmtContext& ctx) const
    {
        string ret = "list[";
		bool first=true;
		for(const auto& element : l) {
			if(!first) ret += ", ";
			first=false;
			ret+=quoteIfString(element);
		}
		ret += "]";
        return ranges::copy(ret, ctx.out()).out;
    }
};

template<typename T>
struct formatter<vector<T>, char>
{
 
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
		// No parsing for now
		auto it = ctx.begin();
		if (it == ctx.end() || *it != '}')
			throw std::format_error("Invalid format args for vector.");
        return it;
    }
 
    template<class FmtContext>
    FmtContext::iterator format(vector<T> v, FmtContext& ctx) const
    {
        string ret = "vec[";
		bool first=true;
		for(const auto& element : v) {
			if(!first) ret += ", ";
			first=false;
			ret+=quoteIfString(element);
		}
		ret += "]";
        return ranges::copy(ret, ctx.out()).out;
    }
};


/* Some tests to make sure they're fine
void test() {
	set<ll> sl = {5, 3, -2, 5};
	println("sl = {}", sl);

	set<string> ss = {"test", "\""};
	println("ss = {}", ss);

	multiset<ll> ml = {5, 3, -2, 5};
	println("ml = {}", ml);

	list<ll> lil = {5, 3, 2};
	println("lil = {}", lil);

	vector<ll> vl = {5, 3, 2};
	println("vl = {}", vl);

	vector<vector<ll>> vvl = {{5, 3, 2}, {2, 4}};
	println("vvl = {}", vvl);

	vector<vector<vector<ll>>> vvvl = {{{5, 3, 2}}, {{2, 4}}};
	println("vvvl = {}", vvvl);

	vector<set<ll>> vs={{2,3}};
	println("vs = {}", vs);
	
	map<ll, ll> mll = {{4, 2}, {5, 6}, {-2, 10}};
	println("mll = {}", mll);
}
*/
