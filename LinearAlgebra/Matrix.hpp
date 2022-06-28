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
	int n, m;//n��m��
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

	bool invertible();//�жϾ����Ƿ����
	Matrix<T> inversion1();//�������󣨰�����󷨣�
	Matrix<T> inversion2();//�������󣨳��ȱ任����
	Matrix<T> transposition();//���ת�þ���
	Matrix<T> orthogonalization();//�����������������ľ���
	Matrix<T> unitization();//�����������λ����ľ���
	T det();//�������ʽ��ֵ
	friend T innerProduct(const Matrix<T>&, const Matrix<T>&);//����������������ڻ�
	friend T innerProduct(const Matrix<T>& a, const int a1, const Matrix<T>& b, const int b1);//�������a��a1�к;���b��b1�д�����������ڻ�

	void RowEchelon();//��Ϊ�н����ξ�������
	void RowSimplest();//��Ϊ������;�������
	void RowLSimplest();//��Ϊ������;���,�����Ͻ��ǵ�λ������

	bool HaveSolution();//�жϸ���������ʾ�ķ����������
	Matrix<T> SolvingEquations();//�ⷽ���飺thisΪ������Է����������������������ϵ

	Matrix();
	Matrix(int, int);
	Matrix(const Matrix<T>&);
	Matrix(fstream&);
	~Matrix();
};


