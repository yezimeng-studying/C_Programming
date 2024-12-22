/* 井字棋双人对战*/
#include <stdio.h>
#include <stdlib.h>

// 定义棋盘大小
#define BOARD_SIZE 3

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
    // 检查行
    for (int i = 0; i < BOARD_SIZE; i++) {
        int rowWin = 1;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]!= player) {
                rowWin = 0;
                break;
            }
        }
        if (rowWin) return 1;
    }
    // 检查列
    for (int j = 0; j < BOARD_SIZE; j++) {
        int colWin = 1;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j]!= player) {
                colWin = 0;
                break;
            }
        }
        if (colWin) return 1;
    }
    // 检查对角线
    int diag1Win = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i]!= player) {
            diag1Win = 0;
            break;
        }
    }
    if (diag1Win) return 1;
    int diag2Win = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][BOARD_SIZE - 1 - i]!= player) {
            diag2Win = 0;
            break;
        }
    }
    if (diag2Win) return 1;
    return 0;
}

// 检查棋盘是否已满
int checkFull(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    // 初始化棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
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
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col]!= ' ') {
            printf("无效的移动，请重新输入！\n");
            continue;
        }
        board[row][col] = currentPlayer;
        moveCount++;
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("玩家 %c 获胜！\n", currentPlayer);
            gameOver = 1;
        } else if (checkFull(board)) {
            printBoard(board);
            printf("平局！\n");
            gameOver = 1;
        } else {
            currentPlayer = (currentPlayer == 'X')? 'O' : 'X';
        }
    }
    return 0;
}

