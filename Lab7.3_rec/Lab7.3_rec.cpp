#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
void Create(int** a, const int rowCount, const int colCount, const int Low,
	const int High, int i, int j);
void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);

int Result(int** a, const int k, const int n, int& S, int i, int j, int tmp);
void FindMinDiagonalSum(int** a, int k, int n, int start, int& minSum);
int DiagonalSum(int** a, int k, int n, int i, int j);
int main()
{
	srand((unsigned)time(NULL));
	int Low = -15;
	int High = 15;
	int k, n;
	cout << "k = "; cin >> k;
	cout << "n = "; cin >> n;
	int** a = new int* [k];
	for (int i = 0; i < k; i++)
		a[i] = new int[n];
	Create(a, k, n, Low, High,0,0);
	PrintRows(a, k, n,0);
	int S = 0;
	int minSum = abs(a[0][n - 1]) + DiagonalSum(a, k, n, 1, n - 2);
	Result(a, k, n, S,0,0,0);
	cout << "S = " << S << endl;
	FindMinDiagonalSum(a,k,n,0,minSum);
	cout << "S1 = " << minSum << endl;;


	for (int i = 0; i < k; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}
void Create(int** a, const int rowCount, const int colCount, const int Low,
	const int High, int i, int j)
{
	if (i < rowCount) {
		if (j < colCount) {
			a[i][j] = Low + rand() % (High - Low + 1);
			Create(a, rowCount, colCount, Low, High, j + 1, i);
		}
		Create(a, rowCount, colCount, Low, High, j, i + 1);
	}
}
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
	PrintRow(a, rowNo, colCount, 0);
	if (rowNo < rowCount - 1)
		PrintRows(a, rowCount, colCount, rowNo + 1);
	else
		cout << endl;
}
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < colCount - 1)
		PrintRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}
int Result(int** a, const int k, const int n, int& S, int i, int j, int tmp) {
	if (j >= n) {
		return S;
	}

	if (i >= k) {
		S += tmp;
		return Result(a, k, n, S, 0, j + 1, 0);
	}

	if (a[i][j] < 0) {
		return Result(a, k, n, S, 0, j + 1, 0); 
	}
	else {
		tmp += a[i][j];
		return Result(a, k, n, S, i + 1, j, tmp);
	}
}
int DiagonalSum(int** a, int k, int n, int i, int j) {
	
	if (i >= k || j < 0) return 0;

	
	return abs(a[i][j]) + DiagonalSum(a, k, n, i + 1, j - 1);
}


void FindMinDiagonalSum(int** a, int k, int n, int start, int& minSum) {
	
	if (start >= k + n - 1) return;

	int i, j;
	if (start < n) {  
		i = 0;
		j = start;
	}
	else {  
		i = start - n + 1;
		j = n - 1;
	}

	
	int tmp = DiagonalSum(a, k, n, i, j);

	
	if (tmp < minSum) {
		minSum = tmp;
	}

	
	FindMinDiagonalSum(a, k, n, start + 1, minSum);
}