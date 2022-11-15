#pragma warning(disable:4996);
#include <fstream>//ifstream读文件，ofstream写文件，fstream读写文件
#include <string>//文本对象，储存读取的内容

#include <cstdlib>//调用system("pause");


#include <stdint.h>
#include <cstring>
#include <time.h>
using namespace std;
#include <iostream>
#include "stdlib.h"
#define X 5
#define M 1024
#define N 128
#define Len 45//元素集合数
#define opera_num 9
int Lpath[M][opera_num] = { 0 };


int copy_type[48][3] = {
	0,0,0,
	1,1,0,
	2,2,0,
	3,3,0,
	4,0,1,
	5,1,1,
	6,2,1,
	7,3,1,
	8,0,2,
	9,1,2,
	10,2,2,
	11,3,2,
	12,0,3,
	13,1,3,
	14,2,3,
	15,3,3,
	16,0,4,
	17,1,4,
	18,2,4,
	19,3,4,
	20,0,5,
	21,1,5,
	22,2,5,
	23,3,5,
	24,0,6,
	25,1,6,
	26,2,6,
	27,3,6,
	28,0,7,
	29,1,7,
	30,2,7,
	31,3,7,
	32,0,8,
	33,1,8,
	34,2,8,
	35,3,8,
	36,0,9,
	37,1,9,
	38,2,9,
	39,3,9,
	40,0,10,
	41,1,10,
	42,2,10,
	43,3,10,
	44,0,11,
	45,1,11,
	46,2,11,
	47,3,11,
};
void Printfpath(int leng[opera_num]);
void printfpluspath(int path[opera_num], int location[X], int b[opera_num]);
int MDS(int Matrix_A[4][4][N]);
int Integer_power(int num);
int Pluspath(int path[opera_num], int location[X], int b[opera_num]);
void MP(int A[4][4][N]);
void copyer(int Matrix[4][4][N], int alpha, int copy_number, int bi, int Register_Matrix[20][4][N], int Alpha_Matrix[20][4][N]);
void diager(int Matrix[4][4][N], int alpha, int number);
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void copyshuzu(int path[opera_num], int location[X], int wh[opera_num]);
int path[18][8] = {
{	14	,	1	,	16	,	22	,	27	,	31	,	33	,	40	},
{	14	,	1	,	16	,	23	,	25	,	30	,	35	,	36	},
{	14	,	1	,	17	,	23	,	28	,	24	,	34	,	43	},
{	14	,	2	,	6	,	17	,	31	,	23	,	32	,	37	},
{	14	,	2	,	6	,	23	,	29	,	17	,	32	,	39	},
{	14	,	2	,	17	,	23	,	7	,	24	,	29	,	42	},
{	14	,	4	,	16	,	23	,	29	,	25	,	34	,	43	},
{	14	,	4	,	17	,	22	,	27	,	31	,	32	,	41	},
{	14	,	4	,	23	,	17	,	26	,	28	,	33	,	39	},
{	14	,	6	,	16	,	2	,	27	,	23	,	33	,	36	},
{	14	,	6	,	16	,	23	,	3	,	25	,	28	,	42	},
{	14	,	6	,	23	,	2	,	24	,	16	,	33	,	39	},
{	14	,	16	,	21	,	1	,	27	,	7	,	34	,	40	},
{	14	,	16	,	21	,	26	,	31	,	3	,	32	,	42	},
{	14	,	16	,	23	,	25	,	30	,	2	,	35	,	40	},
{	14	,	17	,	20	,	4	,	27	,	3	,	34	,	41	},
{	14	,	17	,	20	,	26	,	31	,	7	,	33	,	42	},
{	14	,	17	,	23	,	24	,	30	,	6	,	35	,	41	},


};
int main()
{
	FILE* fp = fopen("new.txt", "r");
	FILE* fp1 = fopen("pluspath(n=5（10-50).txt", "a");
	int n1 = 435;
	for (int k = 0; k < n1; k++)
	{
		for (int i = 0; i < opera_num; i++)
		{
			fscanf_s(fp, "%2d", &Lpath[k][i]);
		}
	}
	for (int K = 10; K < 50; K++)
	{
		for (int l0 = 0; l0 < Len; l0++)
		{
			for (int l1 = l0 + 1; l1 < Len; l1++)
			{
				for (int l2 = l1 + 1; l2 < Len; l2++)
				{
					for (int l3 = l2 + 1; l3 < Len; l3++)
					{
						for (int l4 = l3 + 1; l4 < Len; l4++)
						{
							int b[opera_num] = { 0 }, b1[opera_num] = { 1,1,1,1,1,1,1,1,1 };
							int location[5] = { l0,l1,l2,l3,l4 };
							copyshuzu(Lpath[K], location, b1);
							for (b[0] = 0; b[0] < b1[0]; b[0]++)
							{
								for (b[1] = 0; b[1] < b1[1]; b[1]++)
								{
									for (b[2] = 0; b[2] < b1[2]; b[2]++)
									{
										for (b[3] = 0; b[3] < b1[3]; b[3]++)
										{
											for (b[4] = 0; b[4] < b1[4]; b[4]++)
											{
												for (b[5] = 0; b[5] < b1[5]; b[5]++)
												{
													for (b[6] = 0; b[6] < b1[6]; b[6]++)
													{
														for (b[7] = 0; b[7] < b1[7]; b[7]++)
														{
															for (b[8] = 0; b[8] < b1[8]; b[8]++)
															{
																int SS = Pluspath(Lpath[K], location, b);
																if (SS == 1)
																{
																	//printfpluspath(Lpath[K], location, b);
																	for (int i = 0; i < opera_num; i++)
																	{
																		fprintf(fp1, "%d ", Lpath[K][i]);
																	}
																	for (int i = 0; i < opera_num; i++)
																	{
																		fprintf(fp1, "%d ", b[i]);
																	}
																	for (int i = 0; i < X; i++)
																	{
																		fprintf(fp1, "%d ", location[i]);
																	}
																	fprintf(fp1, "\n ");
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
	//cout << "time used: " << (double)(end - begin) / CLOCKS_PER_SEC << endl;
}
void printfpluspath(int path[opera_num], int location[X], int b[opera_num])
{
	for (int i = 0; i < opera_num; i++)
	{
		printf("%3d", path[i]);
	}
	for (int i = 0; i < opera_num; i++)
	{
		printf("%3d", b[i]);
	}
	for (int i = 0; i < X; i++)
	{
		printf("%3d", location[i]);
	}
	printf("\n");
}

int Pluspath(int path[opera_num], int location[X], int b[opera_num])
{
	int diag[opera_num][4] = {}, coffcopy[opera_num] = {}, num = 1;
	int Temp_Matrix[4][4][N] = { 0 }, Alpha_Matrix[20][4][N] = { 0 }, Register_Matrix[20][4][N] = { 0 };
	Alpha_Matrix[0][0][0] = Register_Matrix[0][0][0] = Temp_Matrix[0][0][0] = 1;
	Alpha_Matrix[1][1][0] = Register_Matrix[1][1][0] = Temp_Matrix[1][1][0] = 1;
	Alpha_Matrix[2][2][0] = Register_Matrix[2][2][0] = Temp_Matrix[2][2][0] = 1;
	Alpha_Matrix[3][3][0] = Register_Matrix[3][3][0] = Temp_Matrix[3][3][0] = 1;
	for (int i = 0; i < opera_num; i++)
	{
		coffcopy[i] = 1;
		for (int j = 0; j < 4; j++)
		{
			diag[i][j] = 1;
		}
	}
	for (int i = 0; i < X; i++)
	{
		if (location[i] % 5 == 0)
		{
			coffcopy[location[i] / 5] = Integer_power(num);
			num++;
		}
		else
		{
			int di = location[i] / 5;//D_i
			int dj = location[i] % 5 - 1;//D_i^j
			diag[di][dj] = Integer_power(num);
			num++;
		}
	}
	int r = 4;
	for (int i = 0; i < opera_num; i++)
	{
		copyer(Temp_Matrix, coffcopy[i], path[i], b[i], Register_Matrix, Alpha_Matrix);
		//MP(Temp_Matrix);
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < N; k++)
			{
				Alpha_Matrix[r][j][k] = Register_Matrix[r][j][k] = Temp_Matrix[copy_type[path[i]][1]][j][k];
			}
		}
		r++;
		for (int d = 0; d < 4; d++)
		{
			if (diag[i][d] > 1)
			{
				int r1 = 0;
				for (int z1 = 0; z1 < r; z1++)
				{
					int t1 = 0;
					for (int z2 = 0; z2 < 4; z2++)
					{
						int t2 = 0;
						for (int k = 0; k < 4; k++)
						{
							if (Temp_Matrix[d][z2][k] == Register_Matrix[z1][z2][k])
							{
								t2++;
							}
						}
						if (t2 < 4) break;
						else
						{
							t1++;
						}
					}
					if (t1 == 4)
					{
						r1 = z1;
						break;
					}
				}
				diager(Temp_Matrix, diag[i][d], d);
				//MP(Temp_Matrix);
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < N; k++)
					{
						Alpha_Matrix[r1][j][k] = Temp_Matrix[d][j][k];
					}
				}
			}
		}
	}
	int ss = MDS(Temp_Matrix);
	//MP(Temp_Matrix);
	/*if (ss == 1)
	{
		MP(Temp_Matrix);
	}*/
	return ss;
}
void Printfpath(int leng[opera_num])
{
	for (int j = 0; j < opera_num; j++)
	{
		cout << leng[j] << " ";
	}
	cout << endl;
}
void copyer(int Matrix[4][4][N], int alpha, int copy_number, int bi, int Register_Matrix[20][4][N], int Alpha_Matrix[20][4][N])
{
	int temp1[4][N] = { 0 };
	int temp[N] = { alpha };
	for (int i = 0; i < 4; i++)
	{
		if (bi == 0)
		{
			multoper(temp, Register_Matrix[copy_type[copy_number][2]][i], temp1[i]);
		}
		else
		{
			multoper(temp, Alpha_Matrix[copy_type[copy_number][2]][i], temp1[i]);
		}
		addoper(Matrix[copy_type[copy_number][1]][i], temp1[i], Matrix[copy_type[copy_number][1]][i]);
	}
}
void diager(int Matrix[4][4][N], int alpha, int number)
{
	int temp1[4][N] = { 0 };
	int temp[N] = { alpha };
	for (int j = 0; j < 4; j++)
	{
		multoper(temp, Matrix[number][j], Matrix[number][j]);
	}
	//MP(Matrix);
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Matrix_A[i][j][0] == 0)
			{
				return 0;
			}
		}
	}
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
void MP(int A[4][4][N])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			for (int k = 0; k < N; k++)
			{
				if (A[i][j][k] == 0)break;
				printf("%2d", A[i][j][k]);
			}
			printf(";");
		}
		printf("\n");
	}
	printf("\n");
}
void copyshuzu(int path[opera_num], int location[X], int b1[opera_num])
{
	int Temp_Matrix[4][4][N] = { 0 }, Alpha_Matrix[20][4][N] = { 0 }, Register_Matrix[20][4][N] = { 0 };
	Alpha_Matrix[0][0][0] = Register_Matrix[0][0][0] = Temp_Matrix[0][0][0] = 1;
	Alpha_Matrix[1][1][0] = Register_Matrix[1][1][0] = Temp_Matrix[1][1][0] = 1;
	Alpha_Matrix[2][2][0] = Register_Matrix[2][2][0] = Temp_Matrix[2][2][0] = 1;
	Alpha_Matrix[3][3][0] = Register_Matrix[3][3][0] = Temp_Matrix[3][3][0] = 1;
	int diag[opera_num][4] = {}, coffcopy[opera_num] = {}, num = 1, ww = 0, r = 4;
	int wh[opera_num] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		Alpha_Matrix[i][i][0] = Register_Matrix[i][i][0] = Temp_Matrix[i][i][0] = 1;
	}
	for (int i = 0; i < opera_num; i++)
	{
		coffcopy[i] = 1;
		for (int j = 0; j < 4; j++)
		{
			diag[i][j] = 1;
		}
	}
	for (int i = 0; i < X; i++)
	{
		if (location[i] % 5 == 0)
		{
			coffcopy[location[i] / 5] = Integer_power(num);
			num++;
		}
		else
		{
			int di = location[i] / 5;//D_i
			int dj = location[i] % 5 - 1;//D_i^j
			diag[di][dj] = Integer_power(num);
			num++;
		}
	}
	for (int i = 0; i < opera_num; i++)
	{
		copyer(Temp_Matrix, coffcopy[i], path[i], 0, Register_Matrix, Alpha_Matrix);
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < N; k++)
			{
				Alpha_Matrix[r][j][k] = Register_Matrix[r][j][k] = Temp_Matrix[copy_type[path[i]][1]][j][k];
			}
		}
		r++;
		for (int d = 0; d < 4; d++)
		{
			if (diag[i][d] > 1)
			{
				int r1 = 0;
				for (int z1 = 0; z1 < r; z1++)
				{
					int t1 = 0;
					for (int z2 = 0; z2 < 4; z2++)
					{
						int t2 = 0;
						for (int k = 0; k < N; k++)
						{
							if (Temp_Matrix[d][z2][k] == Register_Matrix[z1][z2][k])
							{
								t2++;
							}
						}
						if (t2 < N) break;
						else
						{
							t1++;
						}
					}
					if (t1 == 4)
					{
						wh[ww] = r1 = z1;
						ww++;
						break;
					}
				}
				diager(Temp_Matrix, diag[i][d], d);
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < N; k++)
					{
						Alpha_Matrix[r1][j][k] = Temp_Matrix[d][j][k];
					}
				}
			}
		}

	}
	for (int i = 0; i < opera_num; i++)
	{
		for (int j = 0; j < ww; j++)
		{
			if (copy_type[path[i]][2] == wh[j])
			{
				b1[i] = 2;
			}
		}
	}
}



