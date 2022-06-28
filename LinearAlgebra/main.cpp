//#include"Polynomial1.h"
#include "Matrix.hpp"
int main() {
	fstream file;
	file.open("data.txt", ios::in);
	//Polynomial1 p1,p2;
//	cin >> p1 >> p2;

	//cout << p1.calculate(5);
	//Polynomial1 p2();
	//p2.print();
	//(p1 * p2).print();
	//cout << "yes" << endl;
	//Matrix<Polynomial1> x1(file);

	Matrix<double> x1(file);
	//cin >> x1;
	//Matrix<double> x3(3,3);
	cout << x1;
	//x3 = x1.inversion2();
	//cout << ":" << endl; 
	//x3.printm();

	//x3.SolvingEquations().printm();
	//x1.RowEchelon();
	//x1.printm();
	//x1.inversion2().printm();
	return 0;
}
