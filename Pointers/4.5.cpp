#include<iostream>
using namespace std;

bool subArrays(int *arrays[], int npointers, int arrLengths[]) {
	
	//Извежда адресите на елементите от масивите. Масив 3 е подмасив на 1.
	for(int i = 0; i <  npointers; i ++) {
		for(int j = 0; j < arrLengths[i]; j ++) {
			cout << (arrays[i] + j) << " ";
		}
		cout << endl;
	}

	//Това тука ми е малко трудно да го обясня с коментари.
	for(int i = 0; i <  npointers; i ++) {
		// arrays[i] - е масивът, с който ще работим сега, той има дължина arrLengths[i].
		for(int j = 0; j < arrLengths[i]; j ++) { //Обхождаме елементите на масивът
			for(int r = i + 1; r < npointers; r ++) { //За всеки един останал масив
				int h = 0;
				bool flag = 1;
				while( h < arrLengths[r] && h + j < arrLengths[i]) {
					if(arrLengths[r] + h != arrLengths[i] + h + j) flag = 0;
					h++;
				}
				if(flag)return 1;
			}

		}
	}
	return 0;//Ако стигне до тук, значи не сме намерили подмасиви.
}

int main() {
	int arr1[5] = {1, 2, 3, 4, 5}, arr2[3] = {6, 7, 8}, // Масивите към, които ще сочят пойнтърите от arrays. arrays[0] -> arr1
	npointers = 3, //Броя на масивите
	arrLengths[3] = {5, 3, 3},// Дължините на масивите arrLengths[0] == дължината на arr1
	*arrays[3];//Масивът с пойнтърите към arr1, arr2, arr3;

	arrays[0] = arr1;
	arrays[1] = arr2;
	arrays[2] = &arr1[2];

	cout << subArrays(arrays, npointers, arrLengths);

}
