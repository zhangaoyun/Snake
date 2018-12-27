#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define WIDTH 80 // 游戏区域地图的宽度 
#define HEIGHT 40 // 游戏区域地图的高度 
#define INITSNAKELEN 3
#define TIME 120 //竞速时间的秒数
#define LEN sizeof(struct Snake) //Snake结构体字节数 

#define K 0//这个频率0，就是不响，作为空拍 

//以下的所有表示音符的符号均来自fl studio 14 的fl keys的标注，或许和一般钢琴的标注不一样 。 
//只有三个八度的音高频率 ，因为一般人声可以达到的频率大概都会落在这些里面 
#define C4 523
#define D4 588
#define E4 660
#define F4 700
#define G4 786
#define A4 884
#define B4 992

#define C5 1046
#define D5 1176
#define E5 1320
#define F5 1400
#define G5 1572
#define A5 1768
#define B5 1984

#define C6 2092
#define D6 2352
#define E6 2640
#define F6 2800
#define G6 3144
#define A6 3536
#define B6 3968
#define P 125   //折合bpm==120，原bpm为105，此处取了个近似值 

//蛇结构体 
struct Snake
{
	int x;
	int y;
	struct Snake * pervious;
	struct Snake * next;
};

struct Snake * head = NULL;
struct Snake * tail = NULL;
struct Snake * part, *temp = NULL;
struct Snake * p = NULL;

//玩家2的蛇的结构体 
struct Snake_2
{
	int x;
	int y;
	struct Snake_2 * pervious;
	struct Snake_2 * next;
};

struct Snake_2 * head_2 = NULL;
struct Snake_2 * tail_2 = NULL;
struct Snake_2 * part_2, *temp_2 = NULL;
struct Snake_2 * p_2 = NULL;

struct Food
{
	int x;
	int y;
};

struct Food food;

struct Grass
{
	int x;
	int y;
};

struct Grass grass;
struct Grass grass_1;
struct Grass grass_2;

struct Boom
{
	int x;
	int y;
};

struct Boom boom;

struct Wisdom
{
	int x;
	int y;
};

struct Wisdom wisdom;

//
char name[20];
char saved_data[3][30];
char name_2[20];
//文件相关全局变量 
char file_level[] = { "scores.dat" }; // 关卡模式存储文件名 
char n[3][20];
int s[3];
int l[3];
char file_t[] = { "scores_t.dat" };  // 竞速模式
char file_i[] = { "scores_i.dat" };
char file_l_record[] = { "level_record.dat" }; // 记录玩家玩过的关卡，没有解锁下一关就不能直接选下一关 

// 下面是在游戏过程中存的档 
char file_on_l[] = { "onlevel.dat" };
char file_on_i[] = { "oninfinite.dat" };
char file_on_t[] = { "ontime.dat" };

//初始化方向为右 
char current_dir = 'd';
char old_dir = 'd';
char current_dir_2 = 'i';
char old_dir_2 = 'i';

//初始化分数、吃到食物的数量、吃到毒草的数量、速度 
int score = 0;
int score_2 = 0;
int food_count = 0;
int food_count_2 = 0;
int grass_count = 0;
int grass_count_2 = 0;
int snake_length = 3;
int snake_length_2 = 3;
int boom_count = 0;
int boom_count_2 = 0;
int wisdom_count = 0;
int dis = 0;
int speed = 90;
char temp_ch;
int level = 1;
int c; // choose
int food_flag = 0;
int food_flag_2 = 0;
int grass_flag = 0;
int grass_flag_2 = 0;
char mode = 'l';
int start_time;
int start_time_i = 1;
int barrier_i;
char c_save;
int load_flag = 0;

void set_windows(); // 设置控制台窗口
void setting();
void music_play();
void init_view(); // 初始化游戏界面
void gotoxy(int x, int y);
void snake_born(); // 生成蛇
void start_game(char mode);
void move(char current_dir);
void print_snake();
void food_born();
void eat_food();
void grass_born();
void eat_grass();
void grass_reborn();
void grass_blink();
void boom_born();
void eat_boom();
void clear_screen();
void wisdom_born();
void eat_wisdom();
void death_judge();
void restart();
void next_level();
void init_data();
void about_time();
void v_control();
void save();
void choose_level();
void barrier_born(int level);
void eat_barrier(int level);
void items_not_barrier();
void if_level_3();
void load();
void save_on_game();
void snake_born_load();
void menu();

void about_play2();
//关于玩家2的一些函数
void snake_2_born();
void move_2(char current_dir_2);
void death_judge_double();
void relief();

int main()
{
	set_windows();
	music_play();
	setting();
	return 0;
}

void setting()
{
	//
	char mode_c;
	system("color 0B"); // 设置游戏前景为蓝色，背景为黑色 	
	gotoxy(50, 20);
	printf("请输入你的名字：");
	scanf("%s", name);
	system("cls");
	gotoxy(46, 19);
	printf("请\033[31m确认在英文输入法下\033[0m进行游戏");
	gotoxy(46, 20);
	printf("你好,%s,按空格键开始", name);
	char start;
	while (start = _getch() != ' ');
	menu();
}

void menu()
{
	char mode_c;
	system("cls");
	printf("    A-开始游戏\n    B-继续游戏\n    C-查看游戏说明\n    D-查看排行榜\n    Esc-退出游戏\n");
	c = getch();
	if (c == 'a')
	{
		printf("\n    请选择模式：\n    L-关卡模式\n    I-无限模式\n    T-竞速模式\n    D-双人模式\n");
		mode = getch();
		if (mode == 'l')
		{
			choose_level();
		}
		if (mode == 'i')
		{
			init_view();
			snake_born();
			start_game(mode);
		}
		if (mode == 't')
		{
			init_view();
			snake_born();
			start_game(mode);
		}
		if (mode == 'd')
		{
			printf("\n请输入玩家2的姓名");
			scanf("%s", name_2);
			wisdom.x = 200;
			wisdom.y = 200;
			init_view();
			snake_born();
			about_play2();
			start_game(mode);
		}
	}
	else if (c == 'b')
	{
		printf("\n    请选择要加载的模式：\n    L-关卡模式\n    I-无限模式\n    T-竞速模式\n");
		mode = _getch();
		load();
	}
	else if (c == 'c')
	{
		printf("游戏说明\n");
		printf("这里是说明\n");
		printf("WASD控制上下左右(双人模式玩家2JIKL控制上下左右)\n");
		printf("\033[32m★\033[0m是食物，吃了蛇加一节身体，分数加10\n");
		printf("\033[35m※\033[0m是毒草，吃了蛇减一节身体，分数减20\n");
		printf("\033[31m◎\033[0m是炸弹，吃了蛇减一半身体，分数减炸掉的身体数×15\n");
		printf("\033[33m◆\033[0m是智慧草，吃了蛇自动寻找下一个食物，吃到食物后停顿一秒\n");
		printf("吃的食物数量越多，蛇运动的速度越快\n");
		printf("关卡模式一共有三关，达到一定分数可进入下一关\n");
		printf("无限模式没有下一关，记录死亡时的分数\n");
		printf("竞速模式计算120秒时间得到的分数\n");
		printf("双人模式有两位玩家，哪方死亡哪方败北\n");
		char back_c;
		back_c = _getch();
		while (back_c != 13) // 回车键值为13 
		{
			back_c = _getch();
		}
		system("cls");
		menu();
	}
	else if (c == 'd')
	{
		system("cls");
		printf("要查看哪个模式的排行榜？");
		printf("\n    请选择模式：\n    L-关卡模式\n    I-无限模式\n    T-竞速模式\n");
		mode_c = getch();
		if (mode_c == 'l')
		{
			printf("关卡模式排行榜\n");
			printf("排名      姓名      分数      关卡\n");
			FILE * fp;
			if ((fp = fopen(file_level, "r")) == NULL)
			{
				printf("error");
				system("pause");
			}
			fscanf(fp, "%s%d%d%s%d%d%s%d%d", n[0], &s[0], &l[0], n[1], &s[1], &l[1], n[2], &s[2], &l[2]);
			int k;
			for (k = 0; k < 3; k++)
				printf("%-10d%-10s%-10d%-10d\n", k + 1, n[k], s[k], l[k]);
			fclose(fp);
		}
		else if (mode_c == 'i')
		{
			printf("无限模式排行榜\n");
			printf("排名      姓名      分数\n");
			FILE * fp;
			if ((fp = fopen(file_i, "r")) == NULL)
			{
				printf("error");
				system("pause");
			}
			fscanf(fp, "%s%d%s%d%s%d", n[0], &s[0], n[1], &s[1], n[2], &s[2]);
			int k;
			for (k = 0; k < 3; k++)
				printf("%-10d%-10s%-10d\n", k + 1, n[k], s[k]);
			fclose(fp);
		}
		else if (mode_c == 't')
		{
			printf("竞速模式排行榜\n");
			printf("排名      姓名      分数\n");
			FILE * fp;
			if ((fp = fopen(file_t, "r")) == NULL)
			{
				printf("error");
				system("pause");
			}
			fscanf(fp, "%s%d%s%d%s%d", n[0], &s[0], n[1], &s[1], n[2], &s[2]);
			int k;
			for (k = 0; k < 3; k++)
				printf("%-10d%-10s%-10d\n", k + 1, n[k], s[k]);
			fclose(fp);
		}
		char back_c;
		back_c = _getch();
		while (back_c != 13) // 回车键值为13 
		{
			back_c = _getch();
		}
		system("cls");
		menu();
	}
	else if (c == 27) //Esc键值为27 
	{
		exit(0);
	}
}
void about_play2()
{
	snake_2_born();
}

void snake_2_born()
{
	part_2 = temp_2 = (struct Snake_2 *)malloc(LEN);
	part_2->x = WIDTH / 4;
	part_2->y = HEIGHT / 2;
	part_2->pervious = NULL;
	int i;
	for (i = 0; i <= INITSNAKELEN; i++)
	{
		if (i == 0)
		{
			head_2 = part_2;
		}
		else
		{
			part_2->pervious = temp_2;
			temp_2->next = part_2;
		}
		temp_2 = part_2;
		part_2 = (struct Snake_2 *)malloc(LEN);
		part_2->x = temp_2->x;
		part_2->y = temp_2->y + 1;
	}
	temp_2->next = NULL;
	p_2 = head_2;
	int n = 1;
	do
	{
		if (n == 1)
		{
			gotoxy(p_2->x, p_2->y);
			printf("\033[40;37;5m●\033[0m\n");
			n++;
		}
		else
		{
			gotoxy(p_2->x, p_2->y);
			printf("\033[40;37;5m●\033[0m\n");
		}
		p_2 = p_2->next;
	} while (p_2->next != NULL);
}

void init_view() // 初始化游戏界面
{
	system("cls");
	system("color 0B"); // 设置游戏前景为蓝色，背景为黑色 
	int i;
	int j;
	//这一重循环先打印出所有方块
	for (i = 0; i < WIDTH;)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			gotoxy(i, j);
			printf("■");
		}
		i += 2;
		Sleep(30);
	}
	//这一重循环打印空格形成地图
	for (i = 2; i < WIDTH - 2;)
	{
		for (j = 1; j < HEIGHT - 1; j++)
		{
			gotoxy(i, j);
			printf("  "); // 注意这里要打两个空格
		}
		i += 2;
		Sleep(30);
	}
	if (mode != 'd')
	{
		gotoxy(94, 5);
		printf("玩家：%s", name);
	}
	else
	{
		gotoxy(94, 5);
		printf("玩家1：%s", name);
		gotoxy(94, 7);
		printf("玩家2：%s", name_2);
	}
	if (mode == 'l')
	{
		gotoxy(94, 3);
		printf("关卡模式");
		gotoxy(94, 4);
		printf("level:%d", level);
	}
	if (mode == 'i')
	{
		gotoxy(94, 3);
		printf("无限模式");
	}
	if (level == 2)
	{
		gotoxy(92, 17);
		printf("通关所需分数：250");
	}
	if (mode == 'd')
	{
		gotoxy(94, 3);
		printf("双人模式");
	}
	if (mode == 't')
	{
		gotoxy(94, 3);
		printf("竞速模式");
	}
}

void gotoxy(int x, int y)  // 光标函数？光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	//下面两句隐藏光标 
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void snake_born()
{
	part = temp = (struct Snake *)malloc(LEN);
	part->x = WIDTH / 2;
	part->y = HEIGHT / 2;
	part->pervious = NULL;
	int i;
	for (i = 0; i <= INITSNAKELEN; i++)
	{
		if (i == 0)
		{
			head = part;
		}
		else
		{
			part->pervious = temp;
			temp->next = part;
		}
		temp = part;
		part = (struct Snake *)malloc(LEN);
		part->x = temp->x - 2;
		part->y = temp->y;
	}
	temp->next = NULL;
	p = head;
	int n = 1;
	do
	{
		if (n == 1)
		{
			gotoxy(p->x, p->y);
			printf("\033[40;36;5m●\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("●");
		}
		p = p->next;
	} while (p->next != NULL);
}

void start_game(char mode)
{
	barrier_born(level);
	food_born();
	grass_born();
	boom_born();
	if (mode != 'd' || level != 3)
	{
		wisdom_born();
	}
	items_not_barrier();
	while (1)
	{
		mciSendString("play bgm.mp3", NULL, 0, NULL);
		if_level_3();
		char c_kbhit;
		if (_kbhit())
		{
			c_kbhit = _getch();
			if (c_kbhit == 'a' || c_kbhit == 'w' || c_kbhit == 's' || c_kbhit == 'd')
				current_dir = c_kbhit;
			else if (c_kbhit == 'j' || c_kbhit == 'i' || c_kbhit == 'l' || c_kbhit == 'k')
				current_dir_2 = c_kbhit;
			move(current_dir);
			if (mode == 'd')
				move_2(current_dir_2);
			food_flag = 0;
			food_flag_2 = 0;
			if (c_kbhit == 'f')
			{
				save_on_game();
			}
		}
		else
		{
			move(current_dir);
			if (mode == 'd')
				move_2(current_dir_2);
			food_flag = 0;
			food_flag_2 = 0;
		}
		barrier_born(level);
		eat_food();
		eat_grass();
		eat_boom();
		if (mode != 'd' || level != 3)
		{
			eat_wisdom();
		}
		if (mode != 'd')
			death_judge();
		else
			death_judge_double();
		gotoxy(100, 10);
		printf("                 ");
		gotoxy(100, 10);
		if (mode != 'd')
			printf("\033[44;37;5m分数：%d\033[0m ", score);
		if (mode == 'l')
		{
			next_level();
		}
		gotoxy(106, 12);
		printf("      ");
		gotoxy(96, 12);
		if (mode != 'd')
			printf("蛇的长度：%d", snake_length);
		gotoxy(90, 38);
		about_time(); // 关于时间的东西，比如毒草闪烁 ,竞速模式时间计算
	}
}

void print_snake()
{
	p = head;
	int n = 1;
	do
	{
		if (n == 1)
		{
			gotoxy(p->x, p->y);
			printf("\033[40;36;5m●\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("●");
		}
		p = p->next;
	} while (p->next != NULL);
	gotoxy(p->x, p->y);
	printf("  ");
	//下面是双人模式下打印第二条蛇 
	if (mode == 'd')
	{
		p_2 = head_2;
		n = 1;
		do
		{
			if (n == 1)
			{
				gotoxy(p_2->x, p_2->y);
				printf("\033[40;37;5m●\033[0m\n");
				n++;
			}
			else
			{
				gotoxy(p_2->x, p_2->y);
				printf("\033[40;37;5m●\033[0m\n");
			}
			p_2 = p_2->next;
		} while (p_2->next != NULL);
		gotoxy(p_2->x, p_2->y);
		printf("  ");
	}
	//速度控制
	v_control();
}

void food_born()
{
	if (!load_flag)
	{
		srand((unsigned)time(NULL));
		food.x = rand() % WIDTH + 2;
		if (food.x % 2 != 0)
			food.x++;
		if (food.x > 76)
			food.x -= 6;
		food.y = rand() % HEIGHT + 1;
		if (food.y > 38)
			food.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == food.x&&p->y == food.y)
				food.y--;
			p = p->next;
		}
	}
	gotoxy(food.x, food.y);
	printf("\033[32m★\033[0m");
}

void eat_food()
{
	if (food.x == head->x&&food.y == head->y)
	{
		mciSendString("play eat_food.mp3", NULL, 0, NULL);
		food_flag = 1;
		load_flag = 0;
		food_born();
		grass_reborn();
		score += 10;
		food_count++;
		snake_length++;
	}
	//下面两句把原来打印出的蛇的长度覆盖掉，否则会造成残留 
	gotoxy(106, 7);
	printf("       ");
	gotoxy(92, 7);
	//设置“食物”为绿色 
	if (mode != 'd')
		printf("吃的\033[32m食物★\033[0m数：%d", food_count);
	if (mode == 'd')
	{
		if (food.x == head_2->x&&food.y == head_2->y)
		{
			mciSendString("play eat_food.mp3", NULL, 0, NULL);
			food_flag_2 = 1;
			food_born();
			grass_reborn();
			score_2 += 10;
			food_count_2++;
			snake_length_2++;
		}
		//下面两句把原来打印出的蛇的长度覆盖掉，否则会造成残留 
		gotoxy(106, 7);
		printf("       ");
		gotoxy(92, 7);
		//设置“食物”为绿色 
		if (mode != 'd')
			printf("吃的\033[32m食物★\033[0m数：%d", food_count_2);
	}
}

void grass_born()
{
	if (!load_flag)
	{
		//毒草0 
		grass.x = rand() % WIDTH + 2;
		if (grass.x % 2 != 0)
			grass.x++;
		if (grass.x > 76)
			grass.x -= 6;
		grass.y = rand() % HEIGHT + 1;
		if (grass.y > 38)
			grass.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == grass.x&&p->y == grass.y)
				grass.y--;
			p = p->next;
		}
		//毒草1 
		grass_1.x = rand() % WIDTH + 2;
		if (grass_1.x % 2 != 0)
			grass_1.x++;
		if (grass_1.x > 76)
			grass_1.x -= 6;
		grass_1.y = rand() % HEIGHT + 1;
		if (grass_1.y > 38)
			grass_1.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == grass_1.x&&p->y == grass_1.y)
				grass_1.y--;
			p = p->next;
		}
		//毒草2 
		grass_2.x = rand() % WIDTH + 2;
		if (grass_2.x % 2 != 0)
			grass_2.x++;
		if (grass_2.x > 76)
			grass_2.x -= 6;
		grass_2.y = rand() % HEIGHT + 1;
		if (grass_2.y > 38)
			grass_2.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == grass_2.x&&p->y == grass_2.y)
				grass_2.y--;
			p = p->next;
		}
	}
}

void eat_grass()
{
	if ((grass.x == head->x&&grass.y == head->y)
		|| (grass_1.x == head->x&&grass_1.y == head->y)
		|| (grass_2.x == head->x&&grass_2.y == head->y))
	{
		load_flag = 0;
		mciSendString("play eat_grass.mp3", NULL, 0, NULL);
		temp = (struct Snake *)malloc(LEN);
		temp = head->next;
		head = temp;
		grass_reborn();
		score -= 20;
		grass_count++;
		snake_length--;
	}
	gotoxy(92, 8);
	if (mode != 'd')
		printf("吃的\033[35m毒草※\033[0m数：%d", grass_count);
	// 如果是双人模式
	if (mode == 'd')
	{
		if ((grass.x == head_2->x&&grass.y == head_2->y)
			|| (grass_1.x == head_2->x&&grass_1.y == head_2->y)
			|| (grass_2.x == head_2->x&&grass_2.y == head_2->y))
		{
			mciSendString("play eat_grass.mp3", NULL, 0, NULL);
			temp_2 = (struct Snake_2 *)malloc(LEN);
			temp_2 = head_2->next;
			head_2 = temp_2;
			grass_reborn();
			score_2 -= 20;
			grass_count_2++;
			snake_length_2--;
		}
		gotoxy(92, 8);
		if (mode != 'd')
			printf("吃的\033[35m毒草※\033[0m数：%d", grass_count_2);
	}
}

void grass_reborn()
{
	// 先把原来的覆盖掉 
	gotoxy(grass.x, grass.y);
	printf("  ");
	gotoxy(grass_1.x, grass_1.y);
	printf("  ");
	gotoxy(grass_2.x, grass_2.y);
	printf("  ");
	// 再重新生成毒草 
	grass_born();
	//items_not_barrier();
}

void boom_born()
{
	if (!load_flag)
	{
		boom.x = rand() % WIDTH + 2;
		if (boom.x % 2 != 0)
			boom.x++;
		if (boom.x > 76)
			boom.x -= 6;
		boom.y = rand() % HEIGHT + 1;
		if (boom.y > 38)
			boom.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == boom.x&&p->y == boom.y)
				boom.y--;
			p = p->next;
		}
	}
}

void eat_boom()
{
	if (boom.x == head->x&&boom.y == head->y)
	{
		load_flag = 0;
		int i = 1;
		p = head;
		while (i <= snake_length / 2)
		{
			p = p->next;
			i++;
		}
		snake_length /= 2;
		p->next = NULL;
		boom_count++;
		score -= snake_length * 15;
		PlaySound(TEXT("eat_boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		clear_screen();
		boom_born();
		//food_born();
	}
	gotoxy(92, 9);
	if (mode != 'd')
		printf("吃的\033[31m炸弹◎\033[0m数：%d", boom_count);
	//玩家2
	if (mode == 'd')
	{
		if (boom.x == head_2->x&&boom.y == head_2->y)
		{
			int i = 1;
			p_2 = head_2;
			while (i <= snake_length_2 / 2)
			{
				p_2 = p_2->next;
				i++;
			}
			snake_length_2 /= 2;
			p_2->next = NULL;
			boom_count_2++;
			score -= snake_length_2 * 15;
			PlaySound(TEXT("eat_boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
			clear_screen();
			boom_born();
		}
		gotoxy(92, 9);
		if (mode != 'd')
			printf("吃的\033[31m炸弹◎\033[0m数：%d", boom_count_2);
	}
}

void eat_wisdom()
{
	if (wisdom.x == head->x&&wisdom.y == head->y)
	{
		load_flag = 0;
		gotoxy(wisdom.x, wisdom.y);
		printf("  ");
		gotoxy(grass.x, grass.y);
		printf("  ");
		gotoxy(grass_1.x, grass_1.y);
		printf("  ");
		gotoxy(grass_2.x, grass_2.y);
		printf("  ");
		gotoxy(boom.x, boom.y);
		printf("  ");
		int i;
		for (i = 30; i < 50;)
		{
			gotoxy(i, 10);
			printf("  ");
			gotoxy(i, 30);
			printf("  ");
			i += 2;
		}
		for (i = 15; i < 25; i++)
		{
			gotoxy(10, i);
			printf("  ");
			gotoxy(68, i);
			printf("  ");
		}
		wisdom_count++;
		PlaySound(TEXT("eat_wisdom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (head->x > food.x) // 如果蛇头在食物右边，向左走 
		{
			dis = (head->x - food.x);
			int i;
			for (i = 2; i <= dis; i += 2)
			{
				if (i == 2 && current_dir == 'd') // 如果原来方向是右，先向下或上移一个 
					if (head->y != 38)
						move('s');
					else move('w');
				move('a');
			}
		}
		else // 如果蛇头在食物左边，向右走 
		{
			dis = (food.x - head->x);
			int i;
			for (i = 2; i <= dis; i += 2)
			{
				if (i == 2 && current_dir == 'a')
					if (head->y != 38)
						move('s');
					else move('w');
				move('d');
			}
		}
		if (head->y > food.y) // 如果蛇头在食物下面，向上走 
		{
			dis = head->y - food.y;
			int i;
			for (i = 1; i <= dis; i++)
			{
				move('w');
			}
		}
		else
		{
			dis = food.y - head->y;
			int i;
			for (i = 1; i <= dis; i++)
			{
				move('s');
			}
		}
		eat_food();
		wisdom_born();
		barrier_born(level);
		Sleep(1000);
	}
	gotoxy(90, 15);
	//设置“智慧草”为黄色 
	if (mode != 'd')
		printf("吃的\033[33m智慧草◆\033[0m数：%d", wisdom_count);
}

void restart()
{
	init_view();
	snake_born();
	start_game(mode);
}

void next_level()
{
	if (level == 1 && score >= 150)
	{
		current_dir == 'd';
		level = 2;
		system("cls");
		gotoxy(50, 20);
		PlaySound(TEXT("next_level.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("恭喜进入下一关");
		gotoxy(50, 22);
		printf("三秒后自动进入下一关");
		Sleep(3500);
		restart();
		snake_length = INITSNAKELEN;
		printf("通关所需分数：250");
	}
	if (level == 2 && score >= 250)
	{
		level = 3;
		system("cls");
		gotoxy(50, 20);
		PlaySound(TEXT("next_level.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("恭喜进入下一关");
		gotoxy(50, 22);
		printf("三秒后自动进入下一关");
		Sleep(3500);
		restart();
		snake_length = INITSNAKELEN;
	}
	if (level == 3 && score >= 400)
	{
		system("cls");
		gotoxy(50, 20);
		printf("Congratulations!");
		gotoxy(50, 22);
		printf("游戏胜利");
	}
}

void init_data()
{
	snake_length = 3;
	food_count = 0;
	grass_count = 0;
	boom_count = 0;
	wisdom_count = 0;
	score = 0;
}

void v_control()
{
	//速度控制 
	if (food_count <= 10)
		speed = 90;
	else if (food_count > 10 && food_count <= 15 && speed == 90)
		speed = 80;
	else if (food_count > 15 && food_count <= 20 && speed == 80)
		speed = 70;
	else if (food_count > 20 && food_count <= 30 && speed == 70)
		speed = 60;
	else if (food_count > 30 && speed == 60)
		speed = 50;
	else if (level == 3)
		speed = 50;
	gotoxy(94, 13);
	if (mode != 'd')
		printf("当前的速度：%d", 100 - speed);
	if (mode == 'd') // 如果是双人模式，Sleep时间是一半速度才与非双人模式时相同 
		speed /= 2;
	Sleep(speed);
}

//存档 
void save()
{
	//把闯到的关保存下来
	FILE * f_level_record;
	f_level_record = fopen(file_l_record, "r");
	int record_level;
	fscanf(f_level_record, "%d", &record_level);
	if (record_level < level)
	{
		f_level_record = fopen(file_l_record, "w");
		fprintf(f_level_record, "%d", level);
		fclose(f_level_record);
	}
	else
		fclose(f_level_record);
	//把信息保存下来
	FILE * fp;
	if (mode == 'l')
	{
		fp = fopen(file_level, "r");
		fscanf(fp, "%s %d %d %s %d %d %s %d %d", n[0], &s[0], &l[0], n[1], &s[1], &l[1], n[2], &s[2], &l[2]);
	}
	else if (mode == 'i')
	{
		fp = fopen(file_i, "r");
		fscanf(fp, "%s %d %s %d %s %d", n[0], &s[0], n[1], &s[1], n[2], &s[2]);
	}
	else if (mode == 't')
	{
		fp = fopen(file_t, "r");
		fscanf(fp, "%s %d %s %d %s %d", n[0], &s[0], n[1], &s[1], n[2], &s[2]);
	}
	fclose(fp);
	int t[3];
	if (score > s[2])
	{
		s[2] = score;
		strncpy(n[2], name, 20);
		l[2] = level;
	}
	if (s[0] >= s[1] && s[0] >= s[2] && s[1] >= s[2])
	{
		t[0] = 0;
		t[1] = 1;
		t[2] = 2;
	}
	else if (s[0] >= s[1] && s[0] >= s[2] && s[1] < s[2])
	{
		t[0] = 0;
		t[1] = 2;
		t[2] = 1;
	}
	else if (s[1] >= s[0] && s[1] >= s[2] && s[0] >= s[2])
	{
		t[0] = 1;
		t[1] = 0;
		t[2] = 2;
	}
	else if (s[1] >= s[0] && s[1] >= s[2] && s[0] < s[2])
	{
		t[0] = 1;
		t[1] = 2;
		t[2] = 0;
	}
	else if (s[2] >= s[0] && s[2] >= s[1] && s[0] >= s[1])
	{
		t[0] = 2;
		t[1] = 0;
		t[2] = 1;
	}
	else if (s[2] >= s[0] && s[2] >= s[1] && s[0] < s[1])
	{
		t[0] = 2;
		t[1] = 1;
		t[2] = 0;
	}
	if (mode == 'l')
	{
		fp = fopen(file_level, "w");
		fprintf(fp, "%s %d %d\n%s %d %d\n%s %d %d\n", n[t[0]], s[t[0]], l[t[0]], n[t[1]], s[t[1]], l[t[1]], n[t[2]], s[t[2]], l[t[2]]);
	}
	else if (mode == 'i')
	{
		fp = fopen(file_i, "w");
		fprintf(fp, "%s %d\n%s %d\n%s %d\n", n[t[0]], s[t[0]], n[t[1]], s[t[1]], n[t[2]], s[t[2]]);
	}
	else if (mode == 't')
	{
		fp = fopen(file_t, "w");
		fprintf(fp, "%s %d\n%s %d\n%s %d\n", n[t[0]], s[t[0]], n[t[1]], s[t[1]], n[t[2]], s[t[2]]);
	}
	fclose(fp);
}

void save_on_game()
{
	FILE * f_on_game;
	if (mode == 'l')
	{
		f_on_game = fopen(file_on_l, "w");
		fprintf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, score,
			food_count, grass_count, boom_count, wisdom_count, snake_length,
			food.x, food.y, grass.x, grass.y, grass_1.x, grass_1.y, grass_2.x, grass_2.y, boom.x, boom.y, wisdom.x, wisdom.y,
			level);
		fclose(f_on_game);
	}
	if (mode == 'i')
	{
		f_on_game = fopen(file_on_i, "w");
		fprintf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, score,
			food_count, grass_count, boom_count, wisdom_count, snake_length,
			food.x, food.y, grass.x, grass.y, grass_1.x, grass_1.y, grass_2.x, grass_2.y, boom.x, boom.y, wisdom.x, wisdom.y);
		fclose(f_on_game);
	}
	if (mode == 't')
	{
		f_on_game = fopen(file_on_t, "w");
		fprintf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, score,
			food_count, grass_count, boom_count, wisdom_count, snake_length,
			food.x, food.y, grass.x, grass.y, grass_1.x, grass_1.y, grass_2.x, grass_2.y, boom.x, boom.y, wisdom.x, wisdom.y);
		fclose(f_on_game);
	}
}

void choose_level()
{
	//下面是选关
	gotoxy(56, 10);
	printf("level 1");
	gotoxy(56, 20);
	printf("level 2");
	gotoxy(56, 30);
	printf("level 3");
	gotoxy(46, 36);
	printf("输入关卡数字以进入关卡：");
	scanf("%d", &level);
	if (level > 3)
	{
		printf("无此关卡");
		choose_level();
	}
	FILE * f_level_record;
	f_level_record = fopen(file_l_record, "r");
	int i_level_record;
	fscanf(f_level_record, "%d", &i_level_record);
	if (level > i_level_record)
	{
		printf("此关卡未解锁，请重新选择关卡\n");
		system("pause");
		gotoxy(0, 37);
		printf("                                                      \n                                                  "); // 把上面两行字覆盖掉
		choose_level();
	}
	switch (level)
	{
	case 1:
		init_data();
		init_view();
		gotoxy(92, 17);
		printf("通关所需分数：150");
		snake_born();
		start_game(mode);
		break;
	case 2:
		score = 150;
		speed = 80;
		restart();
		speed = 70;
		break;
	case 3:
		speed = 70;
		score = 250;
		restart();
		speed = 50;
		break;
	}
}

void barrier_born(int level)
{
	switch (level)
	{
	case 1:
		break;
	case 2:
		for (barrier_i = 30; barrier_i < 50;)
		{
			gotoxy(barrier_i, 10);
			printf("■");
			gotoxy(barrier_i, 30);
			printf("■");
			barrier_i += 2;
		}
		for (barrier_i = 15; barrier_i < 25; barrier_i++)
		{
			gotoxy(10, barrier_i);
			printf("■");
			gotoxy(68, barrier_i);
			printf("■");
		}
		break;
	case 3:
		break;
	}
}

void eat_barrier(int level)
{
	switch (level)
	{
	case 3:
		//撞墙死的情况 
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
		{
			mciSendString("close bgm.mp3", NULL, 0, NULL);
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("蛇因撞墙而死");
			gotoxy(96, 31);
			printf("你的分数是%d", score);
			gotoxy(96, 33);
			printf("按R键重新开始");
			gotoxy(96, 34);
			printf("按M键回到主菜单");
			gotoxy(96, 35);
			printf("按其它键退出");
			save();
			char c;
			c = _getch();
			if (c == 'r')
			{
				relief();
				init_data();
				restart();
			}
			if (c == 'm')
			{
				relief();
				menu();
			}
			else
				exit(0);
		}
		break;
	case 1:
		//撞墙死的情况 
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
		{
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("蛇因撞墙而死");
			gotoxy(96, 31);
			printf("你的分数是%d", score);
			gotoxy(96, 33);
			printf("按R键重新开始");
			gotoxy(96, 34);
			printf("按M键回到主菜单");
			gotoxy(96, 35);
			printf("按其它键退出");
			save();
			char c;
			c = _getch();
			if (c == 'r')
			{
				relief();
				init_data();
				restart();
			}
			if (c == 'm')
			{
				relief();
				menu();
			}
			else
				exit(0);
		}
		break;
	case 2:
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39 // 撞墙
			|| (head->x == 10 && head->y >= 15 && head->y <= 24) //下面四个撞到障碍 
			|| (head->x == 68 && head->y >= 15 && head->y <= 24)
			|| (head->x >= 30 && head->x <= 48 && head->y == 10)
			|| (head->x >= 30 && head->x <= 48 && head->y == 30))
		{
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("蛇因撞墙而死");
			gotoxy(96, 31);
			printf("你的分数是%d", score);
			gotoxy(96, 33);
			printf("按R键重新开始");
			gotoxy(96, 34);
			printf("按M键回到主菜单");
			gotoxy(96, 35);
			printf("按其它键退出");
			save();
			char c;
			c = _getch();
			if (c == 'r')
			{
				relief();
				init_data();
				restart();
			}
			if (c == 'm')
			{
				relief();
				menu();
			}
			else
				exit(0);
		}
		break;
	}
}

void if_level_3()
{
	if (level == 3)
	{
		//第三关没有智慧草
		wisdom.x = 200;
		wisdom.y = 200;
		if ((head->y == boom.y&&head->x >= boom.x - 4 && head->x <= boom.x + 4)
			|| (head->x == boom.x&&head->y >= boom.y - 2 && head->y <= boom.y + 2))
		{
			gotoxy(boom.x, boom.y);
			printf("\033[31m◎\033[0m");
		}
		else
		{
			gotoxy(boom.x, boom.y);
			printf("  ");
		}
	}

}

void load()
{
	FILE * f_on_game;
	if (mode == 'l')
	{
		f_on_game = fopen(file_on_l, "r");
		fscanf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, &score,
			&food_count, &grass_count, &boom_count, &wisdom_count, &snake_length,
			&food.x, &food.y, &grass.x, &grass.y, &grass_1.x, &grass_1.y, &grass_2.x, &grass_2.y, &boom.x, &boom.y, &wisdom.x, &wisdom.y,
			&level);
	}
	if (mode == 'i')
	{
		f_on_game = fopen(file_on_i, "r");
		fscanf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, &score,
			&food_count, &grass_count, &boom_count, &wisdom_count, &snake_length,
			&food.x, &food.y, &grass.x, &grass.y, &grass_1.x, &grass_1.y, &grass_2.x, &grass_2.y, &boom.x, &boom.y, &wisdom.x, &wisdom.y);
	}
	if (mode == 't')
	{
		f_on_game = fopen(file_on_t, "r");
		fscanf(f_on_game, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			name, &score,
			&food_count, &grass_count, &boom_count, &wisdom_count, &snake_length,
			&food.x, &food.y, &grass.x, &grass.y, &grass_1.x, &grass_1.y, &grass_2.x, &grass_2.y, &boom.x, &boom.y, &wisdom.x, &wisdom.y);
	}
	fclose(f_on_game);
	init_view();
	snake_born_load();
	load_flag = 1;
	start_game(mode);
}

void snake_born_load()
{
	part = temp = (struct Snake *)malloc(LEN);
	part->x = WIDTH / 2;
	part->y = HEIGHT / 2;
	part->pervious = NULL;
	int i;
	for (i = 0; i <= snake_length; i++)
	{
		if (i == 0)
		{
			head = part;
		}
		else
		{
			part->pervious = temp;
			temp->next = part;
		}
		temp = part;
		part = (struct Snake *)malloc(LEN);
		part->x = temp->x - 2;
		part->y = temp->y;
	}
	temp->next = NULL;
	p = head;
	int n = 1;
	do
	{
		if (n == 1)
		{
			gotoxy(p->x, p->y);
			printf("\033[40;36;5m●\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("●");
		}
		p = p->next;
	} while (p->next != NULL);
}

void relief()
{
	struct Snake * p1, *p2;
	p1 = (struct Snake *)malloc(LEN);
	p2 = (struct Snake *)malloc(LEN);
	p1 = head, p2 = head;
	do
	{
		p2 = p2->next;
		free(p1);
		p1 = p2;
	} while (p2->next != NULL);
	free(p1);
}

void death_judge() // 死亡判定 
{
	//第二关撞到障碍 
	eat_barrier(level);
	//太短而死
	if (snake_length < 3)
	{
		mciSendString("close bgm.mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(96, 30);
		printf("蛇因太短而死");
		gotoxy(96, 31);
		printf("你的分数是%d", score);
		gotoxy(96, 33);
		printf("按R键重新开始");
		gotoxy(96, 34);
		printf("按M回到主菜单");
		gotoxy(96, 35);
		printf("按其它键退出");
		save();
		char c;
		c = _getch();
		if (c == 'r')
		{
			relief();
			init_data();
			restart();
		}
		if (c == 'm')
		{
			relief();
			menu();
		}
		else
			exit(0);
	}
	//自食而死 
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
		if (head->x == p->x&&head->y == p->y)
		{
			mciSendString("close bgm.mp3", NULL, 0, NULL);
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("蛇因自食而死");
			gotoxy(96, 31);
			printf("你的分数是%d", score);
			gotoxy(96, 33);
			printf("按R键重新开始");
			gotoxy(96, 34);
			printf("按M回到主菜单");
			gotoxy(96, 35);
			printf("按其它键退出");
			//保存进度 
			save();
			char c;
			c = _getch();
			if (c == 'r')
			{
				relief();
				init_data();
				restart();
			}
			if (c == 'm')
			{
				relief();
				menu();
			}
			else
				exit(0);
		}
	}
}

void death_judge_double()
{
	if (snake_length < 3)
	{
		mciSendString("close bgm.mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("玩家1的蛇因太短而死，玩家2获胜\n");
		system("pause");
	}
	if (snake_length_2 < 3)
	{
		mciSendString("close bgm.mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("玩家2的蛇因太短而死，玩家1获胜\n");
		system("pause");
	}
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
		if (head->x == p->x&&head->y == p->y)
		{
			mciSendString("close bgm.mp3", NULL, 0, NULL);
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(60, 30);
			printf("玩家1的蛇因自食而死，玩家2获胜\n");
			system("pause");
		}
	}
	p_2 = head_2;
	while (p_2->next != NULL)
	{
		p_2 = p_2->next;
		if (head_2->x == p_2->x&&head_2->y == p_2->y)
		{
			mciSendString("close bgm.mp3", NULL, 0, NULL);
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(60, 30);
			printf("玩家2的蛇因自食而死，玩家1获胜\n");
			system("pause");
		}
	}
	if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
	{
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("玩家1的蛇因撞墙而死，玩家2获胜\n");
		system("pause");
	}
	if (head_2->x == 0 || head_2->x == 78 || head_2->y == 0 || head_2->y == 39)
	{
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("玩家2的蛇因撞墙而死，玩家1获胜\n");
		system("pause");
	}
	if (head->x == head_2->x&&head->y == head_2->y)
	{
		gotoxy(60, 30);
		printf("两蛇头相撞，平手\n");
		system("pause");
	}
	p_2 = head_2;
	while (p_2->next != NULL)
	{
		p_2 = p_2->next;
		if (head->x == p_2->x&&head->y == p_2->y)
		{
			gotoxy(60, 30);
			printf("玩家1的蛇撞到了玩家2的蛇身，玩家2获胜\n");
			system("pause");
		}
	}
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
		if (head_2->x == p->x&&head_2->y == p->y)
		{
			gotoxy(60, 30);
			printf("玩家2的蛇撞到了玩家1的蛇身，玩家1获胜\n");
			system("pause");
		}
	}
}

void items_not_barrier()
{
	int i;
	for (i = 30; i < 50;)
	{
		if (food.x == i && (food.y == 10 || food.y == 30))
			food.y--;
		if (boom.x == i && (boom.y == 10 || boom.y == 30))
			boom.y--;
		if (grass.x == i && (grass.y == 10 || grass.y == 30))
			grass.y--;
		if (grass_1.x == i && (grass_1.y == 10 || grass_1.y == 30))
			grass_1.y--;
		if (grass_2.x == i && (grass_2.y == 10 || grass_2.y == 30))
			grass_2.y--;
		if (wisdom.x == i && (wisdom.y == 10 || wisdom.y == 30))
			wisdom.y--;
		i += 2;
	}
	for (i = 15; i < 25; i++)
	{
		if ((food.x == 10 || food.x == 68) && food.y == i)
			food.x -= 2;
		if ((boom.x == 10 || boom.x == 68) && boom.y == i)
			boom.x -= 2;
		if ((grass.x == 10 || grass.x == 68) && grass.y == i)
			grass.x -= 2;
		if ((grass_1.x == 10 || grass_1.x == 68) && grass_1.y == i)
			grass_1.x -= 2;
		if ((grass_2.x == 10 || grass_2.x == 68) && grass_2.y == i)
			grass_2.x -= 2;
		if ((wisdom.x == 10 || wisdom.x == 68) && wisdom.y == i)
			wisdom.x -= 2;
	}

}

//下面不改了 
void move(char current_dir)
{
	switch (current_dir)
	{
	case 'd':
	case 'D':
		if (old_dir != 'a') // 如果不是掉头走的 
		{
			temp = (struct Snake *)malloc(LEN);
			temp->x = head->x + 2;
			temp->y = head->y;
			temp->next = head;
			head = temp;
			if (!food_flag)
			{
				p = head;
				while (p->next->next != NULL)
				{
					p = p->next;
				}
				p->next = NULL;
			}
			print_snake();
			old_dir = current_dir;
		}
		else
			move(old_dir);
		break;
	case 'w':
	case 'W':
		if (old_dir != 's')
		{
			temp = (struct Snake *)malloc(LEN);
			temp->x = head->x;
			temp->y = head->y - 1;
			temp->next = head;
			head = temp;
			if (!food_flag) // 如果food_flag=0,即没有吃到食物，就把最后一节消掉
			{
				p = head;
				while (p->next->next != NULL)
				{
					p = p->next;
				}
				p->next = NULL;
			} // 否则就是吃到食物，不进行上述操作，就是相当于增加了一节身体
			print_snake();
			old_dir = current_dir;
		}
		else
			move(old_dir);
		break;
	case 'a':
	case 'A':
		if (old_dir != 'd')
		{
			temp = (struct Snake *)malloc(LEN);
			temp->x = head->x - 2;
			temp->y = head->y;
			temp->next = head;
			head = temp;
			if (!food_flag)
			{
				p = head;
				while (p->next->next != NULL)
				{
					p = p->next;
				}
				p->next = NULL;
			}
			print_snake();
			old_dir = current_dir;
		}
		else
			move(old_dir);
		break;
	case 's':
	case 'S':
		if (old_dir != 'w')
		{
			temp = (struct Snake *)malloc(LEN);
			temp->x = head->x;
			temp->y = head->y + 1;
			temp->next = head;
			head = temp;
			if (!food_flag)
			{
				p = head;
				while (p->next->next != NULL)
				{
					p = p->next;
				}
				p->next = NULL;
			}
			print_snake();
			old_dir = current_dir;
		}
		else
			move(old_dir);
		break;
	default:
		break;
	}
}

void move_2(char current_dir_2)
{
	switch (current_dir_2)
	{
	case 'l':
	case 'L':
		if (old_dir_2 != 'j') // 如果不是掉头走的 
		{
			temp_2 = (struct Snake_2 *)malloc(LEN);
			temp_2->x = head_2->x + 2;
			temp_2->y = head_2->y;
			temp_2->next = head_2;
			head_2 = temp_2;
			if (!food_flag_2)
			{
				p_2 = head_2;
				while (p_2->next->next != NULL)
				{
					p_2 = p_2->next;
				}
				p_2->next = NULL;
			}
			print_snake();
			old_dir_2 = current_dir_2;
		}
		else
			move(old_dir_2);
		break;
	case 'i':
	case 'I':
		if (old_dir_2 != 'k')
		{
			temp_2 = (struct Snake_2 *)malloc(LEN);
			temp_2->x = head_2->x;
			temp_2->y = head_2->y - 1;
			temp_2->next = head_2;
			head_2 = temp_2;
			if (!food_flag_2)
			{
				p_2 = head_2;
				while (p_2->next->next != NULL)
				{
					p_2 = p_2->next;
				}
				p_2->next = NULL;
			}
			print_snake();
			old_dir_2 = current_dir_2;
		}
		else
			move(old_dir_2);
		break;
	case 'j':
	case 'J':
		if (old_dir_2 != 'l')
		{
			temp_2 = (struct Snake_2 *)malloc(LEN);
			temp_2->x = head_2->x - 2;
			temp_2->y = head_2->y;
			temp_2->next = head_2;
			head_2 = temp_2;
			if (!food_flag_2)
			{
				p_2 = head_2;
				while (p_2->next->next != NULL)
				{
					p_2 = p_2->next;
				}
				p_2->next = NULL;
			}
			print_snake();
			old_dir_2 = current_dir_2;
		}
		else
			move(old_dir_2);
		break;
	case 'k':
	case 'K':
		if (old_dir_2 != 'i')
		{
			temp_2 = (struct Snake_2 *)malloc(LEN);
			temp_2->x = head_2->x;
			temp_2->y = head_2->y + 1;
			temp_2->next = head_2;
			head_2 = temp_2;
			if (!food_flag_2)
			{
				p_2 = head_2;
				while (p_2->next->next != NULL)
				{
					p_2 = p_2->next;
				}
				p_2->next = NULL;
			}
			print_snake();
			old_dir_2 = current_dir_2;
		}
		else
			move(old_dir_2);
		break;
	default:
		break;
	}
}

void wisdom_born()
{
	if (!load_flag)
	{
		wisdom.x = rand() % WIDTH + 2;
		if (wisdom.x % 2 != 0)
			wisdom.x++;
		if (wisdom.x > 76)
			wisdom.x -= 6;
		wisdom.y = rand() % HEIGHT + 1;
		if (wisdom.y > 38)
			wisdom.y -= 2;
		p = head;
		while (p->next != NULL)
		{
			if (p->x == wisdom.x&&p->y == wisdom.y)
				wisdom.y--;
			p = p->next;
		}
	}
	gotoxy(wisdom.x, wisdom.y);
	printf("\033[33m◆\033[0m");
}

void clear_screen() // 地图部分清屏 
{
	int i;
	int j;
	for (i = 2; i < WIDTH - 2;)
	{
		for (j = 1; j < HEIGHT - 1; j++)
		{
			gotoxy(i, j);
			printf("  "); // 注意这里要打两个空格
		}
		i += 2;
	}
}

void about_time()
{
	time_t tmpcal_ptr;
	struct tm * tmp_ptr = NULL;
	time(&tmpcal_ptr);
	tmp_ptr = localtime(&tmpcal_ptr);
	printf("%d.%d.%d ", (1900 + tmp_ptr->tm_year), (1 + tmp_ptr->tm_mon), tmp_ptr->tm_mday);
	if (tmp_ptr->tm_hour < 10)
		printf("0%d:", tmp_ptr->tm_hour);
	else
		printf("%d:", tmp_ptr->tm_hour);
	if (tmp_ptr->tm_min < 10)
		printf("0%d:", tmp_ptr->tm_min);
	else
		printf("%d:", tmp_ptr->tm_min);
	if (tmp_ptr->tm_sec < 10)
		printf("0%d", tmp_ptr->tm_sec);
	else
		printf("%d", tmp_ptr->tm_sec);

	//下面一对if-else是毒草,炸弹闪烁 
	if (level != 3 && tmp_ptr->tm_sec % 2 == 0)
	{
		gotoxy(grass.x, grass.y);
		printf("  ");
		gotoxy(grass_1.x, grass_1.y);
		printf("  ");
		gotoxy(grass_2.x, grass_2.y);
		printf("  ");
		gotoxy(boom.x, boom.y);
		printf("  ");
	}
	else if (level != 3 && tmp_ptr->tm_sec % 2 == 1)
	{
		gotoxy(grass.x, grass.y);
		printf("\033[35m※\033[0m");
		gotoxy(grass_1.x, grass_1.y);
		printf("\033[35m※\033[0m");
		gotoxy(grass_2.x, grass_2.y);
		printf("\033[35m※\033[0m");
		gotoxy(boom.x, boom.y);
		printf("\033[31m◎\033[0m");
	}
	else if (level == 3 && tmp_ptr->tm_sec % 3 == 0)
	{
		gotoxy(grass.x, grass.y);
		printf("\033[35m※\033[0m");
		gotoxy(grass_1.x, grass_1.y);
		printf("\033[35m※\033[0m");
		gotoxy(grass_2.x, grass_2.y);
		printf("\033[35m※\033[0m");
	}
	else
	{
		gotoxy(grass.x, grass.y);
		printf("  ");
		gotoxy(grass_1.x, grass_1.y);
		printf("  ");
		gotoxy(grass_2.x, grass_2.y);
		printf("  ");
	}
	//PlaySound(TEXT("bgm.wav"), NULL, SND_LOOP | SND_ASYNC | SND_NOSTOP);
	if (mode == 't')
	{
		if (start_time_i == 1)
		{
			start_time = tmp_ptr->tm_min * 60 + tmp_ptr->tm_sec;
			start_time_i = 0;
		}
		int now_time = tmp_ptr->tm_min * 60 + tmp_ptr->tm_sec;
		if (now_time - start_time == TIME) // 这里设置竞速时间
		{
			save();
			while (1)
			{
				gotoxy(96, 30);
				printf("时间到");
				gotoxy(96, 32);
				printf("你的分数是%d", score);
			}
		}
	}
}

void set_windows() // 设置控制台窗口
{
	system("mode con cols=120 lines=40"); //设定窗口大小co1s是宽度，1ines是长度，
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
	RECT rc;
	GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形
	//改变cmd窗口风格
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE)&~WS_THICKFRAME&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
	//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
}

void grass_blink() // 毒草闪烁 
{
	// 在about_time()里 
}

void music_play()
{
	gotoxy(58, 20);
	printf("加载中......");
	typedef struct
	{
		int frequency;
		int duration;
	}PU;
	//以下谱子是《社会主义好》的一段 
	PU t[] = { B5,1,B5,2,B5,1,D6,2,B5,5,A5,2,G5,1,E5,2,G5,1,A5,2,B5,2,K,5,B5,1,B5,2,B5,1,D6,2,E6,4,D6,3,E5,1
			,E5,2,E5,1,G5,2,A5,2,K,5,B5,3,A5,1,G5,3,G5,2,E5,1,D5,3,B5,2,D6,1,B5,2,A5,1,G5,2,A5,1,G5,2,A5,2,B5,3,E5,
			3,G5,1,D5,2,K,5,B5,2,D6,1,B5,1,D6,2,E6,3,E6,2,D6,1,E6,5,B5,2,A5,3,B5,1,E6,3,D6,3,B5,3,A5,3,K,1,E6,2,D6,
			1,B5,2,A5,1,G5,4,K,3,E6,2,D6,1,B5,2,A5,1,G5,4, };
	int i;
	//结构体数组的长度sizeof(t)/sizeof(PU)得到，总结构体数组大小 / 单个结构体大小
	for (i = 0; i < sizeof(t) / sizeof(PU); i++)
	{
		Beep(t[i].frequency, t[i].duration*P);
		gotoxy(i, 21);
		printf("-");
	}
}
