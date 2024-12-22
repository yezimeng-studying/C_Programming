/*LED动画效果*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 假设这4个引脚连接着LED，根据实际硬件调整引脚编号
#define LED_PIN_1 0
#define LED_PIN_2 1
#define LED_PIN_3 2
#define LED_PIN_4 3

// 定义引脚高低电平
#define HIGH 1
#define LOW  0

// 模拟单片机的引脚寄存器（简单示意，实际是硬件相关的内存映射等）
unsigned char pin_status[4];

// 函数声明
void setup();
void delay_ms(int milliseconds);
void ledAnimation(int flow_speed, int blink_times, int random_blink_speed, int random_blink_count);
void flowLightEffect(int speed);
void allLedsBlinkEffect(int times, int on_time, int off_time);
void randomLedBlinkEffect(int led_count, int speed, int count);
void updatePinStatus(int pin, int level);

int main() {
    setup();
    // 设置动画效果参数，可根据实际需求调整
    int flow_speed = 500;  // 流水灯每个LED点亮时间，单位：毫秒
    int blink_times = 3;   // 全部LED闪烁的次数
    int random_blink_speed = 200;  // 随机LED闪烁时亮灭的时间间隔，单位：毫秒
    int random_blink_count = 5;    // 随机LED闪烁的总次数
    ledAnimation(flow_speed, blink_times, random_blink_speed, random_blink_count);
    return 0;
}

// 初始化引脚状态，相当于设置引脚为输出模式（简单模拟）
void setup() {
    for (int i = 0; i < 4; i++) {
        pin_status[i] = LOW;
    }
}

// 简单的延时函数，模拟实现一定毫秒数的延时
void delay_ms(int milliseconds) {
    clock_t start_time = clock();
    while (clock() - start_time < milliseconds * CLOCKS_PER_SEC / 1000) {
        // 空循环等待，达到延时效果
    }
}

// LED动画函数，整合多种动画效果，通过参数控制
void ledAnimation(int flow_speed, int blink_times, int random_blink_speed, int random_blink_count) {
    while (1) {
        // 流水灯效果
        flowLightEffect(flow_speed);

        // 全部LED闪烁效果
        allLedsBlinkEffect(blink_times, 300, 300);

        // 随机LED闪烁效果
        randomLedBlinkEffect(4, random_blink_speed, random_blink_count);
    }
}

// 流水灯效果函数，实现依次点亮每个LED的流水灯效果
void flowLightEffect(int speed) {
    int i;
    for (i = 0; i < 4; i++) {
        updatePinStatus(i, HIGH);  // 点亮当前LED
        delay_ms(speed);
        updatePinStatus(i, LOW);   // 熄灭当前LED
        delay_ms(100);
    }
}

// 全部LED闪烁效果函数，实现所有LED一起闪烁指定次数
void allLedsBlinkEffect(int times, int on_time, int off_time) {
    int j;
    for (j = 0; j < times; j++) {
        // 点亮所有LED
        for (int i = 0; i < 4; i++) {
            updatePinStatus(i, HIGH);
        }
        delay_ms(on_time);

        // 熄灭所有LED
        for (int i = 0; i < 4; i++) {
            updatePinStatus(i, LOW);
        }
        delay_ms(off_time);
    }
}

// 随机LED闪烁效果函数，随机选择LED进行闪烁指定次数
void randomLedBlinkEffect(int led_count, int speed, int count) {
    int k;
    unsigned int seed;  // 新增变量用于保存随机数种子
    for (k = 0; k < count; k++) {
        seed = (unsigned int)time(NULL);  // 将当前时间赋值给种子变量
        int random_led = rand_r(&seed) % led_count;  // 使用种子变量的地址作为rand_r函数的参数
        updatePinStatus(random_led, HIGH);
        delay_ms(speed);
        updatePinStatus(random_led, LOW);
        delay_ms(speed);
    }
}

// 更新指定引脚的电平状态函数，模拟对引脚电平的操作
void updatePinStatus(int pin, int level) {
    if (pin >= 0 && pin < 4) {
        pin_status[pin] = level;
        // 这里可以添加实际硬件操作相关的代码，比如向对应寄存器写入电平值等（此处省略）
        printf("LED_PIN_%d is set to %s\n", pin + 1, level == HIGH? "HIGH" : "LOW");
    } else {
        printf("Invalid pin number!\n");
    }
}

