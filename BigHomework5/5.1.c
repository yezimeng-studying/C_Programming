/*代码雨*/
#include<time.h>
#include<unistd.h>
#include <ncurses.h> 	
#include <sys/time.h>	
#include <stdio.h>
#include <stdlib.h>		
#include <sys/queue.h>	

#define COL_NUM 7	//队列数量
#define COL_LEN 4	//队列长度
#define COL_WIDE 10	//队列间距
//某个点的结构体定义
struct Node
{
	char ch;	//字符
	int x;		//x值
	int y;		//y值
	SIMPLEQ_ENTRY(Node) entry;
};

int main(void)
{
	int i = 0;
	int j = 0;
	int count = 0;
	struct Node *temp;
	
	initscr();								//初始化屏幕
	noecho();
	curs_set(0);							//不显示光标
	start_color();							//启用颜色支持
	init_pair(1, COLOR_GREEN, COLOR_BLACK);	//使用绿色作为前景色，黑色作为背景色
	bkgdset(COLOR_PAIR(1));					//设置颜色对
	clear();								//清屏，去除原来的字符
	
	//在特定位置显示想要的字符
	//位置用坐标来表示，坐标的原点在窗口左上角，x轴指向右边，y轴指向下面
	int xmax = getmaxx(stdscr);				//标准屏幕的x的最大值
	int ymax = getmaxy(stdscr);				//标准屏幕的y的最大值
	
	srand(time(NULL));						//随机数种子
	
	SIMPLEQ_HEAD(, Node) col[COL_NUM]; 		//创建MAX_NUM个队列
	
	for(i = 0; i<COL_NUM; i++)
	{
		SIMPLEQ_INIT(&col[i]);
	}

	//对所有的队列的每个成员进行初始化
	for(j = 0;j<COL_NUM;j++)
	{
		for(i = 0;i<COL_LEN;i++)
		{
			temp = malloc(sizeof(struct Node));			//申请内存空间
			temp->ch = rand()%10 + 'a';
			temp->x = 10 + j*COL_WIDE;
			temp->y = i;
			SIMPLEQ_INSERT_TAIL(&col[j], temp, entry);	//将节点加入队列
		}
	}
	while(1)
	{
		clear(); 			//清屏

		struct Node *var; 	//临时变量用来遍历队列的每一个节点
		
		for(j = 0; j<COL_NUM; j++)
		{
			SIMPLEQ_FOREACH(var, &col[j], entry)
			{			
				//若该队列头部成员到了底部，删除该成员，并在队列尾部增加新成员
				if(var->y >= ymax - 2)					
				{
					SIMPLEQ_REMOVE_HEAD(&col[j], entry); //清除头部成员，每次去除一个

					free(temp);
					for(i = 0;i<COL_LEN;i++)
					{
						temp = malloc(sizeof(struct Node));	//申请内存空间
						temp->ch = rand()%10 + 'a';
						temp->x = 10  + j*COL_WIDE;
						temp->y = i;
						
						//将新成员加入该队列尾
						SIMPLEQ_INSERT_TAIL(&col[j], temp, entry);
					}

				}
						
				//显示		
				move(var->y, var->x);
				addch(var->ch);
				
				var->y++;
			}
	
		}
		refresh();	
		//延时
		usleep(120000);
	}
	getch();			//等待按键，确保不会马上退出
	endwin();			//退出
	free(temp);
	return 0;
}

