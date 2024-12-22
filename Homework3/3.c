/*一个8 x 8的国际象棋棋盘上放置8个皇后，使这些皇后之间不会相互攻击的所有的摆放方案*/
#include <stdio.h>
#include <stdlib.h>

#define N 8

// 检查在当前位置(row, col)放置皇后是否安全
int isSafe(int board[N][N], int row, int col) {
    int i, j;

    // 检查同一列是否有皇后冲突
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return 0;
    }

    // 检查左上方是否有皇后冲突
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return 0;
    }

    // 检查右上方是否有皇后冲突
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1)
            return 0;
    }

    return 1;
}

// 递归函数用于放置皇后并寻找所有解
void solveNQueensUtil(int board[N][N], int row) {
    // 如果所有行都放置了皇后，找到一种解决方案，输出棋盘布局
    if (row == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    // 尝试在当前行的每一列放置皇后
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            solveNQueensUtil(board, row + 1);
            board[row][col] = 0;  // 回溯，撤销当前位置的皇后放置
        }
    }
}

// 主函数，调用解决八皇后问题的函数
int main() {
    int board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
    solveNQueensUtil(board, 0);
    return 0;
}

