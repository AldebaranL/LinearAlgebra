#pragma once
template<typename T>class Determinant
{
public:
	Determinant(int);
	~Determinant();
	int n;
	T** a;
	T det();
	T cofactor(int, int);
	void printd();

};


#include<stdio.h>
#include<stdlib.h>

/*
int now[50];
bool flag[50];
double sign() {
	double ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (now[i] > now[j])ans *= (-1);
		}
	}
	return ans;
}
double mul() {
	double ans = 1;
	for (int i = 0; i < n; i++) {
		ans *= a[i][now[i] - 1];
	}
	return ans;
}
void dfs(double* ans, int lev) {
	if (lev == 0)return;
	if (lev == 1) {
		for (int i = 1; i <= n; i++) {
			if (flag[i])continue;
			now[n - lev] = i;
		}
		*ans += sign() * mul(); //printf("%d ", *ans);
		//for (int i = 0; i < n; i++) printf("%d", now[i]); printf("\n");
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (flag[i])continue;
		flag[i] = 1;
		now[n - lev] = i;
		dfs(ans, lev - 1);
		flag[i] = 0;
	}
}
double det1() {
	double ans = 0;
	for (int i = 1; i <= n; i++)flag[i] = 0;
	dfs(&ans, n);
	return ans;
}
*/
template<typename T> Determinant<T>::Determinant(int nn) {
	n = nn;
	a = new T * [n];
	for (int i = 0; i < n; i++)
		a[i] = new T[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = (T)((double)0);
}
template<typename T> Determinant<T>::~Determinant() {
	for (int i = 0; i < n; ++i)
	{
		delete[] a[i];
	}
	delete[] a;
}
template<typename T>void Determinant<T>::printd() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.1f ", this->a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

template<typename T> static int change(T** b, int l, int n) {
	for (int i = l; i < n; i++) {
		if (b[i][l] != 0) {
			for (int j = 0; j < n; j++) {
				T t = b[l][j];
				b[l][j] = b[i][j];
				b[i][j] = t;
			}
			return 0;
		}
	}
	return 1;
}
template<typename T>T Determinant<T>::cofactor(int ii, int jj) {
	Determinant<T> t(n - 1);
	for (int i = 0; i < ii - 1; i++) {
		for (int j = 0; j < jj - 1; j++) {
			t.a[i][j] = a[i][j];
		}
		for (int j = jj - 1; j < n - 1; j++) {
			t.a[i][j] = a[i][j + 1];
		}
	}
	for (int i = ii - 1; i < n - 1; i++) {
		for (int j = 0; j < jj - 1; j++) {
			t.a[i][j] = a[i + 1][j];
		}
		for (int j = jj - 1; j < n - 1; j++) {
			t.a[i][j] = a[i + 1][j + 1];
		}
	}
	if ((ii + jj) % 2 == 1)return -t.det();
	else return t.det();
}
template<typename T> T Determinant<T>::det() {
	Determinant<T> b(n);
	T c, ans = (T)(1.0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b.a[i][j] = a[i][j];
	//printd(b);

	for (int i = 0; i < n; i++) {
		for (int i1 = i + 1; i1 < n; i1++) {
			if (b.a[i][i] == 0) {
				//		printf("!%d!\n", i);
				if (change(b.a, i, n))return 0;
				ans *= (T)(-1.0);
			}
			//	printd(b);
			c = (T)(-1.0) * (b.a[i1][i] / b.a[i][i]);
			for (int j = i; j < n; j++) {
				b.a[i1][j] += b.a[i][j] * c;
			}
		}
	}
	for (int i = 0; i < n; i++)ans *= b.a[i][i];
	//	printd(b);
	return ans;
}
/*
int main() {


	//creatdet();
	FILE* fpin = NULL;
	if (fopen_s(&fpin, "C:/Users/Aldebaran/Desktop/1.txt", "r"))
		printf("无法打开此文件\n");
	FILE* fpout = NULL;
	if (fopen_s(&fpout, "C:/Users/Aldebaran/Desktop/out.txt", "w"))
		printf("无法打开此文件\n");
for(int i=0;i<100;i++){
	fscanf_s(fpin, "%d", &n);
	a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fpin, "%lf", &a[i][j]);
		}
	}
	//printd(a);
	double ans1 = det1(), ans2 = det2();
	if (ans1 != ans2)fprintf(fpout, "%.0f %.0f\n", ans1, ans2);
	else fprintf(fpout, "y");
}
	fclose(fpout);
	fclose(fpin);
	//print(a);


	return 0;
}*/
