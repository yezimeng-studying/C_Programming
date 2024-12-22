/*程序从用户接收多行英文字符串。当用户结束输入后，程序统计出在用户的输>入中所出现过的单词，以及这些单词在每一行出现的次数、在用户输入中总共出>现的次数*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_WORD_LENGTH 100

// 声明一个结构体来存储单词的计数信息
typedef struct {
    char word[MAX_WORD_LENGTH];
    int line_count[MAX_LINES];
    int total_count;
} WordCount;

// 函数声明
void tokenize(const char *line, char **tokens, int max_tokens);
int find_word(WordCount *word_counts, int size, const char *word);
void count_words(WordCount *word_counts, int *word_count_size, const char *line, int current_line);

int main() {
    char **lines = malloc(MAX_LINES * sizeof(char *));
    WordCount *word_counts = malloc(MAX_LINES * sizeof(WordCount));
    int line_count = 0;
    int word_count_size = 0;
    char line[1024];
    // 初始化指针数组
    for (int i = 0; i < MAX_LINES; ++i) {
        lines[i] = NULL;
    }

    printf("Enter lines of text (type 'END' to finish):\n");

    // 读取用户输入
    while (fgets(line, sizeof(line), stdin) && line_count < MAX_LINES) {
        // 去除换行符
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "END") == 0) {
            break;
        }

        // 为新行分配内存
        lines[line_count] = strdup(line);
        line_count++;

        // 统计当前行的单词
        count_words(word_counts, &word_count_size, line, line_count);
    }
 // 打印每个单词的计数
    printf("\nWord counts:\n");
    for (int i = 0; i < word_count_size; ++i) {
        printf("%s: ", word_counts[i].word);
        for (int j = 0; j < line_count; ++j) {
            printf("%d ", word_counts[i].line_count[j]);
        }
        printf("Total: %d\n", word_counts[i].total_count);
    }

    // 释放内存
    for (int i = 0; i < line_count; ++i) {
        free(lines[i]);
    }
    free(lines);
    free(word_counts);

    return 0;
}

// 将一行文本分割成单词
void tokenize(const char *line, char **tokens, int max_tokens) {
    int token_count = 0;
    char *token = strtok((char *)line, " ");

    while (token!= NULL && token_count < max_tokens - 1) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    tokens[token_count] = NULL;
}

// 查找单词是否已经存在于word_counts数组中
int find_word(WordCount *word_counts, int size, const char *word) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(word_counts[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}
// 统计一行中的单词，添加当前行参数
void count_words(WordCount *word_counts, int *word_count_size, const char *line, int current_line) {
    char *tokens[MAX_WORD_LENGTH];
    tokenize(line, tokens, MAX_WORD_LENGTH);

    for (int i = 0; tokens[i]!= NULL; ++i) {
        char word[MAX_WORD_LENGTH];
        // 将token转换为小写
        for (int j = 0; tokens[i][j]!= '\0'; ++j) {
            word[j] = tolower(tokens[i][j]);
        }
        word[strcspn(word, "\r\n")] = 0; // 去除换行符

        int index = find_word(word_counts, *word_count_size, word);
        if (index == -1) {
            // 单词不存在，添加新单词
            strcpy(word_counts[*word_count_size].word, word);
            word_counts[*word_count_size].total_count = 1;
            for (int k = 0; k < MAX_LINES; ++k) {
                word_counts[*word_count_size].line_count[k] = 0;
            }
            word_counts[*word_count_size].line_count[current_line - 1] = 1;
            (*word_count_size)++;
        } else {
            // 单词已存在，更新计数
            word_counts[index].total_count++;
            word_counts[index].line_count[current_line - 1]++;
        }
	    }
}
