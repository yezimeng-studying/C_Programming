/*go语言改写万年历*/
package main

import (
    "fmt"
    "time"
)

func main() {
    // 获取当前时间
    now := time.Now()

    // 设置默认月份为当前月份
    month := now.Month()
    year := now.Year()

    // 从命令行参数读取月份和年份（可选）
    if len(os.Args) > 1 {
        month, _ = time.Parse("2006-01", os.Args[1]).Date()
    }
    if len(os.Args) > 2 {
        year, _ = time.Parse("2006", os.Args[2]).Date()
    }

    // 输出标题
    fmt.Printf("Calendar for %s %d\n", month, year)

    // 获取本月第一天是星期几
    firstDayOfWeek := time.Date(year, month, 1, 0, 0, 0, 0, time.UTC).Weekday()

    // 计算该月的天数
    daysInMonth := time.Date(year, month+1, 0, 0, 0, 0, 0, time.UTC).Day()

    // 打印表头
    fmt.Println("Su Mo Tu We Th Fr Sa")

    // 打印前导空格
    for i := 0; i < int(firstDayOfWeek); i++ {
        fmt.Print("   ")
    }

    // 打印每一天
    for day := 1; day <= daysInMonth; day++ {
        fmt.Printf("%2d ", day)
        if (firstDayOfWeek+day)%7 == 0 {
            fmt.Println()
        }
    }

    // 如果最后一天不是周六，则需要打印额外的换行符
    if (firstDayOfWeek+daysInMonth)%7 != 0 {
        fmt.Println()
    }
}
