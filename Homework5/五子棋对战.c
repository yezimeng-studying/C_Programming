/*五子棋双人对战*/
#include <stdio.h>
#include <stdlib.h>
// 假设棋盘大小为15x15，可根据实际情况修改
#define BOARD_SIZE 15
// 打印棋盘
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
// 检查是否有玩家获胜
int checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // 检查水平方向
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j <= BOARD_SIZE - 5; j++) {
            int count = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i][j + k] == player) {
                    count++;
                }
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    // 检查垂直方向
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i <= BOARD_SIZE - 5; i++) {
            int count = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j] == player) {
                    count++;
                }
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    // 检查正斜对角线方向（从左上角到右下角）
    for (int i = 0; i <= BOARD_SIZE - 5; i++) {
        for (int j = 0; j <= BOARD_SIZE - 5; j++) {
            int count = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j + k] == player) {
                    count++;
                }
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    // 检查反斜对角线方向（从右上角到左下角）
    for (int i = 0; i <= BOARD_SIZE - 5; i++) {
        for (int j = 4; j < BOARD_SIZE; j++) {
            int count = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j - k] == player) {
                    count++;
                }
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    return 0;
}
// 检查落子是否合法
int isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return 0;
    }
    return (board[row][col] ==' ');
}
int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    // 初始化棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] =' ';
        }
    }
    char currentPlayer = 'X';
    int moveCount = 0;
    int row, col;
    int gameOver = 0;
    while (!gameOver) {
        printBoard(board);
        printf("玩家 %c 请输入行和列（从0开始），用空格隔开: ", currentPlayer);
        scanf("%d %d", &row, &col);
        if (!isValidMove(board, row, col)) {
            printf("无效的移动，请重新输入！\n");
            continue;
        }
        board[row][col] = currentPlayer;
        moveCount++;
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("玩家 %c 获胜！\n", currentPlayer);
            gameOver = 1;
        } else if (moveCount == BOARD_SIZE * BOARD_SIZE) {
            printBoard(board);
            printf("平局！\n");
            gameOver = 1;
        } else {
            currentPlayer = (currentPlayer == 'X')? 'O' : 'X';
        }
    }
    return 0;
}

