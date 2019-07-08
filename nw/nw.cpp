#include <iostream>
#define MAX(A,B) ( ((A)>(B))?(A):(B) )
#define MIN(A,B) ( ((A)<(B))?(A):(B) )
#define ALEN 10
#define BLEN 14
#define GAP_SCORE -1
#define NPE 4

int main(void) {
	int ik = 1;
	int aM[(ALEN + 1)][(BLEN + 1)] = {0};
	int iMaxLength = MAX(ALEN, BLEN);
	int iMinLength = MIN(ALEN, BLEN);

	init_row: for (int a_idx = 0; a_idx < (ALEN + 1); a_idx++) 
	{
		aM[a_idx][0] = a_idx * GAP_SCORE;
	}

	init_col: for (int b_idx = 0; b_idx < (BLEN + 1); b_idx++) 
	{
	    aM[0][b_idx] = b_idx * GAP_SCORE;
	}

	for (int ik = 2; ik < ALEN + BLEN +2 ; ik++) 
	{
		int ii;
		if (ik < MAX(ALEN, BLEN) + 1)	ii = 1;
		else ii = ik - iMaxLength;

		for (; ii < MIN(ik,iMinLength+1); ii = ii + NPE) 
		{
			aM[ii][ ik - ii] = ik;
			if ((ik - ii - 1 > 0) && (ii + 1 < iMinLength + 1))	aM[ii + 1][ ik - ii - 1] = ik;
			if ((ik - ii - 2 > 0) && (ii + 2 < iMinLength + 1))	aM[ii + 2][ ik - ii - 2] = ik;
			if ((ik - ii - 3 > 0) && (ii + 3 < iMinLength + 1))	aM[ii + 3][ ik - ii - 3] = ik;
		}
	}

	for (int i = 0; i < ALEN+1; i++)
	{
		for (int j = 0; j < BLEN+1; j++)
		{
			printf("%d\t", aM[i][j]);
		}
		printf("\n");
	}
	getchar();
}