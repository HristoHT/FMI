#include<iostream>
using namespace std;

bool subArrays(int *arrays[], int npointers, int arrLengths[]) {
	
	//������� �������� �� ���������� �� ��������. ����� 3 � �������� �� 1.
	for(int i = 0; i <  npointers; i ++) {
		for(int j = 0; j < arrLengths[i]; j ++) {
			cout << (arrays[i] + j) << " ";
		}
		cout << endl;
	}

	//���� ���� �� � ����� ������ �� �� ������ � ���������.
	for(int i = 0; i <  npointers; i ++) {
		// arrays[i] - � �������, � ����� �� ������� ����, ��� ��� ������� arrLengths[i].
		for(int j = 0; j < arrLengths[i]; j ++) { //��������� ���������� �� �������
			for(int r = i + 1; r < npointers; r ++) { //�� ����� ���� ������� �����
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
	return 0;//��� ������ �� ���, ����� �� ��� �������� ���������.
}

int main() {
	int arr1[5] = {1, 2, 3, 4, 5}, arr2[3] = {6, 7, 8}, // �������� ���, ����� �� ����� ���������� �� arrays. arrays[0] -> arr1
	npointers = 3, //���� �� ��������
	arrLengths[3] = {5, 3, 3},// ��������� �� �������� arrLengths[0] == ��������� �� arr1
	*arrays[3];//������� � ���������� ��� arr1, arr2, arr3;

	arrays[0] = arr1;
	arrays[1] = arr2;
	arrays[2] = &arr1[2];

	cout << subArrays(arrays, npointers, arrLengths);

}
