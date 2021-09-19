#pragma once
#include <string>
class matrix
{
private:
	int n;//columns
	int m;//rows
	//(row,column)
	int **p;
public:
	matrix();//ѕо умолчанию матрица 3х3 инициализированна€ нул€ми
	matrix(int m1, int n1);
	matrix(int m1, int n1, int init);//»нициалищирует все пол€ матрицы выбранным целым значением init
	matrix(int m1, int n1, int *init);//»нициализаци€ ќƒЌќћ≈–Ќџћ массивом
	matrix(const matrix& mx);
	~matrix() { delete[]p; }
	// оператор присваивани€
	matrix& operator = (const matrix& m);	// throw Bad_dimensions
	// оператор индексировани€
	int* operator [] (long i) { return p[i]; };
	const int* operator [] (long i) const { return p[i]; };
	// унарные операторы
	matrix& operator += (const matrix& mx);	// throw Bad_dimensions
	matrix& operator -= (const matrix& mx);	// throw Bad_dimensions
	matrix& operator *= (const matrix& mx);	// throw Bad_dimensions
	matrix& operator *= (const int& d);
	// унарные операторы
	friend matrix operator -(const matrix& mx);
	friend matrix operator +(const matrix& mx);//!!»змен€ет знак всех ќ“–»÷ј“≈Ћ№Ќџ’ элементов, иначе операции€ не имеет смысла
	// бинарные операторы
	friend matrix operator * (const int& d, const matrix& mx);
	friend matrix operator * (const matrix& mx, const int& d);
	// следующие бинарные операторы 
	// могут выбросить исключение Bad_dimensions
	friend matrix operator + (const matrix& m1, const matrix& m2);
	friend matrix operator - (const matrix& m1, const matrix& m2);
	friend matrix operator * (const matrix& m1, const matrix& m2);
	//friend void Bad_dimensions();
	
	void chng_spc();
	std::string out();
	//Ёлементарные преобразовани€ матриц
	int *arr();
	void elmul(int m1, double value);//Ёлементарное умножение строки на скал€р
	void swapr(int m1, int m2);//ћен€ет местами 2 строки с указанными номерами
	void swapc(int n1, int n2);//ћен€ет местами 2 столбца с указанными номерами
	void print(int k);
	matrix minor(int x, int y);//¬ыбираем минор без указанной строки и столбца
	int det(matrix mx, int csize);//ѕараметры дл€ того чтобы считать определитель –екурсивно
	void elsadd(int mtarget, int msource);//Ёлементарное прибавление строки к строке

	
};