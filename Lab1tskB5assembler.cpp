// Дружественные числа. Првоерить является ли заданная пара чисел дружественными.
// Выполнено на ассемблере
// 14.10.18 Пашковский Л. П. 8 группа
#include <iostream>
using namespace std;
int main() {
	int a, b, d2=0, f,f2, d = 1;
	cout << "enter 2 numbers\n";
	cin >> a>>b;
	// СУТЬ: если остаток от деления=0, прибавляем делитель в есх, иначе увеличиваем делитель на 1 и проверяем снова
_asm {
		mov ecx, 0	
	del:
		add ecx, d2 //здесь суммируются делители числа, если остаток в edx=0
	cyc:
		mov eax, a	//каждый раз обновляем делимое
		mov edx, 0	//обнуляем ячейку остатка
		div d
		mov ebx,d	
		mov d2,ebx	//сохраняем делитель
		add ebx,1	
		mov d,ebx	//увеличиваем делитель на 1
		mov eax,a
		cmp eax,d	//Ограничение перебора
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
	//for (d = 2; d <= a / 2; d++)//складываем делители первого числа
	//{
	//	if (a%d == 0)
	//		c = c + d;
	//		}
	//for (f = 2; f <= b / 2; f++)//складываем делители второго числа
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