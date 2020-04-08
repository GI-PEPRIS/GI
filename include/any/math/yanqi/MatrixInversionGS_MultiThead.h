#include<math.h>

bool MatrixInversionGS_MultiThead(double **rhs, double **R, int stRank);
void MatrixProduct_MultiThead_(double **rhs, double **m, int nRow, int nR, int nCol, double **R, int iC);
void MatrixProduct_MultiThead(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
