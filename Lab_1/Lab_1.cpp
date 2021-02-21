#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void manualMatrixInp(int** matrix, int N, int M) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> matrix[i][j];
}

void randomlyGenMatrix(int** matrix, int N, int M) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			matrix[i][j] = rand() % 10;
}

void printMatrix(int** matrix, int N, int M) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void deleteArrOfMtrx(int*** matrix, int arrSize, int arrElemSize) {
	for (int i = 0; i < arrSize; i++)
		for (int j = 0; j < arrElemSize; j++)
			delete[] matrix[i][j];

	for (int i = 0; i < arrSize; i++)
		delete[] matrix[i];

}

void main()
{
	srand(time(NULL));
	int n1, m1, n2, m2, k, l = 2;
	system("chcp 1251");

	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";
	

	do 
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	
	do
	{
		cout << "Введите размеры второй матрицы\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);

	int** M1 = new int* [n1];
	for (int i = 0; i < n1; i++)
		M1[i] = new int[m1];

	int** M2 = new int* [n2];
	for (int i = 0; i < n2; i++)
		M2[i] = new int[m2];

	
	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> k;
	} while (k < 1 || k > 2);

	if (k == 1) {
		manualMatrixInp(M1, n1, m1);
		manualMatrixInp(M2, n2, m1);

		cout << "\nМатрица 1\n\n";
		printMatrix(M1, n1, m1);

		cout << "\nМатрица 2\n\n";
		printMatrix(M2, n2, m2);
	}
	else {
		randomlyGenMatrix(M1, n1, n2);
		randomlyGenMatrix(M2, n2, m2);

		cout << "\nМатрица 1\n\n";
		printMatrix(M1, n1, m1);

		cout << "\nМатрица 2\n\n";
		printMatrix(M2, n2, m2);
	}


	//Приведение матриц к требуемому размеру
	while (l < n1 || l < n2 || l < m1 || l < m2)
		l *= 2;
	
	int** reducedMtrx1 = new int* [l];
	int** reducedMtrx2 = new int* [l];

	for (int i = 0; i < l; i++) {
		reducedMtrx1[i] = new int[l];
		reducedMtrx2[i] = new int[l];
		for (int j = 0; j < l; j++) {
			reducedMtrx1[i][j] = 0;
			reducedMtrx2[i][j] = 0;
		}
	}

	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			reducedMtrx1[i][j] = M1[i][j];

	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			reducedMtrx2[i][j] = M2[i][j];
	
	cout << "\nПриведенные матрицы\n";
	
	cout << "\nМатрица 1\n\n";
	printMatrix(reducedMtrx1, l, l);

	cout << "\nМатрица 2\n\n";
	printMatrix(reducedMtrx2, l, l);


	//Создание массива разбиения матриц на подматрицы и их заполнение
	int*** submatrix = new int** [8];
	for (int i = 0; i < 8; i++)
	{
		submatrix[i] = new int* [l / 2];
		for (int j = 0; j < l / 2; j++)
			submatrix[i][j] = new int[l / 2];
	}

	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++) {
			submatrix[0][i][j] = reducedMtrx1[i][j];
			submatrix[1][i][j] = reducedMtrx1[i][j + l / 2];
			submatrix[2][i][j] = reducedMtrx1[i + l / 2][j];
			submatrix[3][i][j] = reducedMtrx1[i + l / 2][j + l / 2];
			submatrix[4][i][j] = reducedMtrx2[i][j];
			submatrix[5][i][j] = reducedMtrx2[i][j + l / 2];
			submatrix[6][i][j] = reducedMtrx2[i + l / 2][j];
			submatrix[7][i][j] = reducedMtrx2[i + l / 2][j + l / 2];
		}


	//Создание массива промежуточных матриц
	int*** p = new int** [7];
	for (int i = 0; i < 7; i++)
	{
		p[i] = new int* [l / 2];
		for (int j = 0; j < l / 2; j++)
			p[i][j] = new int[l / 2];
	}


	//Вычисление значений промежуточных матриц
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < l / 2; j++)
			for (int k = 0; k < l / 2; k++)
				p[i][j][k] = 0;

	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++)
			for (int z = 0; z < l / 2; z++) {
				p[0][i][j] += (submatrix[0][i][z] + submatrix[3][i][z]) * (submatrix[4][z][j] + submatrix[7][z][j]);
				p[1][i][j] += (submatrix[2][i][z] + submatrix[3][i][z]) * submatrix[4][z][j];
				p[2][i][j] += submatrix[0][i][z] * (submatrix[5][z][j] - submatrix[7][z][j]);
				p[3][i][j] += submatrix[3][i][z] * (submatrix[6][z][j] - submatrix[4][z][j]);
				p[4][i][j] += (submatrix[0][i][z] + submatrix[1][i][z]) * submatrix[7][z][j];
				p[5][i][j] += (submatrix[2][i][z] - submatrix[0][i][z]) * (submatrix[4][z][j] + submatrix[5][z][j]);
				p[6][i][j] += (submatrix[1][i][z] - submatrix[3][i][z]) * (submatrix[6][z][j] + submatrix[7][z][j]);
			}


	//Создание вспомогательных матриц
	int*** suppMatrix = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		suppMatrix[i] = new int* [l / 2];
		for (int j = 0; j < l / 2; j++)
			suppMatrix[i][j] = new int[l / 2];
	}

	
	//Подсчет значений вспомогательных матриц из промежуточных
	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++)
		{
			suppMatrix[0][i][j] = p[0][i][j] + p[3][i][j] - p[4][i][j] + p[6][i][j];
			suppMatrix[1][i][j] = p[2][i][j] + p[4][i][j];
			suppMatrix[2][i][j] = p[1][i][j] + p[3][i][j];
			suppMatrix[3][i][j] = p[0][i][j] - p[1][i][j] + p[2][i][j] + p[5][i][j];
		}

	
	//Создание результирующей матрицы
	int** preResultMtrx = new int* [l];
	for (int i = 0; i < l; i++)
		preResultMtrx[i] = new int[l];


	//Занесение информации из вспомогательных матриц в результирующую
	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++)
		{
			preResultMtrx[i][j] = suppMatrix[0][i][j];
			preResultMtrx[i][j + l / 2] = suppMatrix[1][i][j];
			preResultMtrx[i + l / 2][j] = suppMatrix[2][i][j];
			preResultMtrx[i + l / 2][j + l / 2] = suppMatrix[3][i][j];
		}

	
	//Выравнивание границ результирующей матрицы
	int x = 0, f = 100, s = 100;
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
			if (preResultMtrx[i][j] != 0)
			{
				x++;
				f = 100;
			}

		if (x == 0 && i < f)
			f = i;
	}

	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
			if (preResultMtrx[j][i] != 0)
			{
				x++;
				s = 100;
			}

		if (x == 0 && i < s)
			s = i;
	}

	int** resultMtrx = new int* [f];
	for (int i = 0; i < f; i++)
	{
		resultMtrx[i] = new int[s];
		for (int j = 0; j < s; j++)
			resultMtrx[i][j] = preResultMtrx[i][j];
	}

	cout << "\nРезультирующая матрица\n\n";
	printMatrix(resultMtrx, f, s);

	system("pause");


	//Освобождение памяти
	for (int i = 0; i < n1; i++)
		delete[] M1[i];

	for (int i = 0; i < n2; i++)
		delete[] M2[i];

	for (int i = 0; i < l; i++)
	{
		delete[] reducedMtrx1[i];
		delete[] reducedMtrx2[i];
		delete[] preResultMtrx[i];
	}

	for (int i = 0; i < f; i++)
		delete[] resultMtrx[i];

	delete[] M1, M2, reducedMtrx1, reducedMtrx2, preResultMtrx, resultMtrx;

	deleteArrOfMtrx(submatrix, 8, l / 2);
	deleteArrOfMtrx(p, 7, l / 2);
	deleteArrOfMtrx(suppMatrix, 4, l / 2);

	delete[] p, submatrix, suppMatrix;
}