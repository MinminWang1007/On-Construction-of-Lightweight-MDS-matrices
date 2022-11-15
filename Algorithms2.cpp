#include <fstream>//ifstream读文件，ofstream写文件，fstream读写文件
#include <string>//文本对象，储存读取的内容
#include <cstdlib>//调用system("pause");
#include<vector>
#include<algorithm>
#include <stdint.h>
#include <cstring>
#include <time.h>
#include <iostream>
#include "stdlib.h"
using namespace std;
#define M 1024
#define N 64
#define dim 4
#define num_non_xor_zero 3
#define path_leng 8
int nn = 0;
int Mult_finite_field[16][16] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13,
0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2,
0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9,
0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6,
0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4,
0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11,
0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1,
0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14,
0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12,
0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3,
0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8,
0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7,
0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5,
0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10,
};
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

void equal(int  Matrix_A[M][4][4], int count);
int array_num[8][num_non_xor_zero] = { 2,2,2,2,2,9,2,9,2,2,9,9,9,2,2,9,2,9,9,9,2,9,9,9 };
int element_finite(int element[N], int array_element[num_non_xor_zero]);
int path_position[M][4][4][N] = { 0 };
int MDS_matrix[M][4][4] = { 0 };
int find_the_path_with_position(int leng[], int count, vector <vector<int> >vector_array[2]);
void Generate_matrix(int leng[], int count,  int register_set[], int Temp_Matrix[4][4][N], int h[12]);
void combine1(int count, int  num, vector <vector<int> >vector_array[2]);
void Comb(int index, int begin, int len, int nm, int *A, int *C, vector <vector<int> >vector_array[2]);
void Initialization(int Matrix_A[4][4][N]);
int MDS(int Matrix_A[4][4][N]);
int Integer_power(int num);
void copyer(int Matrix[4][4][N], int alpha, int copy_number, int Register_Matrix[12][4][N]);
void diager(int Matrix[4][4][N], int alpha[4]);
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void Printfmatrix(int  Matrix_A[4][4][N]);
int Generate_U(int leng[], int element_set[], int U_k[][8]);
int gen_vector(int vector[], int  temp[]);
int Judge_MDS(int Matrix[4][4]);
int equal_two_row_matrix(int matrix_a[4][4], int matrix_b[4][4]);
void finitefiledelement(int finite[44], int array[3]);
void equal_element(int  Matrix_A[M][4][4][N], int count);
void Generate_matrix_finite_field(int leng[], int count, int Temp_Matrix_finite_field[4][4], int element_set_finite_field[], int h[]);
int equal_two_matrix_element(int matrix_a[4][4][N], int matrix_b[4][4][N]);
int equal_two_matrix(int matrix_a[4][4], int matrix_b[4][4]);
int main()
{
	vector <vector<int> >vector_array[2];
	int count = 8;
	combine1(44, num_non_xor_zero, vector_array);
	for (int i = 0; i < 18; i++)
	{
		find_the_path_with_position(path[i], 8, vector_array);

	}

	equal_element(path_position, nn);
	//cout << nn << endl;



	int kk = 0;
	for (int k = 0; k < 8; k++) {
		for (int s = 0; s < nn; s++)
		{
			int temp_matrix_element_finite[4][4] = { 0 };
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{

					temp_matrix_element_finite[i][j] = element_finite(path_position[s][i][j], array_num[k]);
				}


			}
			if (Judge_MDS(temp_matrix_element_finite) == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{

						MDS_matrix[kk][i][j]= temp_matrix_element_finite[i][j];
						//cout << MDS_matrix[kk][i][j] << ", ";
					}


				}
				//cout << endl;
				kk++;
			}

		}
	}

	cout << equal_two_matrix(MDS_matrix[0], MDS_matrix[4]);

	equal(MDS_matrix, kk);

	//cout << kk << endl;
	//int h[12] = { 0,0,0,0,0,0,0,0,0,1,0,0 };
	////
	////int U_k[32][8] = { 0 };
	//////////int array[3] = { 0,0,0 };
	//int element_set_finite_field[44] = { 0 };

	//////////for (int i = 0; i < 44; i++)
	//////////{
	//////////	element_set_finite_field[i] = 0;
	//////////}
	//int Temp_Matrix[4][4][N] = { 0 };
	//element_set_finite_field[15] = 1;
	//element_set_finite_field[18] = 2;
	//element_set_finite_field[32] = 3;
	//Generate_matrix(path[0], 8,  element_set_finite_field,  Temp_Matrix,  h);
	//if (MDS(Temp_Matrix) == 1)
	//{
	//	//cout << i << endl;

	//	Printfmatrix(Temp_Matrix);
	//	
	//}
	//int array[3] = { 2,9,9 };
	//int a[4][4] = { 0 };
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{

	//		a[i][j] = element_finite(Temp_Matrix[i][j], array);
	//		cout << a[i][j] << " ";
	//	}
	//	cout <<  endl;

	//}
	//cout << Judge_MDS(a) << endl;


	//Generate_U(path[0], element_set_finite_field, U_k);
	//Generate_matrix_finite_field(path[0], 8, Temp_Matrix, element_set_finite_field, h);
}







int find_the_path_with_position(int leng[], int count, vector <vector<int> >vector_array[2])
{
	for (int i = 0; i < 8; i++)
	{
		cout << leng[i]<<", ";
	}
	cout << endl;
	

	for (int i = 0; i < vector_array[1].size(); i++)
	{
		
		//cout << i << endl;
		int element_set[44] = { 0 };
		for (int j = 0; j < 44; j++)
		{
			element_set[j] = vector_array[0][i][j];
			
		}
		int U_k[32][8] = { 0 };
		int num_array = Generate_U(leng, element_set, U_k);
		//int h[12] = { 0,0,0,0,0,0,0,0,0,1,0,0 };






		for (int numb = 0; numb < num_array; numb++)
		{
			
			int Temp_Matrix[4][4][N] = { 0 };
			int h[12] = { 0 };

			for (int i = 4; i < 12; i++)
			{
				h[i] = U_k[numb][i - 3];
			}
			
			Generate_matrix(leng, count, element_set, Temp_Matrix,h);
		
			if (MDS(Temp_Matrix) == 1)
			{
				//cout << i << endl;

				//Printfmatrix(Temp_Matrix);
				for (int l = 0; l < 4; l++)
				{
					for (int j = 0; j < 4; j++)
					{
						for (int k = 0; k < N; k++)
						{
							if (Temp_Matrix[l][j][k] == 0)
							{

								break;
							}

							path_position[nn][l][j][k] = Temp_Matrix[l][j][k];


						}

					}


				}
					nn++;
				

			
			}
			

		}

	}


	return 0;




}
void Generate_matrix(int leng[], int count, int element_set[], int Temp_Matrix[4][4][N],int h[12])
{
	
		
	
	Initialization(Temp_Matrix);

	int Register_Matrix[4][12][4][N] = { 0 };
	Register_Matrix[0][0][0][0] = 1;
	Register_Matrix[0][1][1][0] = 1;
	Register_Matrix[0][2][2][0] = 1;
	Register_Matrix[0][3][3][0] = 1;
	int r = 3;
	int num = 4;
	int t[12] = { 0 };

	int cadidate[4] = { 0,1,2,3 };

	//cout << "  dd" << endl;
	for (int i = 0; i < 8; i++)
	{
		int temp_D[4] = { element_set[num],element_set[num + 1],element_set[num + 2],element_set[num + 3] };
		diager(Temp_Matrix, temp_D);
		for (int s = 0; s < 4; s++)
		{
			if (element_set[num + s] > 0)
			{
				t[cadidate[s]]++;
				for (int j = 0; j < 4; j++)
				{
					int temp[N] = { Integer_power(element_set[num + s]) };
					multoper(Temp_Matrix[s][j], temp, Register_Matrix[t[cadidate[s]]][cadidate[s]][j]);

				}

			}

		}
		num = num + 4;
		copyer(Temp_Matrix, element_set[num], leng[i], Register_Matrix[h[r]]);
		r++;
		num++;
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < N; k++)
			{
				if (Temp_Matrix[copy_type[leng[i]][1]][j][k] == 0)break;
				Register_Matrix[0][r][j][k] = Temp_Matrix[copy_type[leng[i]][1]][j][k];
			}
		}
		cadidate[copy_type[leng[i]][1]] = r;

	}




}
int Generate_U(int leng[], int element_set[],int U_k[][8])
{
	int r = 3;
	int num = 4;
	int t[12] = { 0 };
	int cadidate[4] = { 0,1,2,3 };
	for (int i = 0; i < 8; i++)
	{
		int temp_D[4] = { element_set[num],element_set[num + 1],element_set[num + 2],element_set[num + 3] };
		for (int s = 0; s < 4; s++)
		{
			if (element_set[num + s] > 0)
			{
				t[cadidate[s]]++;

			}

		}
		num = num + 4;
		r++;
		num++;
		cadidate[copy_type[leng[i]][1]] = r;

	}
	int vector[8] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		vector[i] = t[copy_type[leng[i]][2]];
	}



	int a = 1;
	int temp[8] = { 0 };
	int count = 0;
	while (a)
	{

		for (int i = 0; i < 8; i++)
		{

			U_k[count][i] = temp[i];
			//cout << temp[i] << " ";
		}
		
		//cout << endl;
		a = a ^ gen_vector(vector, temp);

		count++;

	}


	return count;
}



int gen_vector(int vector[8], int  temp[8])
{

	
	for (int i = 0; i < 8; i++)
	{
		if (temp[i] < vector[i])
		{
			temp[i]++;
			return 0;
		}
		else {
			
			for (int k = 0; k < 8 - i; k++)
			{
				if (temp[k] < vector[k])
				{
					temp[k]++;


					for (int j = 0; j < k; j++)
					{
						temp[j] = 0;
					}
					return 0;
				}
			}
		}
	}
	return 1;

}
int element_finite(int element[N] , int array_element[3])
{
	int temp = 0;
	
	for (int i = 0; i < N; i++)
	{
		int tem = 1, c = 0;
		if (element[i] == 0)
		{
			return temp;
		}
		
		for (int j = 1; j < 4; j++)
		{
			c = (element[i] >> j) & 1;
			//cout << c << " ";
			if (c == 0)
			{
				tem = tem;
			}
			else
			{
				
				tem = Mult_finite_field[tem][array_element[j-1]];
				
				
			}
			
			
		}
		
		temp = temp ^ tem;
	}
	return 0;
}




int Judge_MDS(int Matrix[4][4])
{
	int hh[36][4] = {
	0,1,0,1,0,1,0,2,0,1,0,3,0,1,1,2,0,1,1,3,0,1,2,3,
	0,2,0,1,0,2,0,2,0,2,0,3,0,2,1,2,0,2,1,3,0,2,2,3,
	0,3,0,1,0,3,0,2,0,3,0,3,0,3,1,2,0,3,1,3,0,3,2,3,
	1,2,0,1,1,2,0,2,1,2,0,3,1,2,1,2,1,2,1,3,1,2,2,3,
	1,3,0,1,1,3,0,2,1,3,0,3,1,3,1,2,1,3,1,3,1,3,2,3,
	2,3,0,1,2,3,0,2,2,3,0,3,2,3,1,2,2,3,1,3,2,3,2,3
	};
	int hg[4][3] = {
		0, 1, 2, 0, 1, 3, 0, 2, 3, 1, 2, 3 };
	int c, d, e, m;
	int g[68] = { 0 };
	int a[3][3];
	int b[3];
	for (int i = 0; i < 36; i++)
	{
		c = Matrix[hh[i][0]][hh[i][2]];
		d = Matrix[hh[i][1]][hh[i][3]];
		e = Matrix[hh[i][1]][hh[i][2]];
		m = Matrix[hh[i][0]][hh[i][3]];
		g[i] = Mult_finite_field[c][d]^ Mult_finite_field[e][m];
	
		if (g[i] == 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		
		for (int j = 0; j < 4; j++)
		{
			
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)

				{
					a[k][l] = Matrix[hg[i][k]][hg[j][l]];
					
				}
				
			}
		
			b[0] = Mult_finite_field[a[1][1]][a[2][2]]^Mult_finite_field[a[1][2]][a[2][1]];
			b[1] = Mult_finite_field[a[1][0]][a[2][2]]^Mult_finite_field[a[1][2]][a[2][0]];
			b[2] = Mult_finite_field[a[1][1]][a[2][0]]^Mult_finite_field[a[1][0]][a[2][1]];

		

			g[36 + 4 * i + j] = Mult_finite_field[b[0]][a[0][0]]^ Mult_finite_field[a[0][1]][b[1]]^ Mult_finite_field[a[0][2]][b[2]];
			if (g[36 + 4 * i + j] == 0)
			{
				return 0;
			}
		}


	}
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			g[52 + 4 * i + j] = Matrix[i][j];
			if (g[52 + 4 * i + j] == 0)
			{
				return 0;
			}
		}
	}
	

	return  1;
	

}

void finitefiledelement(int finite[44],int array[3])
{
	int temp[44] = { 0 };
	int count = 0;
	int temp_count = 0;
	for (int i = 0; i < 44; i++)
	{
		
		if (finite[i] == 0)
		{
			temp[count] = 1;
		}
		else { 
			temp[count] = array[temp_count];
			temp_count++;
		}
		count++;
	}
	for (int i = 0; i < 44; i++)
	{
		finite[i] = temp[i];
	}
}








void combine1(int count, int  num, vector <vector<int> >vector_array[2])
{

	int A[20] = { 0 };
	for (int i = 1; i < count; i++)
	{
		A[i] = i;
		//cout << A[i];
	}
	int len = count, nm = num;
	int *C = new int[nm + 1];
	Comb(0, 0, len, nm, A, C, vector_array);

	for (int i = 0; i < vector_array[1].size(); i++)
	{
		vector<int>v_array;
		int AA[M] = { 0 };
		int t = 1;
		for (int j = 0; j < num; j++)
		{
			AA[vector_array[1][i][j]] = t;

			t++;
		}
		for (int j = 0; j < count; j++)
		{

			v_array.push_back(AA[j]);
		}
		vector_array[0].push_back(v_array);

	}


	//for (int i = 0; i < vector_array[1].size(); i++)
	//{


	//	for (int j = 0; j < count; j++)
	//	{

	//		cout << vector_array[0][i][j] << "  ";
	//	}
	//	cout << endl;
	//}
	//cout << vector_array[1].size() << endl;
}
void Comb(int index, int begin, int len, int nm, int *A, int *C, vector <vector<int> >vector_array[2])
{                                // index表示某个组合中的索引，begin表示从数组A中begin位置开始寻找，
//  len表示数组A长度，n表示组合中个数，A表示原数组，C表示组合数组

	if (index == nm)
	{
		vector<int>v_array;
		for (int i = 0; i < nm; i++)
		{
			//cout << C[i] << " ";
			v_array.push_back(C[i]);

		}
		vector_array[1].push_back(v_array);
		//cout << vector_array[0].size() << endl;
		//cout << endl;

		return;
	}
	for (int j = begin; j <= len - nm + index; j++)
	{
		C[index] = A[j];
		Comb(index + 1, j + 1, len, nm, A, C, vector_array);
	}
}
void Initialization(int Matrix_A[4][4][N])
{
	for (int i = 0; i < dim; i++)
	{
		Matrix_A[i][i][0] = 1;
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

	}
	return  1;
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
void copyer(int Matrix[4][4][N], int alpha, int copy_number, int Register_Matrix[12][4][N])
{
	int temp1[4][N] = { 0 };
	int temp[N] = { Integer_power(alpha) };
	//Printfmatrix(Matrix);
	for (int i = 0; i < 4; i++)
	{
		multoper(temp, Register_Matrix[copy_type[copy_number][2]][i], temp1[i]);
		addoper(Matrix[copy_type[copy_number][1]][i], temp1[i], Matrix[copy_type[copy_number][1]][i]);
	}

	




}
void diager(int Matrix[4][4][N], int alpha[4])
{
	int temp[4][N] = { {Integer_power(alpha[0])},{Integer_power(alpha[1])},{Integer_power(alpha[2])},{Integer_power(alpha[3])} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			multoper(temp[i], Matrix[i][j], Matrix[i][j]);
		}
	}
	//MP(Matrix);
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

void equal(int  Matrix_A[M][4][4],int count)
{
	int temp_array[M] = { 0 };
	int a = 1;
	for (int i = 0; i < count; i++)
	{
		if (temp_array[i] == 0)
		{
			temp_array[i] = a;
			for (int j = i + 1; j < count; j++)
			{

				if (equal_two_matrix(Matrix_A[i], Matrix_A[j]) == 1)
				{
					temp_array[j] = a;
				}

			}
			a++;
		}
	}
	//for (int i = 0; i < count; i++)
	//{
	//	cout << temp_array[i] << ",";
	//}
	cout << endl;
	cout << a-1 << endl;

	for (int k = 1; k < a; k++)
	{
		for (int s = 0; s < count; s++)
		{
			if (temp_array[s] == k)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						cout << Matrix_A[s][i][j] << ", ";
					}

				}
				cout << endl;
				break;
			}
		}
	}



}
int equal_two_row_matrix(int matrix_a[4][4], int matrix_b[4][4])
{
	
	int temp1[4] = { 0,1,2,3 };
	for (int s = 0; s < 24; s++)
	{
		int count = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (matrix_a[i][j] == matrix_b[temp1[i]][j])
				{
					count++;
				}
			}

		}

		if (count == 16)
		{
			return 1;
		}
		next_permutation(temp1, temp1 + 4);





	}





	return 0;
}
int equal_two_matrix(int matrix_a[4][4], int matrix_b[4][4])
{
	int temp1[4] = { 0,1,2,3 };
	int count = 0;
	//cout << endl;
	for (int i = 0; i < 24; i++)
	{
		
		int temp_matrix[4][4] = { 0 };
		

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				temp_matrix[j][k] = matrix_b[j][temp1[k]];
				//cout << temp_matrix[j][k] << " ,";
				
			}
		}

		//cout << temp1[0] << " " << temp1[1] << " " << temp1[2] << " " << temp1[3] << endl;
	
		next_permutation(temp1, temp1 + 4);
		count=count+equal_two_row_matrix(matrix_a, temp_matrix);
		

	}



	if (count == 0)
	{
		return 0;
	}



	return 1;
}









void equal_element(int  Matrix_A[M][4][4][N], int count)
{
	int temp_array[M] = { 0 };
	int a = 1;
	for (int i = 0; i < count; i++)
	{
		if (temp_array[i] == 0)
		{
			temp_array[i] = a;
			for (int j = i + 1; j < count; j++)
			{

				if (equal_two_matrix_element(Matrix_A[i], Matrix_A[j]) == 1)
				{
					temp_array[j] = a;
				}

			}
			a++;
		}
	}
	/*for (int i = 0; i < count; i++)
	{
		cout << temp_array[i] << ",";
	}
	cout << a << endl;*/

	//for (int k = 1; k < a; k++)
	//{
	//	for (int s = 0; s < count; s++)
	//	{
	//		if (temp_array[s] == k)
	//		{
	//			for (int i = 0; i < 4; i++)
	//			{
	//				for (int j = 0; j < 4; j++)
	//				{
	//					cout << Matrix_A[s][i][j] << ", ";
	//				}

	//			}
	//			cout << endl;
	//			break;
	//		}
	//	}
	//}



}

int equal_two_matrix_element(int matrix_a[4][4][N], int matrix_b[4][4][N])
{
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int temp[N] = { 0 };
			addoper(matrix_a[i][j], matrix_b[i][j], temp);
				if (temp[0] == 0)
				{
					count++;
				}
		}

	}
	if (count == 16)
	{
		return 1;
	}
	else { return 0; }
}