#include<iostream>
using namespace std;

bool commonel(int *arrays[], int npointers, int arrLengths[]){
	for(int i = 0; i <  npointers; i ++){
		// arrays[i] - е масивът, с който ще работим сега, той има дължина arrLengths[i].
		for(int j = 0; j < arrLengths[i]; j ++){//Обхождаме елементите на масивът
			int currentElement = *(arrays[i] + j);//Това е стойността на j-тия елемент от масивът arrays[i]
			for(int r = i + 1; r < npointers; r ++){//С този цикъл ще обходим всички останали масиви, за да проверим дали currentElement не се среща в тях.
				//В момента ще проверяваме за елементите от масив arrays[r], с дължина arrLengths[r]
				for(int h = 0; h < arrLengths[r]; h ++){//Обхождаме елементите на масива arrays[r]
					int elementToCheck = *(arrays[r] + h);//Това е стойността на h-тия елемент от масивът arrays[r]
					if(elementToCheck == currentElement){
						return 1;//Ако двата елемента съвпадат връщам true
					}
				}
				
			}
	
		}
	}
	return 0;//Ако стигне до тук, значи не сме намерили два елемента, които да съвпадат.
}

int main() {
	int arr1[5] = {1, 2, 3, 4, 5}, arr2[3] = {6, 7, 8}, arr3[3] = {9, 1, 10}, // Масивите към, които ще сочят пойнтърите от arrays. arrays[0] -> arr1
	    npointers = 3, //Броя на масивите
		arrLengths[3] = {5, 3, 3},// Дължините на масивите arrLengths[0] == дължината на arr1
	    *arrays[3];//Масивът с пойнтърите към arr1, arr2, arr3;

	arrays[0] = arr1;
	arrays[1] = arr2;
	arrays[2] = arr3;
	
	cout << commonel(arrays, npointers, arrLengths);

}
