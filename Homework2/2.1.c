/*已知2024年10月29日为周二。请基于该信息：
设计一个C语言程序，接收的输入为任意一个日子的年、月、日信息，程序输出该日子为星期几。*/
#include <stdio.h>
#include <stdlib.h>

// 判断是否为闰年，闰年返回1，平年返回0
int isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100!= 0) || year % 400 == 0);
}

// 计算从2024年10月29日到给定日期的总天数
int calculateDays(int year, int month, int day) {
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    int totalDays = 0;
    // 先计算年份差值带来的天数变化
    for (int y = 2024; y < year; y++) {
        totalDays += isLeapYear(y)? 366 : 365;
    }
    // 再计算月份差值带来的天数变化
    for (int m = 10; m < month; m++) {
        totalDays += daysInMonth[m];
    }
    // 加上当月日期的天数
    totalDays += day - 29;
    return totalDays;
}

int main() {
    int year, month, day;
    printf("请输入年 月 日（格式：yyyy mm dd）：");
    scanf("%d %d %d", &year, &month, &day);

    // 检查输入的年份是否合法（简单判断大于0即可，可根据实际需求细化）
    if (year <= 0) {
        printf("输入的年份不合法，请输入大于0的年份！\n");
        return 1;
    }

    // 检查输入的月份是否合法（范围是1 - 12）
    if (month < 1 || month > 12) {
        printf("输入的月份不合法，请输入1 - 12之间的数字作为月份！\n");
        return 1;
    }

    // 检查输入的日期是否合法，根据对应月份的天数范围判断
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    if (day < 1 || day > daysInMonth[month]) {
        printf("输入的日期不合法，请输入符合对应月份范围的日期！\n");
        return 1;
    }

    int totalDays = calculateDays(year, month, day);
    int weekDay = (totalDays % 7 + 2) % 7;  // 2024年10月29日是周二，对应数字2，计算出对应的星期数字
    // 输出对应的星期几，0对应周日，1对应周一，依次类推
    switch (weekDay) {
    case 0:
        printf("周日\n");
        break;
    case 1:
        printf("周一\n");
        break;
    case 2:
        printf("周二\n");
        break;
    case 3:
        printf("周三\n");
        break;
    case 4:
        printf("周四\n");
        break;
    case 5:
        printf("周五\n");
        break;
    case 6:
        printf("周六\n");
        break;
    }

    return 0;
}

