#include<iostream>
using namespace std;

bool duplicates(long *pointers[]) { // ��� ���� � ���� ����� �� �������� *pointers[i] = �[i]
	for(int i = 0; i < 6; i ++){//�� ����� i = 0,1...5
		for(int j = i + 1; j < 6; j ++){//�� ����� j = i+1,i+2,..5
			if( *pointers[i] == *pointers[j] ) return 1;//��� ����������� �� ��� �� ���������� �� ������� ������ 1 �.�. ��������� �����, �� � ��������� ������� ���, ����� �� ��������
		}
	}
	
	return 0;
}

int main() {
	long a[6] = {1, 2, 3, 4, 5, 1};//�������� ����� �� �����.
	long *ptrs[6];//����� �� ��������.
	for(int i = 0; i < 6; i ++){ // � ptrs[i] �������� ������� � �������, ������ � �������� ������� a[i], �.�. ������� �������.
		ptrs[i] = &a[i];
	}
	if(duplicates(ptrs)) cout << "Ima" << endl;
	else cout << "Nqma" << endl;
}
