
#include <iostream>
#include "stdlib.h"
#define M 512
#define N 512
#define n 18
using namespace std;
int Integer_power(int num);
int path[M*M][8] = { 0 };
int Initialization[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1 };
int copy_type[44][3] = {
	0,0,0,  1,1,0,  2,2,0,  3,3,0,
	4,0,1,  5,1,1,  6,2,1,  7,3,1,
	8,0,2,  9,1,2,  10,2,2, 11,3,2,
	12,0,3, 13,1,3, 14,2,3, 15,3,3,
	16,0,4, 17,1,4, 18,2,4, 19,3,4,
	20,0,5, 21,1,5, 22,2,5, 23,3,5,
	24,0,6, 25,1,6, 26,2,6, 27,3,6,
	28,0,7, 29,1,7, 30,2,7, 31,3,7,
	32,0,8, 33,1,8, 34,2,8, 35,3,8,
	36,0,9, 37,1,9, 38,2,9, 39,3,9,
	40,0,10,41,1,10,42,2,10,43,3,10,

};
// There are $12$ different elementary matrices of Type $\rm{III}$ for
//$4\times 4$ matrices over $\mathbb{F}_{2^n}$
int Elementary_type[12][3] = {
	0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 1, 0,  4, 1, 2,  5, 1, 3,
	6, 2, 0, 7, 2, 1, 8, 2, 3, 9, 3, 0, 10, 3, 1, 11, 3, 2,
};
void linear(int Matrix[4][4][N], int alpha, int Elementary_number);
//If each submatrices is nonsingular, then Matrix_A is an MDS matrix.
int MDS(int Matrix_A[4][4][N]);

// alpha_1 and alpha_2 are belong to the finite ring.   alpha_3 = alpha_1 + alpha_2
void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);

// alpha_1 and alpha_2 are belong to the finite ring.   alpha_3 = alpha_1 * alpha_2
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);

// Elementary_number  is one of the $12$ different elementary matrices of Type $\rm{III}$
//Matrix_A=Elementary_number£¨alpha£© such as 
//Matrix_A=\overline{1}(alpha)=
// 1 alpha 0 0
// 0   1   0 0
// 0   0   1 0
// 0   0   0 1
void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number);

//Matrix_A,Matrix_B and Matrix_C are 4*4 matrix over the finite ring. 
//Matrix_C = Matrix_A + Matrix_B.
//void matrixadd(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);


//Matrix_A,Matrix_B and Matrix_C are 4*4 matrix over the finite ring. 
//Matrix_C = Matrix_A * Matrix_B.
//void matrixmult(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);


//Matrix = Elementary_number£¨alpha£©* Matrix
void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4]);
//Matrix = copy_number£¨alpha£©+ Matrix
void copy_operation(int copy_number, int alpha, int Matrix[4][4], int R[12][4]);

void copyer(int Matrix[4][4][N], int alpha, int copy_number, int Register_Matrix[12][4][N]);
//Remove the paths which induce matrices that always contain $0$.
int Step1(int leng[8]);


//Remove the paths which induce matrices with singular submatrices.
int Step2(int leng[8]);
void Printfmatrix(int  Matrix_A[4][4][N]);
// Printf path
void Printfpath(int leng[8]);
//void outMatrix(int Matrix[4][4]);
//void outpolynomialMatrix(int Matrix[4][4][N]);
int main()
{
	int B[4][4] = { 0 };
	int tt = 0;
	for (int i1 = 0; i1 < 20; i1++)
	{
		for (int i2 = 0; i2 < 24; i2++)
		{
			for (int i3 = 0; i3 < 28; i3++)
			{
				for (int c0 = 0; c0 < 32; c0++)
				{
					for (int c1 = 0; c1 < 36; c1++)
					{
						for (int c2 = 0; c2 < 40; c2++)
						{
							for (int c3 = 0; c3 < 44; c3++)
							{
								int leng[8] = { 14,i1,i2,i3,c0,c1,c2,c3 };
								int t1 = Step1(leng);
								if (t1 == 1)
								{
									int a = Step2(leng);
									if (a == 1)
									{
										Printfpath(leng);

										for (int i = 0; i < 8; i++)
										{
											path[tt][i] = leng[i];
										}
										tt = tt + 1;
									}
								}
							}
						}
					}
				}
			}
			cout << tt << endl;
		}
	}
	cout << tt << endl;
	/*for (int i = 0; i < tt; i++)
	{
		int a = Step2(path[i]);
		if (a == 1)
		{
			Printfpath(path[i]);
		}
	}*/
}

int Step1(int leng[8])
{
	int B[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1 };
	int R[12][4] = { 0 };
	R[0][0] = 1, R[1][1] = 1, R[2][2] = 1, R[3][3] = 1, R[4][2] = 1, R[4][3] = 1;
	int r = 5;

	for (int i = 1; i < 8; i++)///Copy_opreation(leng[i], 1, B)
	{
		copy_operation(leng[i], 1, B, R);
		for (int j = 0; j < 4; j++)
		{
			R[r][j] = B[copy_type[leng[i]][1]][j];
		}
		r++;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (B[i][j] == 0)
			{
				return 0;

			}
		}
	}

	return 1;


}
int Step2(int leng[8])
{
	int a = 0;
	// Let Temp_Matrix be a 4*4 matrix  and each  element can be expressed as sum array.  
	int Temp_Matrix[4][4][N] = { 0 };
	int Register_Matrix[12][4][N] = { 0 };
	Register_Matrix[0][0][0] = 1;
	Register_Matrix[1][1][0] = 1;
	Register_Matrix[2][2][0] = 1;
	Register_Matrix[3][3][0] = 1;
	Register_Matrix[4][2][0] = 1, Register_Matrix[4][3][0] = 2;
	transformation(Temp_Matrix, 1, leng[0]);
	int r = 5;

	for (int i = 1; i < 8; i++)
	{
		copyer(Temp_Matrix, i + 1, leng[i], Register_Matrix);
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; j < N; k++)
			{
				if (Temp_Matrix[copy_type[leng[i]][1]][j][k] == 0)break;
				Register_Matrix[r][j][k] = Temp_Matrix[copy_type[leng[i]][1]][j][k];
			}
		}
		r++;
	}
	a = MDS(Temp_Matrix);
	//Printfmatrix(Temp_Matrix);
	return a;

}
void Printfpath(int leng[8])
{
	for (int j = 0; j < 8; j++)
	{
		cout << leng[j] + 1 << " ";

	}
	cout << endl;
}

void Printfmatrix(int  Matrix_A[4][4][N])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < N; k++)
			{
				if (Matrix_A[i][j][k] == 0)
				{
					cout << Matrix_A[i][j][k] << " ";
					break;
				}
				cout << Matrix_A[i][j][k] << " ";
			}
			cout << ",";
		}
		cout << endl;

	}

}

void copy_operation(int copy_number, int alpha, int Matrix[4][4], int R[12][4])
{
	for (int i = 0; i < 4; i++)
	{
		Matrix[copy_type[copy_number][1]][i] = Matrix[copy_type[copy_number][1]][i] + R[copy_type[copy_number][2]][i] * alpha;
	}
}
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N])
{

	int t1 = 0;
	int t2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (alpha_1[i] > 0)
		{
			t1 = t1 + 1;
		}
		if (alpha_2[i] > 0)
		{
			t2 = t2 + 1;
		}
	}
	int d[N] = { 0 };
	int temp[N] = { 0 };
	int t = 0;
	for (int i = 0; i < t1; i++)
	{
		for (int j = 0; j < t2; j++)
		{
			t = alpha_1[i] | alpha_2[j];
			d[t] = d[t] ^ 1;

		}
	}

	t = 0;
	for (int i = N; i >= 0; i--)
	{
		if (d[i] == 1)
		{

			temp[t] = i;
			t = t + 1;

		}
	}

	for (int i = 0; i < N; i++)
	{
		alpha_3[i] = temp[i];
		//printf("%d\n", a[i]);
	}


}

void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N])
{

	int c[N] = { 0 };
	int t1 = 0;
	int t2 = 0;
	int t = 0;
	for (int i = 0; i < N; i++)
	{
		if (alpha_1[t1] > alpha_2[t2])
		{
			c[t] = alpha_1[t1];
			t1 = t1 + 1;
			t = t + 1;
		}
		else if (alpha_1[t1] < alpha_2[t2])
		{
			c[t] = alpha_2[t2];
			t2 = t2 + 1;
			t = t + 1;
		}
		else {
			t1 = t1 + 1;
			t2 = t2 + 1;
		}


	}
	for (int i = 0; i < N; i++)
	{
		alpha_3[i] = c[i];
	}

}

int MDS(int Matrix_A[4][4][N])
{
	int hh[36][4] = {
	0,1,0,1,0,1,0,2,0,1,0,3,0,1,1,2,0,1,1,3,0,1,2,3,
	0,2,0,1,0,2,0,2,0,2,0,3,0,2,1,2,0,2,1,3,0,2,2,3,
	0,3,0,1,0,3,0,2,0,3,0,3,0,3,1,2,0,3,1,3,0,3,2,3,
	1,2,0,1,1,2,0,2,1,2,0,3,1,2,1,2,1,2,1,3,1,2,2,3,
	1,3,0,1,1,3,0,2,1,3,0,3,1,3,1,2,1,3,1,3,1,3,2,3,
	2,3,0,1,2,3,0,2,2,3,0,3,2,3,1,2,2,3,1,3,2,3,2,3
	};
	int gh1[16][3] = {
		0,1,3,0,2,4,1,2,5,3,4,5,
		0,1,3,0,2,4,1,2,5,3,4,5,
		6,7,9,6,8,10,7,8,11,9,10,11,
		18,19,21,18,20,22,19,20,23,21,22,23
	};

	int gh2[16][3] = {
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1
	};
	int hg[4][3] = {
		0, 1, 2, 0, 1, 3, 0, 2, 3, 1, 2, 3 };
	int c[N] = { 0 }, d[N] = { 0 }, e[N] = { 0 }, f[N] = { 0 }, g[N] = { 0 };
	int temp[36][N];
	int tt = 0;
	// Verify the determinants of the 36 submatrices of order two 
	for (int i = 0; i < 36; i++)
	{
		multoper(Matrix_A[hh[i][0]][hh[i][2]], Matrix_A[hh[i][1]][hh[i][3]], c);
		multoper(Matrix_A[hh[i][1]][hh[i][2]], Matrix_A[hh[i][0]][hh[i][3]], d);
		addoper(c, d, e);
		int t = 0;
		for (int j = 0; j < N; j++)
		{
			temp[i][j] = e[j];
			if (e[j] > 0)
			{
				t = t + 1;

			}

		}
		if (t > 0)
		{
			tt = tt + 1;
		}
		else { return 0; }
	}
	if (tt == 36)
	{
		// Verify the determinants of the 16 submatrices of order three 
		for (int i = 0; i < 4; i++)
		{
			multoper(temp[gh1[i][0]], Matrix_A[2][gh2[i][0]], c);
			multoper(temp[gh1[i][1]], Matrix_A[2][gh2[i][1]], d);
			multoper(temp[gh1[i][2]], Matrix_A[2][gh2[i][2]], e);
			addoper(c, d, f);
			addoper(e, f, g);
			int t = 0;
			for (int j = 0; j < N; j++)
			{

				if (g[j] > 0)
				{
					t = t + 1;
					//printf("%d,", g[j]);
				}
			}
			//printf("\n");

			if (t > 0)
			{
				tt = tt + 1;

			}
			else { return 0; }

		}

		for (int i = 4; i < 16; i++)
		{
			multoper(temp[gh1[i][0]], Matrix_A[3][gh2[i][0]], c);
			multoper(temp[gh1[i][1]], Matrix_A[3][gh2[i][1]], d);
			multoper(temp[gh1[i][2]], Matrix_A[3][gh2[i][2]], e);
			addoper(c, d, f);
			addoper(e, f, g);
			int t = 0;
			for (int j = 0; j < N; j++)
			{
				if (g[j] > 0)
				{
					t = t + 1;
				}

			}
			//printf("\n");
			if (t > 0)
			{
				tt = tt + 1;

			}
			else { return 0; }
		}
		return  1;
	}

}
int Integer_power(int num)
{
	int s = 1;
	for (int i = 0; i < num; i++)
	{
		s = s * 2;
	}
	return s;

}
void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number)
{
	Matrix_A[0][0][0] = 1;
	Matrix_A[1][1][0] = 1;
	Matrix_A[2][2][0] = 1;
	Matrix_A[3][3][0] = 1;
	Matrix_A[2][3][0] = Integer_power(alpha);
}
void copyer(int Matrix[4][4][N], int alpha, int copy_number, int Register_Matrix[12][4][N])
{
	int temp1[4][N] = { 0 };
	int temp[N] = { Integer_power(alpha) };
	for (int i = 0; i < 4; i++)
	{
		multoper(temp, Register_Matrix[copy_type[copy_number][2]][i], temp1[i]);
		addoper(Matrix[copy_type[copy_number][1]][i], temp1[i], Matrix[copy_type[copy_number][1]][i]);
	}
}

