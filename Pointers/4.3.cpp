#include<iostream>
using namespace std;

bool duplicates(long *pointers[]) { // Тук това е вече масив от пойнтъри *pointers[i] = а[i]
	for(int i = 0; i < 6; i ++){//За всяко i = 0,1...5
		for(int j = i + 1; j < 6; j ++){//За всяко j = i+1,i+2,..5
			if( *pointers[i] == *pointers[j] ) return 1;//Ако стойностите на два от пойнтърите са еднакви връщам 1 т.е. функцията казва, че е намериала първите два, които се повтарят
		}
	}
	
	return 0;
}

int main() {
	long a[6] = {1, 2, 3, 4, 5, 1};//Нормален масив от числа.
	long *ptrs[6];//Масив от поинтъри.
	for(int i = 0; i < 6; i ++){ // В ptrs[i] запазвам мястото в паметта, където е записано числото a[i], т.е. неговия пойнтър.
		ptrs[i] = &a[i];
	}
	if(duplicates(ptrs)) cout << "Ima" << endl;
	else cout << "Nqma" << endl;
}
