#pragma once
class RationalNumber
{
	int upper, lower;
public:
	RationalNumber(int u, int l) { upper = u; lower = l; };
	RationalNumber() { upper = 0; lower = 1; };
	void print();
	void simp();
	//friend RationalNumber operator+(RationalNumber, RationalNumber);
//	friend RationalNumber operator-(RationalNumber, RationalNumber);
//	friend RationalNumber operator*(RationalNumber, RationalNumber);
//	friend RationalNumber operator/(RationalNumber, RationalNumber);
	//RationalNumber operator=(RationalNumber&);
};

#include<iostream>
using namespace std;

void RationalNumber::print() {
	cout << upper << "/" << lower << endl;
}
void RationalNumber::simp() {
	int min = upper;
	if (min > lower)min = lower;
	for (int i = 1; i <= min; i++) {
		if ((upper % i) == 0 && (lower % i) == 0) {
			upper /= i; lower /= i;
		}
		if (min > lower)min = lower;
		if (min > upper)min = upper;
	}
}
/*
RationalNumber operator +(RationalNumber n1, RationalNumber n2) {
	RationalNumber ans;
	ans.upper = n1.upper * n2.lower + n2.upper * n1.lower;
	ans.lower = n1.lower * n2.lower;
	ans.simp();
	return ans;
}
RationalNumber operator -(RationalNumber n1, RationalNumber n2) {
	RationalNumber ans;
	ans.upper = n1.upper * n2.lower - n2.upper * n1.lower;
	ans.lower = n1.lower * n2.lower;
	ans.simp();
	return ans;
}
RationalNumber operator *(RationalNumber n1, RationalNumber n2) {
	RationalNumber ans;
	ans.upper = n1.upper * n2.upper;
	ans.lower = n1.lower * n2.lower;
	ans.simp();
	return ans;
}
RationalNumber operator /(RationalNumber n1, RationalNumber n2) {
	RationalNumber ans;
	ans.upper = n1.upper * n2.lower;
	ans.lower = n2.upper * n1.lower;
	ans.simp();
	return ans;
}*/
