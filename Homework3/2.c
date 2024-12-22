/*对一个char型的二维数组A进行排序*/
#include <stdio.h>
#include <string.h>

// 交换两个字符
void swap_char(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// 计算一行字符的ASCII码之和
int sum_ascii_row(char row[], int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += row[i];
    }
    return sum;
}

// 对二维数组的每一行进行排序（按照列元素从小到大排序）
void sort_rows(char arr[][2], int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols - 1; j++) {
            for (int k = 0; k < num_cols - j - 1; k++) {
                if (arr[i][k] > arr[i][k + 1]) {
                    swap_char(&arr[i][k], &arr[i][k + 1]);
                }
            }
        }
    }
}

// 按照行的ASCII码和来对二维数组进行排序（整体排序）
void sort_rows_by_sum(char arr[][2], int num_rows, int num_cols) {
    for (int i = 0; i < num_rows - 1; i++) {
        for (int j = 0; j < num_rows - i - 1; j++) {
            int sum1 = sum_ascii_row(arr[j], num_cols);
            int sum2 = sum_ascii_row(arr[j + 1], num_cols);
            if (sum1 > sum2) {
                for (int k = 0; k < num_cols; k++) {
                    swap_char(&arr[j][k], &arr[j + 1][k]);
                }
            }
        }
    }
}

int main() {
    char A[][2] = {
        {'D', 'C'},
        {'B', 'A'}
    };
    int num_rows = sizeof(A) / sizeof(A[0]);
    int num_cols = sizeof(A[0]) / sizeof(A[0][0]);

    // 先对每一行内部排序
    sort_rows(A, num_rows, num_cols);
    // 再按照行的ASCII码和进行整体排序
    sort_rows_by_sum(A, num_rows, num_cols);

    // 输出排序后的数组
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%c ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}
