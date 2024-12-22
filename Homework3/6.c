/*补全函数实现对该二维数组任意元素A[m,n]的访问并验证其正确性*/
#include <stdio.h>

int main()
{       int two_dim_array_access(int *x, int i, int j, int m, int n, int C)
{
    // 首先计算从起始地址到目标行首地址的偏移量
    int offset_row = (m - i) * C;
    // 再加上目标列相对于目标行首地址的偏移量，得到目标元素相对于起始地
址的总偏移量
    int offset = offset_row + (n - j);
    // 通过起始地址加上偏移量，得到目标元素的地址，然后解引用返回该地址
存储的值
    return *(x + offset);
}

    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    // 测试two_dim_array_access函数，期望返回值为6
    int result1 = two_dim_array_access(&A[0][0], 0, 0, 1, 2, 3);
    printf("two_dim_array_access(&A[0][0],0,0,1,2,3)的返回值: %d\n", result1);

    int result2 = two_dim_array_access(&A[0][1], 0, 1, 1, 2, 3);
    printf("two_dim_array_access(&A[0][1],0,1,1,2,3)的返回值: %d\n", result2);

    return 0;
}


