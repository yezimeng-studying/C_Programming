#include <stdio.h>
#include "module.h"

int main() {
    // 调用函数1并打印返回值
    int result1 = function1();
    printf("function1的返回值为：%d\n", result1);

    // 调用函数2并打印返回值
    int result2 = function2();
    printf("function2的返回值为：%d\n", result2);

    // 打印全局变量的值
    printf("全局变量global_variable的值为：%d\n", global_variable);

    return 0;
}

~                                                                      
~                                             
