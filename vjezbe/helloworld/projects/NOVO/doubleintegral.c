// C++ program to calculate
// double integral value

#include <stdio.h>
#include <math.h>

// Change the function according to your need
float givenFunction(float x, float y)
{
	return pow(pow(x, 4) + pow(y, 5), 0.5);
}

// Function to find the double integral value
float doubleIntegral(float h, float k,
					float lx, float ux,
					float ly, float uy)
{
	int nx, ny;

	// z stores the table
	// ax[] stores the integral wrt y
	// for all x points considered
	float z[50][50], ax[50], answer;

	// Calculating the number of points
	// in x and y integral
	nx = (ux - lx) / h + 1;
	ny = (uy - ly) / k + 1;

	// Calculating the values of the table
	for (int i = 0; i < nx; ++i) {
		for (int j = 0; j < ny; ++j) {
			z[i][j] = givenFunction(lx + i * h,
									ly + j * k);
		}
	}

	// Calculating the integral value
	// wrt y at each point for x
	for (int i = 0; i < nx; ++i) {
		ax[i] = 0;
		for (int j = 0; j < ny; ++j) {
			if (j == 0 || j == ny - 1)
				ax[i] += z[i][j];
			else if (j % 2 == 0)
				ax[i] += 2 * z[i][j];
			else
				ax[i] += 4 * z[i][j];
		}
		ax[i] *= (k / 3);
	}

	answer = 0;

	// Calculating the final integral value
	// using the integral obtained in the above step
	for (int i = 0; i < nx; ++i) {
		if (i == 0 || i == nx - 1)
			answer += ax[i];
		else if (i % 2 == 0)
			answer += 2 * ax[i];
		else
			answer += 4 * ax[i];
	}
	answer *= (h / 3);

	return answer;
}

// Driver Code
int main()
{
	// lx and ux are upper and lower limit of x integral
	// ly and uy are upper and lower limit of y integral
	// h is the step size for integration wrt x
	// k is the step size for integration wrt y
	float h, k, lx, ux, ly, uy;

	lx = 2.3, ux = 2.5, ly = 3.7,
	uy = 4.3, h = 0.1, k = 0.15;

	printf("%f", doubleIntegral(h, k, lx, ux, ly, uy));
	return 0;
}
