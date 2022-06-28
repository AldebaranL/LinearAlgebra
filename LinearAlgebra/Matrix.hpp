#pragma once
#include<iostream>
#include "Determinant.hpp"
#include<math.h>
#include<fstream>
using namespace std;
template<class T>class Matrix
{
public:
	//char name[10];
	int n, m;//n行m列
	int rank;
	T** a;

	//void inputm();
	//void printm();

	//Complex<T> operator+(Complex<T>& c);
	Matrix<T> operator*(const Matrix<T>&);
	Matrix<T> operator*(T);
	Matrix<T> operator+(const Matrix<T>&);
	Matrix<T> operator-(const Matrix<T>&);
	void operator=(const Matrix<T>&);
	friend ostream& operator<<(ostream&, const Matrix<T>&);
	friend istream& operator>>(istream&, Matrix<T>&);

	bool invertible();//判断矩阵是否可逆
	Matrix<T> inversion1();//输出逆矩阵（伴随矩阵法）
	Matrix<T> inversion2();//输出逆矩阵（初等变换法）
	Matrix<T> transposition();//输出转置矩阵
	Matrix<T> orthogonalization();//输出列向量正交化后的矩阵
	Matrix<T> unitization();//输出列向量单位化后的矩阵
	T det();//输出行列式的值
	friend T innerProduct(const Matrix<T>&, const Matrix<T>&);//输出两个列向量的内积
	friend T innerProduct(const Matrix<T>& a, const int a1, const Matrix<T>& b, const int b1);//输出矩阵a的a1列和矩阵b的b1列代表的向量的内积

	void RowEchelon();//化为行阶梯形矩阵，求秩
	void RowSimplest();//化为行最简型矩阵，求秩
	void RowLSimplest();//化为行最简型矩阵,其左上角是单位阵，求秩

	bool HaveSolution();//判断该增广矩阵表示的方程组解的情况
	Matrix<T> SolvingEquations();//解方程组：this为齐次线性方程组的增广矩阵，输出基础解系

	Matrix();
	Matrix(int, int);
	Matrix(const Matrix<T>&);
	Matrix(fstream&);
	~Matrix();
};


