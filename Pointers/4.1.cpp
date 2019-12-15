#include<iostream>
using namespace std;
void swapArr(int *a, int *b, int n) {
	for(int i = 0; i < n; i ++) {
		int *ptr = a + n, *ptrA = a + i, *ptrB = b + i;
		cout << a + i << " " << *(a + i) << endl;
		*ptr = *(a + i);
		*ptrA = *(b + i);
		*ptrB = *ptr;
	}
}

int main() {
	int arr1[3] = { 1, 2, 3}, arr2[3] = { 4, 5, 6};
	swapArr(arr1, arr2, 3);
	for(int i = 0; i < 3; i ++) {
		cout << *arr1 + i << " " << *arr2 + i << endl;
	}
}
