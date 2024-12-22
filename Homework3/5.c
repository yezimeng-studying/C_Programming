/*C语言使用的存放方式是行排列*/
#include<stdio.h>
void testLocalArray(){
        int arr[5]={1,2,3,4,5};
        printf("局部数组arr的首地址：%p\n",&arr);
}
int main(){
        testLocalArray();
        return 0;
}
~                                       
