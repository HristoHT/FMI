#include<iostream>
using namespace std;
// ���� ������ �� ���� ����� ���� ��� � ��������, �� ��� � ����� ���������� �� ��������.
double sum(int n){
	if (n == 0)return 0;
	double a;
	cin >> a;
	return a + sum(--n);
}

int main(){
	int n;
	cin >> n;
	cout << sum(n) << endl;
}
