/*实现非递归版本的链表空间释放函数erase_list(list_item *head)*/
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct list_item {
    int data;  // 这里简单使用int类型数据作为示例，可根据实际替换
    struct list_item *next;
} list_item;

// 非递归版本的链表空间释放函数
void erase_list(list_item *head) {
    list_item *current = head;
    list_item *next;
    while (current!= NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// 用于创建链表节点的函数（辅助函数）
list_item *create_node(int value) {
    list_item *new_node = (list_item *)malloc(sizeof(list_item));
    if (new_node == NULL) {
        perror("内存分配失败");
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// 用于构建简单链表的函数（辅助函数）
list_item *build_list(int num_elements) {
    list_item *head = NULL;
    list_item *tail = NULL;
    for (int i = 0; i < num_elements; i++) {
        list_item *new_node = create_node(i);
        if (new_node == NULL){
		       	// 如果创建节点失败，释放已构建部分链表的空间
                if (head!= NULL) {
                    erase_list(head);
                }
                return NULL;
            }
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
    }
    return head;
}

int main() {
    // 构建一个包含5个节点的链表
    list_item *my_list = build_list(5);
    if (my_list == NULL) {
        printf("链表构建失败\n");
        return -1;
    }

    // 调用链表空间释放函数
    erase_list(my_list);
    printf("链表空间已成功释放\n");

    return 0;
}
