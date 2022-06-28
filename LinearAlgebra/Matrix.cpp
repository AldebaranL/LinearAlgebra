#include "Matrix.hpp"
const double zero = 0.0000000001;

template<class T> Matrix<T>::Matrix(int nn, int mm) {
	n = nn;
	m = mm;
	a = new T * [n];
	rank = 0;//需要调RowEchelon或RowSimplest函数才可算出！
	for (int i = 0; i < n; i++)
	{
		a[i] = new T[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = (T)0.0;
		}
	}
	//cout << "name?" << endl;
	//cin >> name;
}
template<class T> Matrix<T>::Matrix() {
	n = 0;
	m = 0;
	a = NULL;
	rank = 0;
}
template<class T> Matrix<T>::~Matrix() {
	//cout << name << "已释放！"<<n<<endl;
	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	n = 0;
	m = 0;
}
///*
template<class T> Matrix<T>::Matrix(fstream& fp) {
	fp >> n >> m;
	a = new T * [n];
	rank = 0;//需要调RowEchelon或RowSimplest函数才可算出！
	for (int i = 0; i < n; i++)
	{
		a[i] = new T[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fp >> a[i][j];
		}
	}
	//cout << "name?" << endl;
	//cin >> name;
}//*/
template<class T> Matrix<T>::Matrix(const Matrix<T>& m1) {
	m = m1.m;
	n = m1.n;
	rank = m1.rank;
	a = new T * [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new T[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = m1.a[i][j];
		}
	}
}
/*template<class T>void Matrix<T>::inputm() {
	ifstream ifile;
	ifile.open("data.txt", ios::in);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ifile >> a[i][j];
		}
	}
}
template<class T>void Matrix<T>::printm() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//	if (abs(a[i][j]) < zero) a[i][j] = (T)0.0;
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}*/

template<class T1> static double abs(T1 a1) {
	return std::abs((double)a1);
}
template <class T>Matrix<T> Matrix<T>::operator *(const Matrix<T>& n2) {
	Matrix<T> ans(n, n2.m);
	if (m != n2.n) {
		cout << "wrong@!" << m << ',' << n2.n << endl;
		return ans;
	}
	int p = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n2.m; j++) {
			for (int k = 0; k < p; k++) {
				ans.a[i][j] += a[i][k] * n2.a[k][j];
			}
		}
	}
	return ans;
}
template<class T>Matrix<T> Matrix<T>::operator *(T k) {
	Matrix<T> ans(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans.a[i][j] = k * (this->a[i][j]);
		}
	}
	return ans;
}
template <class T>Matrix<T>  Matrix<T>::operator +(const Matrix<T>& n2) {
	Matrix<T> ans(n, m);
	if ((m != n2.m) || (n != n2.n)) {
		cout << "wrong!" << endl;
		return ans;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n2.m; j++) {
			ans.a[i][j] = a[i][j] + n2.a[i][j];
		}
	}
	return ans;
}
template <class T>Matrix<T>  Matrix<T>::operator -(const Matrix<T>& n2) {
	Matrix<T> ans(n, m);
	if ((m != n2.m) || (n != n2.n)) {
		cout << "wrong!" << endl;
		return ans;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n2.m; j++) {
			ans.a[i][j] = a[i][j] - n2.a[i][j];
		}
	}
	return ans;
}
template<class T>void Matrix<T>::operator=(const Matrix<T>& n1) {
	if ((m != n1.m) || (n != n1.n)) {
		cout << "wrong!" << endl;
		return;
	}
	for (int i = 0; i < n1.n; i++) {
		for (int j = 0; j < n1.m; j++) {
			a[i][j] = n1.a[i][j];
		}
	}
}
template<class T> ostream& operator<<(ostream& output, const Matrix<T>& p) {
	for (int i = 0; i < p.n; i++) {
		for (int j = 0; j < p.m; j++) {
			//	if (abs(a[i][j]) < zero) a[i][j] = (T)0.0;
			cout << p.a[i][j] << " ";
		}
		output << endl;
	}
	return output;
}
template<class T> istream& operator>>(istream& input, Matrix<T>& p)
{
	int n, m;
	input >> n >> m;
	Matrix<T> ans(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			input >> ans.a[i][j];
		}
	}
	p = ans;
	return input;
}

template<class T>bool Matrix<T>::invertible() {
	if (m != n)return 0;
	Determinant<T> a1(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a1.a[i][j] = a[i][j];
		}
	}
	if (abs(a1.det()) <= 0.0001) return 0;
	return 1;
}
template<class T> T Matrix<T>::det() {
	Determinant<T> ans1(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans1.a[i][j] = a[i][j];
		}
	}
	return ans1.det();
}
template<class T>Matrix<T> Matrix<T>::inversion1() {
	Matrix<T> ans(n, m);
	if (!(this->invertible())) {
		cout << "不可逆！" << endl;
		return ans;
	}
	cout << "可逆！" << endl;
	Determinant ans1(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans1.a[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans.a[i][j] = ans1.cofactor(j + 1, i + 1);
		}
	}
	return ans * ((T)1.0 / ans1.det());
}
template<class T>Matrix<T> Matrix<T>::transposition() {
	Matrix<T> ans(m, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans.a[j][i] = a[i][j];
		}
	}
	return ans;
}
template<class T>static int change1(T** b, int l, int n, int m, int p) {
	if (abs(b[l][p]) > zero)return 0;
	for (int i = l + 1; i < n; i++) {
		if (abs(b[i][p]) > zero) {
			for (int j = 0; j < m; j++) {
				T t = b[l][j];
				b[l][j] = b[i][j];
				b[i][j] = t;
			}
			return 0;
		}
		else b[i][p] = (T)0.0;
	}
	return 1;
}
template<class T>void Matrix<T>::RowEchelon() {
	int r = 0;
	for (int i = 0; i < m && r < n; i++) {
		if (change1(a, r, n, m, i))continue;
		for (int j = r + 1; j < n; j++) {
			T c = ((T)-1.0) * a[j][i] / a[r][i];
			for (int k = i; k < m; k++) {
				a[j][k] += a[r][k] * c;
			}
		}
		r++;
	}
	//b.printm();
	rank = r;
	//cout << b.rank;
}
template<class T>void Matrix<T>::RowSimplest() {
	int r = 0;
	for (int i = 0; i < m && r < n; i++) {
		if (change1(a, r, n, m, i))continue;
		T t = (T)1.0 / a[r][i];
		for (int k = i; k < m; k++) {
			a[r][k] *= t;
		}
		for (int j = r + 1; j < n; j++) {
			if (abs(a[j][i]) < zero) {
				a[j][i] = (T)0.0;
				continue;
			}
			T c = ((T)-1.0) * a[j][i] / a[r][i];
			for (int k = i; k < m; k++) {
				a[j][k] += a[r][k] * c;
			}
		}
		for (int j = 0; j < r; j++) {
			if (abs(a[r][i]) < zero) {
				a[r][i] = (T)0.0;
				continue;
			}
			T c = ((T)-1.0) * a[j][i] / a[r][i];
			for (int k = i; k < m; k++) {
				a[j][k] += a[r][k] * c;
			}
		}
		r++;
	}
	//(*this).printm();
	rank = r;
	//cout << r;
}
template<class T>Matrix<T> Matrix<T>::inversion2() {
	Matrix<T> ans(n, m);
	if (!(this->invertible())) {
		cout << "不可逆！" << endl;
		return ans;
	}
	cout << "可逆！" << endl;
	Matrix<T> t(n, n * 2);
	Determinant<T> ans1(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			t.a[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < n; i++)t.a[i][i + n] = (T)1.0;
	t.RowSimplest();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans.a[i][j] = t.a[i][j + n];
		}
	}
	return ans;
}
template<class T>void Matrix<T>::RowLSimplest() {
	this->RowSimplest();
	for (int i = 0; i < rank; i++) {
		int j = 0;
		while (!a[i][j])j++;
		for (int k = 0; k < n; k++) {
			T t = a[k][j];
			a[k][j] = a[k][i];
			a[k][i] = t;
		}
	}
}
template<class T>bool Matrix<T>::HaveSolution() {
	Matrix<T> b(n, m - 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			b.a[i][j] = a[i][j];
		}
	}
	b.RowEchelon();
	Matrix<T> c(n, m);
	c = (*this);
	c.RowEchelon();
	if (c.rank == b.rank) {
		if (c.rank == m - 1) cout << "有唯一解" << endl;
		if (c.rank < m - 1) cout << "有无穷解" << endl;
		return 1;
	}
	else {
		cout << "无解" << endl;
		return 0;
	}
}
template<class T>Matrix<T> Matrix<T>::SolvingEquations() {
	this->RowLSimplest();
	//this->printm();
	//cout << this->rank;
	Matrix<T> b(m, m - this->rank);
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < m - rank; j++) {
			b.a[i][j] = -a[i][rank + j];
		}
	}
	for (int i = rank; i < m; i++)b.a[i][i - rank] = (T)1.0;
	//b.printm();
	return b;
}
template<class T> T innerProduct(const Matrix<T>& a, const int a1, const Matrix<T>& b, const int b1) {
	T ans = (T)0;
	if (a.n != b.n) {
		cout << "wrong!" << endl;
		return T;
	}
	for (int i = 0; i < a.n; i++) {
		ans += a.a[i][a1] * b.a[i][b1];
	}
	return ans;
}
template<class T>Matrix<T> Matrix<T>::orthogonalization() {
	Matrix<T> ans(n, m);
	if (m > n) {
		cout << "不可正交化！" << endl;
		return ans;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.a[i][j] = a[i][j];
	for (int j = 1; j < m; j++) {
		for (int k = 0; k < j; k++) {
			T coe = innerProduct(*this, j, ans, k) / innerProduct(ans, k, ans, k);
			for (int i = 0; i < n; i++) {
				ans.a[i][j] -= coe * ans.a[i][k];
			}
		}
	}
	return ans;
}
template<class T>Matrix<T> Matrix<T>::unitization() {
	Matrix<T> ans(n, m);
	for (int j = 0; j < m; j++) {
		T coe = innerProduct(*this, j, *this, j);
		coe = (T)1 / sqrt(coe);
		for (int i = 0; i < n; i++)
			ans.a[i][j] = a[i][j] * coe;
	}
	return ans;
}
