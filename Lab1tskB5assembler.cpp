// ������������� �����. ��������� �������� �� �������� ���� ����� ��������������.
// ��������� �� ����������
// 14.10.18 ���������� �. �. 8 ������
#include <iostream>
using namespace std;
int main() {
	int a, b, d2=0, f,f2, d = 1;
	cout << "enter 2 numbers\n";
	cin >> a>>b;
	// ����: ���� ������� �� �������=0, ���������� �������� � ���, ����� ����������� �������� �� 1 � ��������� �����
_asm {
		mov ecx, 0	
	del:
		add ecx, d2 //����� ����������� �������� �����, ���� ������� � edx=0
	cyc:
		mov eax, a	//������ ��� ��������� �������
		mov edx, 0	//�������� ������ �������
		div d
		mov ebx,d	
		mov d2,ebx	//��������� ��������
		add ebx,1	
		mov d,ebx	//����������� �������� �� 1
		mov eax,a
		cmp eax,d	//����������� ��������
		je ent
		cmp edx, 0
		je del
		jmp cyc
	ent: 
		mov f, ecx
	}
d2 = 0; d = 1;
_asm {
	mov ecx, 0
	del1:
	add ecx, d2
		cyc1 :
	mov eax, b
		mov edx, 0
		div d
		mov ebx, d
		mov d2, ebx
		add ebx, 1
		mov d, ebx
		mov eax, b
		cmp eax, d
		je ent1
		cmp edx, 0
		je del1
		jmp cyc1
		ent1 :
	mov f2, ecx
}
	cout <<"Sum of a div-rs: "<< f<< endl <<"Sum of b div-rs: "<< f2 << endl;
	if (a == f2 && b == f)
	cout << "friendly\n";
	else cout << "no\n";
	system("pause");
	return(0);
}
	//for (d = 2; d <= a / 2; d++)//���������� �������� ������� �����
	//{
	//	if (a%d == 0)
	//		c = c + d;
	//		}
	//for (f = 2; f <= b / 2; f++)//���������� �������� ������� �����
	//{
	//	if (b%f == 0)
	//		e = e + f;
	//}
	//if ((a == e) && (b == c))
			//cout << "friendly\n";
		//else cout << "no\n";
//test 220 284
//test 1184 1210
//test 5020 5564