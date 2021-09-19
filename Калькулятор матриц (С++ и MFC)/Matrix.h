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
	matrix();//�� ��������� ������� 3�3 ������������������ ������
	matrix(int m1, int n1);
	matrix(int m1, int n1, int init);//�������������� ��� ���� ������� ��������� ����� ��������� init
	matrix(int m1, int n1, int *init);//������������� ���������� ��������
	matrix(const matrix& mx);
	~matrix() { delete[]p; }
	// �������� ������������
	matrix& operator = (const matrix& m);	// throw Bad_dimensions
	// �������� ��������������
	int* operator [] (long i) { return p[i]; };
	const int* operator [] (long i) const { return p[i]; };
	// ������� ���������
	matrix& operator += (const matrix& mx);	// throw Bad_dimensions
	matrix& operator -= (const matrix& mx);	// throw Bad_dimensions
	matrix& operator *= (const matrix& mx);	// throw Bad_dimensions
	matrix& operator *= (const int& d);
	// ������� ���������
	friend matrix operator -(const matrix& mx);
	friend matrix operator +(const matrix& mx);//!!�������� ���� ���� ������������� ���������, ����� ��������� �� ����� ������
	// �������� ���������
	friend matrix operator * (const int& d, const matrix& mx);
	friend matrix operator * (const matrix& mx, const int& d);
	// ��������� �������� ��������� 
	// ����� ��������� ���������� Bad_dimensions
	friend matrix operator + (const matrix& m1, const matrix& m2);
	friend matrix operator - (const matrix& m1, const matrix& m2);
	friend matrix operator * (const matrix& m1, const matrix& m2);
	//friend void Bad_dimensions();
	
	void chng_spc();
	std::string out();
	//������������ �������������� ������
	int *arr();
	void elmul(int m1, double value);//������������ ��������� ������ �� ������
	void swapr(int m1, int m2);//������ ������� 2 ������ � ���������� ��������
	void swapc(int n1, int n2);//������ ������� 2 ������� � ���������� ��������
	void print(int k);
	matrix minor(int x, int y);//�������� ����� ��� ��������� ������ � �������
	int det(matrix mx, int csize);//��������� ��� ���� ����� ������� ������������ ����������
	void elsadd(int mtarget, int msource);//������������ ����������� ������ � ������

	
};