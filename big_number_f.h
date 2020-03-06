#pragma once
//big_number_f.h
#ifndef BIG_NUMBER_F
#define BIG_NUMBER_F
#endif
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string erase_bef0(string x) {
	while (x[0] == '0') x.erase(0, 1);
	return x;
}
bool madeof0(string x) { //all the elements are '0'
	for (int i = 0; i < x.size(); i++) {
		if (x[i] != '0') return 0;
	}
	return 1;
}
void make_size_equal(string& x, string& y) {
	string& longer = x.size() > y.size() ? x : y;
	string& shorter = x.size() < y.size() ? x : y;
	while (longer.size() > shorter.size()) shorter.insert(0, "0");
}
bool bigger_than(string bigger, string smaller) {
	make_size_equal(bigger, smaller);
	for (int i = 0; i < bigger.size(); i++) {
		if (bigger[i] > smaller[i]) return 1;
		if (bigger[i] < smaller[i]) return 0;
	}
	return 0;
}
bool no_smaller_than(string bigger, string smaller) {
	make_size_equal(bigger, smaller);
	for (int i = 0; i < bigger.size(); i++) {
		if (bigger[i] > smaller[i]) return 1;
		if (bigger[i] < smaller[i]) return 0;
	}
	return 1;
}
bool smaller_than(string smaller, string bigger) {
	make_size_equal(bigger, smaller);
	for (int i = 0; i < bigger.size(); i++) {
		if (bigger[i] > smaller[i]) return 1;
		if (bigger[i] < smaller[i]) return 0;
	}
	return 0;
}
bool no_bigger_than(string smaller, string bigger) {
	make_size_equal(bigger, smaller);
	for (int i = 0; i < bigger.size(); i++) {
		if (bigger[i] > smaller[i]) return 1;
		if (bigger[i] < smaller[i]) return 0;
	}
	return 1;
}
string max_str(string x, string y) {
	return bigger_than(x, y) ? x : y;
}
string min_str(string x, string y) {
	return smaller_than(x, y) ? x : y;
}
string plus_pos(string x, string y, int base = 10) {
	if (madeof0(x) && madeof0(y)) return "0";
	bool p10 = 0;//plus base
	make_size_equal(x, y);
	string ans;
	while (ans.size() <= x.size()) ans.push_back('0');
	/*if(base>36){
		for(int i=0;i<x.size();i++){
			if(x[i]>57) x[i]-=7;
			if(y[i]>57) y[i]-=7;
			if(x[i]>96) x[i]-=6;
			if(y[i]>96) y[i]-=6;
		}
	}
	else */if (base > 10) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i] > 57) x[i] -= 7;
			if (y[i] > 57) y[i] -= 7;
		}
	}
	for (int i = x.size() - 1; i >= 0; i--) {
		char temp = x[i] + y[i] + p10 - 48;
		if (temp > 47 + base) {
			temp -= base;
			p10 = 1;
		}
		else p10 = 0;
		ans[i + 1] = temp;
	}
	if (p10) ans[0] = '1';
	ans = erase_bef0(ans);
	/*if(base>36){
		for(int i=0;i<x.size();i++){
			if(ans[i]>57) ans[i]+=7;
			if(ans[i]>96) ans[i]+=6;
		}
	}
	else */if (base > 10) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans[i] > 57) ans[i] += 7;
		}
	}
	return ans;
}
string minus_pos(string x, string y, int base = 10) {
	if (madeof0(x) && madeof0(y)) return "0";
	x = erase_bef0(x), y = erase_bef0(y);
	bool ans_nag = 0;
	make_size_equal(x, y);
	string ans;
	if (x == y) return "0";
	if (bigger_than(y, x)) {
		string temp = x;
		x = y, y = temp;
		ans_nag = 1;
	}
	while (ans.size() < x.size()) ans.push_back('0');
	/*if(base>36){
		for(int i=0;i<x.size();i++){
			if(x[i]>57) x[i]-=7;
			if(y[i]>57) y[i]-=7;
			if(x[i]>96) x[i]-=6;//equal to single -=13
			if(y[i]>96) y[i]-=6;//equal to single -=13
		}
	}
	else */if (base > 10) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i] > 57) x[i] -= 7;
			if (y[i] > 57) y[i] -= 7;
		}
	}
	bool m10 = 0;
	for (int i = x.size() - 1; i >= 0; i--) {
		if (m10) x[i]--;
		if (x[i] < y[i]) {
			x[i] += base;
			m10 = 1;
		}
		char temp = x[i] - y[i] + 48;
		ans[i] = temp;
	}
	ans = erase_bef0(ans);
	if (ans_nag) ans.insert(0, "-");
	/*if(base>36){
		for(int i=0;i<x.size();i++){
			if(ans[i]>96) ans[i]+=13;
			if(ans[i]>57) ans[i]+=7;
		}
	}
	else */if (base > 10) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans[i] > 57) ans[i] += 7;
		}
	}
	return ans;
}
string basic_multi_pos(string x, string y) { //maxnum 999*109
	if (x < y) swap(x, y);
	string ans = x;
	if (erase_bef0(y).empty()) return ans;
	while (minus_pos(y, "1") != "0") {
		ans = plus_pos(ans, x);
		y = minus_pos(y, "1");
	}
	return ans;
}
string multi_one_pos(string x, char y, int base = 10) { //abcd*e
	if (y == '0' || madeof0(x)) return "0";
	x = erase_bef0(x);
	string ans;
	while (ans.size() <= x.size()) ans.push_back('0');
	if (base > 10) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i] > 57) x[i] -= 7;
		}
		if (y > 57) y -= 7;
	}
	int plus10s = 0;
	for (int i = x.size() - 1; i >= 0; i--) {
		int temp = (x[i] - 48) * (y - 48) + plus10s;
		plus10s = temp / base;
		temp -= plus10s * base;
		ans[i + 1] = temp + 48;
	}
	if (plus10s) {
		ans[0] = plus10s + 48;
	}
	ans = erase_bef0(ans);
	if (base > 10) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans[i] > 57) ans[i] += 7;
		}
	}
	return ans;
}
string temp_multi_one_pos(string x, char y, int base = 10) { //no if(base>10) setences
	if (y == '0' || madeof0(x)) return "0";
	x = erase_bef0(x);
	string ans;
	while (ans.size() <= x.size()) ans.push_back('0');
	int plus10s = 0;
	for (int i = x.size() - 1; i >= 0; i--) {
		int temp = (x[i] - 48) * (y - 48) + plus10s;
		plus10s = temp / base;
		temp -= plus10s * base;
		ans[i + 1] = temp + 48;
	}
	if (plus10s) {
		ans[0] = plus10s + 48;
	}
	ans = erase_bef0(ans);
	return ans;
}
string temp_plus_pos(string x, string y, int base = 10) {
	if (madeof0(x) && madeof0(y)) return "0";
	bool p10 = 0;//plus base
	make_size_equal(x, y);
	string ans;
	while (ans.size() <= x.size()) ans.push_back('0');
	for (int i = x.size() - 1; i >= 0; i--) {
		char temp = x[i] + y[i] + p10 - 48;
		if (temp > 47 + base) {
			temp -= base;
			p10 = 1;
		}
		else p10 = 0;
		ans[i + 1] = temp;
	}
	if (p10) ans[0] = '1';
	ans = erase_bef0(ans);
	return ans;
}
string multi_pos(string x, string y, int base = 10) {
	if (x < y) swap(x, y);
	if (base > 10) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i] > 57) x[i] -= 7;
			if (y[i] > 57) y[i] -= 7;
		}
	}
	int ysize = y.size();
	string temp, ans = "0";
	for (int i = ysize - 1, j = 0; i >= 0; i--, j++) {
		temp = temp_multi_one_pos(x, y[i], base);
		for (int k = 0; k < j; k++) {
			temp.push_back('0');
		}
		ans = temp_plus_pos(ans, temp, base);
	}
	if (base > 10) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans[i] > 57) ans[i] += 7;
		}
	}
	return ans;
}
struct divide_rem {
	string quo, rem; //"rem"=reminder,"quo"=quotient.
	divide_rem() {
		quo = rem = "0";
	}
	divide_rem(string new_quo) {
		quo = new_quo, rem = "0";
	}
	divide_rem(string new_quo, string new_rem) {
		quo = new_quo, rem = new_rem;
	}
	bool whole() {
		return madeof0(rem);
	}
};
divide_rem basic_divide_rem_pos(string x, string y, int base = 10) {
	if (madeof0(y)) return divide_rem("inf");
	if (madeof0(x)) return divide_rem();
	divide_rem ans;
	for (;;) {
		if (smaller_than(x, y)) {
			ans.rem = x;
			break;
		}
		x = minus_pos(x, y, base);
		ans.quo = plus_pos(ans.quo, "1", base);
	}
	return ans;
}
