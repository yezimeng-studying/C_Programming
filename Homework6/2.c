/*请编程实现简易字符动画设计制作套件（多物体、彩色、动画导出、动画回放等）*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>  // ncurses库头文件，用于终端界面控制
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FRAMES 100  // 最大动画帧数
#define MAX_OBJECTS 10  // 最大物体数量
#define DELAY_TIME 100000  // 每帧之间的延迟时间（微秒）

// 物体结构体，用于表示每个动画中的物体
typedef struct Object {
    int x;
    int y;
    char shape;
    int color_pair;
} Object;

// 动画帧结构体，包含所有物体在该帧的状态
typedef struct Frame {
    Object objects[MAX_OBJECTS];
    int object_count;
} Frame;

// 动画结构体，包含多个动画帧
typedef struct Animation {
    Frame frames[MAX_FRAMES];
    int frame_count;
} Animation;

// 初始化ncurses库及颜色
void init_ncurses() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    cbreak();
    noecho();
    curs_set(0);
}

// 关闭ncurses库
void end_ncurses() {
    endwin();
}

// 创建一个新的动画对象
Animation create_animation() {
    Animation anim;
    anim.frame_count = 0;
    for (int i = 0; i < MAX_FRAMES; i++) {
        anim.frames[i].object_count = 0;  // 初始化每个帧的物体数量为0
    }
    return anim;
}

// 向动画中添加一个帧
void add_frame(Animation *anim, Frame frame) {
    if (anim->frame_count < MAX_FRAMES) {
        anim->frames[anim->frame_count++] = frame;
    }
}

// 在终端绘制一帧画面
void draw_frame(Frame frame) {
    clear();
    for (int i = 0; i < frame.object_count; i++) {
        Object obj = frame.objects[i];
        attron(COLOR_PAIR(obj.color_pair));
        mvaddch(obj.y, obj.x, obj.shape);
        attroff(COLOR_PAIR(obj.color_pair));
    }
    refresh();
}

// 播放动画
void play_animation(Animation anim) {
    for (int i = 0; i < anim.frame_count; i++) {
        draw_frame(anim.frames[i]);
        usleep(DELAY_TIME);
    }
}

// 将每一帧画面保存为文本文件（模拟动画帧导出，可后续用ImageMagick合成动画）
void export_frames(Animation anim, const char *output_folder) {
    char filename[200];
    size_t len = strlen(output_folder);
    if (output_folder[len - 1]!= '/') {
        // 如果路径最后不是 / ，添加 /
        char folder[100];
        strcpy(folder, output_folder);
        strcat(folder, "/");
        for (int i = 0; i < anim.frame_count; i++) {
            sprintf(filename, "%sframe_%03d.txt", folder, i);
            FILE *fp = fopen(filename, "w");
            if (fp!= NULL) {
                Frame frame = anim.frames[i];
                for (int j = 0; j < frame.object_count; j++) {
                    Object obj = frame.objects[j];
                    fprintf(fp, "%d %d %c %d\n", obj.x, obj.y, obj.shape, obj.color_pair);
                }
                fclose(fp);
            }
        }
    } else {
        for (int i = 0; i < anim.frame_count; i++) {
            sprintf(filename, "%sframe_%03d.txt", output_folder, i);
            FILE *fp = fopen(filename, "w");
            if (fp!= NULL) {
                Frame frame = anim.frames[i];
                for (int j = 0; j < frame.object_count; j++) {
                    Object obj = frame.objects[j];
                    fprintf(fp, "%d %d %c %d\n", obj.x, obj.y, obj.shape, obj.color_pair);
                }
                fclose(fp);
            }
        }
    }
}

// 创建文件夹函数，如果文件夹不存在则创建
void create_folder(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
    // 初始化ncurses
    init_ncurses();

    Animation anim = create_animation();

    // 创建几个示例帧和物体，模拟简单动画
    Frame frame1;
    frame1.object_count = 2;
    frame1.objects[0].x = 10;
    frame1.objects[0].y = 5;
    frame1.objects[0].shape = 'O';
    frame1.objects[0].color_pair = 1;
    frame1.objects[1].x = 20;
    frame1.objects[1].y = 8;
    frame1.objects[1].shape = '*';
    frame1.objects[1].color_pair = 2;
    add_frame(&anim, frame1);

    Frame frame2;
    frame2.object_count = 3;
    frame2.objects[0].x = 12;
    frame2.objects[0].y = 6;
    frame2.objects[0].shape = 'O';
    frame2.objects[0].color_pair = 1;
    frame2.objects[1].x = 22;
    frame2.objects[1].y = 9;
    frame2.objects[1].shape = '*';
    frame2.objects[1].color_pair = 2;
    frame2.objects[2].x = 5;
    frame2.objects[2].y = 3;
    frame2.objects[2].shape = '+';
    frame2.objects[2].color_pair = 3;
    add_frame(&anim, frame2);

    // 播放动画
    play_animation(anim);

    // 导出动画帧（保存为文本文件）
    char output_folder[] = "output_frames";
    create_folder(output_folder);
    export_frames(anim, output_folder);

    // 关闭ncurses
    end_ncurses();

    // 使用ImageMagick命令行工具将文本帧合成为动画（需先安装ImageMagick）
    // 改进的图片帧生成逻辑，添加错误处理等
    char command[200];
    sprintf(command, "cd %s && for file in frame_*.txt; do if [ -f \"$file\" ]; then convert -size 80x24 xc:black -pointsize 12 -fill white -draw \"text 0,0 '@$file'\" $file.png; fi; done", output_folder);
    if (system(command) == -1) {
        perror("Error generating image frames");
        return 1;
    }

    // 合成GIF动画逻辑，添加错误处理
    sprintf(command, "cd %s && convert -delay 100 -loop 0 frame_*.png animation.gif", output_folder);
    if (system(command) == -1) {
        perror("Error creating animation GIF");
        return 1;
    }

    return 0;
}

