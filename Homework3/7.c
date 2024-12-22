/*void matrix_multi(double A[3][4], double B[4][5], double C[3][5]);编>写该函数的函数体并测试其正确性。*/
#include<stdio.h>
int main() {
   void matrix_multi(double A[3][4],double B[4][5],double C[3][5]){
                   for (int i=0;i<3;i++){
                   for (int j=0;j<5;j++){
                   C[i][j]=0;
                   for (int k=0;k<4;k++){
                        C[i][j]+=A[i][k]*B[k][j];
                        }
                        }
         }
        }
        double A[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    double B[4][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    double C[3][5];

    matrix_multi(A, B, C);

      // 输出结果矩阵C
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%.0f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

