#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FLIGHTS 100
#define FILENAME "flights.dat"

// 航班信息结构体
typedef struct {
    char flight_id[10];  // 航班号
    char departure[20];  // 出发地
    char destination[20]; // 目的地
    char takeoff_time[6]; // 起飞时间(HH:MM)
    char arrival_time[6]; // 到达时间
    int seats;           // 座位数
} Flight;

Flight flights[MAX_FLIGHTS];
int num_flights = 0;

// 函数声明
void load_data();
void save_data();
void add_flight();
void display_all();
void search_flight();
void delete_flight();
void modify_flight();
void show_menu();

int main() {
    load_data();
    while(1) {
        show_menu();
        int choice;
        scanf("%d", &choice);
        getchar(); // 清除输入缓冲区
        
        switch(choice) {
            case 1: add_flight(); break;
            case 2: display_all(); break;
            case 3: search_flight(); break;
            case 4: delete_flight(); break;
            case 5: modify_flight(); break;
            case 6: save_data(); exit(0);
            default: printf("无效选项!\n");
        }
    }
    return 0;
}

void load_data() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(&num_flights, sizeof(int), 1, file);
        fread(flights, sizeof(Flight), num_flights, file);
        fclose(file);
    }
}

void save_data() {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(&num_flights, sizeof(int), 1, file);
        fwrite(flights, sizeof(Flight), num_flights, file);
        fclose(file);
    }
}

void add_flight() {
    if (num_flights >= MAX_FLIGHTS) {
        printf("航班数量已达上限!\n");
        return;
    }
    
    Flight f;
    printf("输入航班号: ");
    scanf("%s", f.flight_id);
    getchar();
    
    // 检查航班号是否已存在
    for (int i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].flight_id, f.flight_id) == 0) {
            printf("该航班号已存在!\n");
            return;
        }
    }
    
    printf("出发地: ");
    scanf("%19s", f.departure);
    printf("目的地: ");
    scanf("%19s", f.destination);
    printf("起飞时间(HH:MM): ");
    scanf("%5s", f.takeoff_time);
    printf("到达时间(HH:MM): ");
    scanf("%5s", f.arrival_time);
    printf("座位数: ");
    scanf("%d", &f.seats);
    
    flights[num_flights++] = f;
    printf("添加成功!\n");
}

void display_all() {
    printf("\n%-10s %-15s %-15s %-10s %-10s %-5s\n", 
           "航班号", "出发地", "目的地", "起飞时间", "到达时间", "座位");
    for (int i = 0; i < num_flights; i++) {
        printf("%-10s %-15s %-15s %-10s %-10s %-5d\n",
               flights[i].flight_id,
               flights[i].departure,
               flights[i].destination,
               flights[i].takeoff_time,
               flights[i].arrival_time,
               flights[i].seats);
    }
}

void search_flight() {
    char id[10];
    printf("输入要查询的航班号: ");
    scanf("%s", id);
    
    for (int i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].flight_id, id) == 0) {
            printf("\n航班信息:\n");
            printf("航班号: %s\n", flights[i].flight_id);
            printf("出发地: %s\n", flights[i].departure);
            printf("目的地: %s\n", flights[i].destination);
            printf("起飞时间: %s\n", flights[i].takeoff_time);
            printf("到达时间: %s\n", flights[i].arrival_time);
            printf("座位数: %d\n", flights[i].seats);
            return;
        }
    }
    printf("未找到该航班!\n");
}

void delete_flight() {
    char id[10];
    printf("输入要删除的航班号: ");
    scanf("%s", id);
    
    for (int i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].flight_id, id) == 0) {
            for (int j = i; j < num_flights - 1; j++) {
                flights[j] = flights[j+1];
            }
            num_flights--;
            printf("删除成功!\n");
            return;
        }
    }
    printf("未找到该航班!\n");
}

void modify_flight() {
    char id[10];
    printf("输入要修改的航班号: ");
    scanf("%s", id);
    
    for (int i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].flight_id, id) == 0) {
            printf("输入新信息(留空则保持原值):\n");
            
            char input[20];
            printf("出发地(%s): ", flights[i].departure);
            scanf("%19s", input);
            if (strlen(input) > 0) strcpy(flights[i].departure, input);
            
            printf("目的地(%s): ", flights[i].destination);
            scanf("%19s", input);
            if (strlen(input) > 0) strcpy(flights[i].destination, input);
            
            printf("起飞时间(%s): ", flights[i].takeoff_time);
            scanf("%5s", input);
            if (strlen(input) > 0) strcpy(flights[i].takeoff_time, input);
            
            printf("到达时间(%s): ", flights[i].arrival_time);
            scanf("%5s", input);
            if (strlen(input) > 0) strcpy(flights[i].arrival_time, input);
            
            printf("座位数(%d): ", flights[i].seats);
            scanf("%s", input);
            if (strlen(input) > 0) flights[i].seats = atoi(input);
            
            printf("修改成功!\n");
            return;
        }
    }
    printf("未找到该航班!\n");
}

void show_menu() {
    printf("\n===== 航班管理系统 =====\n");
    printf("1. 添加航班\n");
    printf("2. 显示所有航班\n");
    printf("3. 查询航班\n");
    printf("4. 删除航班\n");
    printf("5. 修改航班\n");
    printf("6. 退出系统\n");
    printf("请输入选择: ");
}
