#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class Polynomial1                            //类声明        
{
public:
	int n;//次数
	double* a;//a[i]表示x的i次方的系数
//	double* b;//b[i]表示x的i次方的系数，分母
	Polynomial1();
	Polynomial1(int, double[]);
	explicit Polynomial1(double);
	explicit Polynomial1(int);
	Polynomial1(const Polynomial1& p2);
	Polynomial1(fstream&);
	~Polynomial1();
	void print();
	Polynomial1 derivative();//输出该多项式的导数
	double calculate(double x);//求其在x的值
	explicit operator double();
	Polynomial1 operator*(const Polynomial1&);
	Polynomial1 operator+(const Polynomial1&);
	Polynomial1 operator-(const Polynomial1&);
	Polynomial1 operator/(const Polynomial1&);//待完善！！！(目前直接忽略了余数)
	void operator=(const Polynomial1&);
	void operator+=(const Polynomial1&);
	void operator-=(const Polynomial1&);
	void operator*=(const Polynomial1&);
	Polynomial1 operator-();
	bool operator!();
	friend ostream& operator<<(ostream&, const Polynomial1&);
	friend istream& operator>>(istream&, Polynomial1& p);
};
#include "Polynomial1.h"

Polynomial1::Polynomial1() {
	n = -1;
	a = NULL;
}
Polynomial1::Polynomial1(int nn, double a1[]) {
	n = nn;
	a = new double[n + 1];
	if (a1)for (int i = 0; i <= n; i++)a[i] = a1[i];
	else for (int i = 0; i <= n; i++)a[i] = 0;
}
Polynomial1::Polynomial1(double a1) {
	n = 0;
	a = new double[1];
	a[0] = a1;
}
Polynomial1::Polynomial1(int a1) {
	n = 0;
	a = new double[1];
	a[0] = (double)a1;
}
Polynomial1::Polynomial1(const Polynomial1& p2) {
	n = p2.n;
	a = new double[n + 1];
	for (int i = 0; i <= n; i++)a[i] = p2.a[i];
}
Polynomial1::Polynomial1(fstream& fp) {
	fp >> this->n;
	a = new double[n + 1];
	for (int i = 0; i < n + 1; i++) {
		fp >> a[i];
	}
}
Polynomial1::~Polynomial1() {
	//n = -1;
	delete[]a;
}
Polynomial1 Polynomial1::derivative() {
	Polynomial1 ans(n - 1, NULL);
	for (int i = 0; i < n; i++) {
		ans.a[i] = a[i + 1] * (i + 1);
	}
	return ans;
}
double Polynomial1::calculate(double x) {
	double ans = 0;
	double pow = 1.0;
	for (int i = 0; i <= n; i++) {
		ans += pow * a[i];
		pow *= x;
	}
	return ans;
}
void Polynomial1::print() {
	bool f = 0;
	for (int i = 0; i < n + 1; i++) {
		if (f == 1) cout << '+';
		if (a[i]) {
			cout << '(' << a[i] << ")x^" << i;
			f = 1;
		}
	}
	cout << endl;
}
Polynomial1 Polynomial1::operator*(const Polynomial1& p2) {
	Polynomial1 ans(n + p2.n, NULL);
	for (int i = 0; i <= p2.n; i++) {
		for (int j = 0; j <= n; j++) {
			ans.a[j + i] += a[j] * p2.a[i];
		}
	}
	while (ans.n > 0 && (!ans.a[ans.n]))ans.n--;
	return ans;
}
Polynomial1 Polynomial1::operator/(const Polynomial1& p2) {
	if (p2.n > n) {
		cout << "wrong!" << endl;
		Polynomial1 ans;
		return ans;
	}
	Polynomial1 ans(n - p2.n, NULL);
	/*for (int i = n - p2.n; i >= 0; i--) {
		int t = (i + p2.n > n ) ? n : i + p2.n;
		ans.a[i] = a[j] - a[j - (n - p2.n)];
		for (int j = t; j >=i; j--) {
			ans.a[i] -=a[j]*a[]/a[j-(n-p2.n)]
		}
	}*/
	return ans;
}
Polynomial1 Polynomial1::operator+(const Polynomial1& p2) {
	int maxn = (n > p2.n) ? n : p2.n;
	Polynomial1 ans(maxn, NULL);
	for (int i = 0; i <= n; i++)ans.a[i] = a[i] + p2.a[i];
	while (ans.n > 0 && (!ans.a[ans.n]))ans.n--;
	return ans;
}
Polynomial1 Polynomial1::operator-(const Polynomial1& p2) {
	int maxn = (n > p2.n) ? n : p2.n;
	Polynomial1 ans(maxn, NULL);
	for (int i = 0; i <= n; i++)ans.a[i] = a[i] - p2.a[i];
	while (ans.n > 0 && (!ans.a[ans.n]))ans.n--;
	return ans;
}
void Polynomial1::operator=(const Polynomial1& p2) {
	n = p2.n;
	delete[]a;
	a = new double[n + 1];
	for (int i = 0; i <= n; i++)a[i] = p2.a[i];
}
void Polynomial1::operator+=(const Polynomial1& p2) {
	(*this) = (*this) + p2;
}
void Polynomial1::operator-=(const Polynomial1& p2) {
	(*this) = (*this) - p2;
}
void Polynomial1::operator*=(const Polynomial1& p2) {
	(*this) = (*this) * p2;
}
Polynomial1 Polynomial1::operator-() {
	Polynomial1 ans(n, NULL);
	for (int i = 0; i <= n; i++)ans.a[i] = -a[i];
	return ans;
}
bool Polynomial1::operator!() {
	if (n < 0)return 1;
	return 0;
}
Polynomial1::operator double()
{
	return a[0];
}
ostream& operator<<(ostream& output, const Polynomial1& p)
{
	bool f = 0;
	if (p.n < 0)return output;
	if (p.n == 0) {
		output << '(' << p.a[0] << ')';
		return output;
	}
	if (p.a[0]) {
		output << '(' << p.a[0] << ')';
		f = 1;
	}
	if (p.a[1]) {
		if (f == 1) cout << '+';
		output << '(' << p.a[1] << ")x";
		f = 1;
	}
	for (int i = 2; i < p.n + 1; i++) {
		if (p.a[i]) {
			if (f == 1) cout << '+';
			output << '(' << p.a[i] << ")x^" << i;
			f = 1;
		}
	}
	return output;
}

static double getn(int& now, char str[], int len) {
	double ans = 0;
	bool s = 1;
	if (str[now] == '+') {
		s = 1;
		now++;
	}
	if (str[now] == '-') {
		s = 0;
		now++;
	}
	if (str[now] == 'x' || str[now] == 'X') {
		if (s) return 1.0;
		else return -1.0;
	}
	while (str[now] >= '0' && str[now] <= '9' && now < len) {
		ans *= 10;
		ans += str[now] - '0';
		now++;
	}
	if (str[now] == '.') {
		now++;
		double w = 0.1;
		while (str[now] >= '0' && str[now] <= '9' && now < len) {
			ans += (str[now] - '0') * w;
			w *= 0.1;
			now++;
		}
	}
	if (str[now] == '+' || str[now] == '-' || str[now] == 'x' || str[now] == 'X' || now == len) {
		if (s) return ans;
		else return -ans;
	}
}
istream& operator>>(istream& input, Polynomial1& p)
{
	char str[1000];
	double a1[500] = { 0 };
	input >> str;
	int len = strlen(str);
	int now = 0, maxn = 0;
	while (now < len) {
		double t = getn(now, str, len);
		if (str[now] == 'x' || str[now] == 'X') {
			now++;
			if (str[now] == '^') {
				now++;
				int wn = 0;
				while (str[now] >= '0' && str[now] <= '9' && now < len) {
					wn *= 10;
					wn += str[now] - '0';
					now++;
				}
				if (maxn < wn)maxn = wn;
				a1[wn] += t;
			}
			else {
				if (maxn < 1)maxn = 1;
				a1[1] += t;
			}
		}
		else {
			a1[0] += t;
		}
	}
	Polynomial1 ans(maxn, a1);
	p = ans;
	return input;
}