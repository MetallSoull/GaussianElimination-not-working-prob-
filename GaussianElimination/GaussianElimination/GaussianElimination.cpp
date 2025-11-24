#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int forwardElimination(vector<vector<double>>& matrix, int n) {
	for (int k = 0; k < n; ++k) {
		int i_max = k;
		double max_val = abs(matrix[k][k]);

		for (int i = k + 1; i < n; ++i) {
			if (abs(matrix[i][k]) > max_val) {
				max_val = abs(matrix[i][k]);
				i_max = i;
			}
		}
		if(i_max != k) {
			swap(matrix[k], matrix[i_max]);
		}

		if(matrix[k][k] == 0) {
			cerr << "Matrix is singular!" << endl;
			return -1;
		}

		for (int i = k + 1; i < n; ++i) {
			double factor = matrix[i][k] / matrix[k][k];
			for(int j = k; j <= n; ++j) {
				matrix[i][j] -= factor * matrix[k][j];
			}
		}
	}
	return -1;
}

void backSubstitution(const vector<vector<double>>& matrix, int n, vector<double>& solution) {
	for (int i = n - 1; i >= 0; --i) {
		solution[i] = matrix[i][n];
		for (int j = i + 1; j < n; ++j) {
			solution[i] -= matrix[i][j] * solution[j];
		}
		solution[i] /= matrix[i][i];
	}
}

void printSolution(const vector<double>& solution, int n) {
	cout << "Solution:" << endl;
	for (int i = 0; i < n; ++i) {
		cout << "x" << i << " = " << solution[i] << endl;
	}
}

int main() {
	int n;
	cout << "Enter number of equations: ";
	if (!(cin >> n)) {
		return 1;
	}
	vector<vector<double>> matrix(n, vector<double>(n + 1));	

	cout << "Enter augmented matrix coefficients row-wise: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j) {
			cout << "mat[" << i << "][" << j << "]: ";
			cin >> matrix[i][j];
		}
	}

	cout << "Augmented Matrix:" << endl;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j <= n; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	int singular_flag = forwardElimination(matrix, n);

	if(singular_flag != -1) {
		cout << "Singluar Matrix" << endl;
		if (matrix[singular_flag][n]) {
			cout << "Inconsistent System." << endl;
		} else {
			cout << "May have infinitely many solutions." << endl;
		}
		return 1;
	}

	vector<double> solution(n);
	backSubstitution(matrix, n, solution);
	printSolution(solution, n);

	return 0;

}
