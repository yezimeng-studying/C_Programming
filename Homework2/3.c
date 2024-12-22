/*已知2024年10月29日为周二。请基于该信息：
设计一个万年历程序。接收的输入为任意一个年份，程序输出该年份的完整日历。*/
#include <stdio.h>
#include <stdlib.h>

// 判断是否为闰年，闰年返回1，平年返回0
int isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100!= 0) || (year % 400 == 0));
}

// 计算从2024年10月29日到给定年份1月1日的总天数
int calculateDaysToYearStart(int year) {
    int totalDays = 0;
    for (int y = 2024; y < year; y++) {
        totalDays += isLeapYear(y)? 366 : 365;
    }
    return totalDays;
}

// 计算给定年份给定月份的总天数
int daysInMonth(int year, int month) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month];
}

// 计算从2024年10月29日到给定年份给定月份1日的总天数
int calculateDaysToMonthStart(int year, int month) {
    int totalDays = calculateDaysToYearStart(year);
    for (int m = 1; m < month; m++) {
        totalDays += daysInMonth(year, m);
    }
    return totalDays;
}

// 输出日历的头部，即星期几的标识
void printCalendarHeader() {
    printf("日 一 二 三 四 五 六\n");
}

// 输出日历主体内容，根据起始星期和该月天数进行输出
void printCalendarBody(int startDay, int daysInMonth) {
    int currentDay = 1;
    // 先输出起始星期前的空格占位
    for (int i = 0; i < startDay; i++) {
        printf("   ");
    }
    // 输出该月每一天的数字
    while (currentDay <= daysInMonth) {
        printf("%2d ", currentDay);
        if ((currentDay + startDay) % 7 == 0 || currentDay == daysInMonth) {
            printf("\n");
        }
        currentDay++;
    }
}

// 检查输入的年份是否合法，如果不合法提示重新输入，合法则返回0
int checkInputValidity(int *year) {
    while (1) {
        if (scanf("%d", year)!= 1) {
            // 输入格式错误，清空输入缓冲区并提示重新输入
            while (getchar()!= '\n')
                ;
            printf("输入格式错误，请重新输入年份（需为整数）：");
            continue;
        }
        if (*year < 0) {
            printf("输入的年份不合法，请重新输入（年份需大于等于0）：");
            continue;
        }
        break;
    }
    return 0;
}

// 计算并返回给定月份的周数
int calculateWeeksInMonth(int startDay, int daysInMonth) {
    int totalDays = startDay + daysInMonth;
    return (totalDays + 6) / 7;  // 通过总天数（包含起始星期占位）除以7向上取整得到周数
}

int main() {
    int year;
    printf("请输入年份：");
    checkInputValidity(&year);

    for (int month = 1; month <= 12; month++) {
        // 输出对应的年份和月份标题
        printf("    %d年%d月\n", year, month);

        int totalDaysToMonthStart = calculateDaysToMonthStart(year, month);
        int startDay = (totalDaysToMonthStart % 7 + 2) % 7;  // 根据已知2024年10月29日是周二来计算该月1日是星期几
        int daysInThisMonth = daysInMonth(year, month);

        printCalendarHeader();
        printCalendarBody(startDay, daysInThisMonth);

        // 计算并输出该月的周数
        int weeksInMonth = calculateWeeksInMonth(startDay, daysInThisMonth);
        printf("该月共有 %d 周\n\n", weeksInMonth);
    }

    return 0;
}

    

