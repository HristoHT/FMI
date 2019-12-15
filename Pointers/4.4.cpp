#include<iostream>
using namespace std;

bool commonel(int *arrays[], int npointers, int arrLengths[]){
	for(int i = 0; i <  npointers; i ++){
		// arrays[i] - � �������, � ����� �� ������� ����, ��� ��� ������� arrLengths[i].
		for(int j = 0; j < arrLengths[i]; j ++){//��������� ���������� �� �������
			int currentElement = *(arrays[i] + j);//���� � ���������� �� j-��� ������� �� ������� arrays[i]
			for(int r = i + 1; r < npointers; r ++){//� ���� ����� �� ������� ������ �������� ������, �� �� �������� ���� currentElement �� �� ����� � ���.
				//� ������� �� ����������� �� ���������� �� ����� arrays[r], � ������� arrLengths[r]
				for(int h = 0; h < arrLengths[r]; h ++){//��������� ���������� �� ������ arrays[r]
					int elementToCheck = *(arrays[r] + h);//���� � ���������� �� h-��� ������� �� ������� arrays[r]
					if(elementToCheck == currentElement){
						return 1;//��� ����� �������� �������� ������ true
					}
				}
				
			}
	
		}
	}
	return 0;//��� ������ �� ���, ����� �� ��� �������� ��� ��������, ����� �� ��������.
}

int main() {
	int arr1[5] = {1, 2, 3, 4, 5}, arr2[3] = {6, 7, 8}, arr3[3] = {9, 1, 10}, // �������� ���, ����� �� ����� ���������� �� arrays. arrays[0] -> arr1
	    npointers = 3, //���� �� ��������
		arrLengths[3] = {5, 3, 3},// ��������� �� �������� arrLengths[0] == ��������� �� arr1
	    *arrays[3];//������� � ���������� ��� arr1, arr2, arr3;

	arrays[0] = arr1;
	arrays[1] = arr2;
	arrays[2] = arr3;
	
	cout << commonel(arrays, npointers, arrLengths);

}
