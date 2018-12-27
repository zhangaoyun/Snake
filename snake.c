#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define WIDTH 80 // ��Ϸ�����ͼ�Ŀ�� 
#define HEIGHT 40 // ��Ϸ�����ͼ�ĸ߶� 
#define INITSNAKELEN 3
#define TIME 120 //����ʱ�������
#define LEN sizeof(struct Snake) //Snake�ṹ���ֽ��� 

#define K 0//���Ƶ��0�����ǲ��죬��Ϊ���� 

//���µ����б�ʾ�����ķ��ž�����fl studio 14 ��fl keys�ı�ע�������һ����ٵı�ע��һ�� �� 
//ֻ�������˶ȵ�����Ƶ�� ����Ϊһ���������Դﵽ��Ƶ�ʴ�Ŷ���������Щ���� 
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
#define P 125   //�ۺ�bpm==120��ԭbpmΪ105���˴�ȡ�˸�����ֵ 

//�߽ṹ�� 
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

//���2���ߵĽṹ�� 
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
//�ļ����ȫ�ֱ��� 
char file_level[] = { "scores.dat" }; // �ؿ�ģʽ�洢�ļ��� 
char n[3][20];
int s[3];
int l[3];
char file_t[] = { "scores_t.dat" };  // ����ģʽ
char file_i[] = { "scores_i.dat" };
char file_l_record[] = { "level_record.dat" }; // ��¼�������Ĺؿ���û�н�����һ�ؾͲ���ֱ��ѡ��һ�� 

// ����������Ϸ�����д�ĵ� 
char file_on_l[] = { "onlevel.dat" };
char file_on_i[] = { "oninfinite.dat" };
char file_on_t[] = { "ontime.dat" };

//��ʼ������Ϊ�� 
char current_dir = 'd';
char old_dir = 'd';
char current_dir_2 = 'i';
char old_dir_2 = 'i';

//��ʼ���������Ե�ʳ����������Ե����ݵ��������ٶ� 
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

void set_windows(); // ���ÿ���̨����
void setting();
void music_play();
void init_view(); // ��ʼ����Ϸ����
void gotoxy(int x, int y);
void snake_born(); // ������
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
//�������2��һЩ����
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
	system("color 0B"); // ������Ϸǰ��Ϊ��ɫ������Ϊ��ɫ 	
	gotoxy(50, 20);
	printf("������������֣�");
	scanf("%s", name);
	system("cls");
	gotoxy(46, 19);
	printf("��\033[31mȷ����Ӣ�����뷨��\033[0m������Ϸ");
	gotoxy(46, 20);
	printf("���,%s,���ո����ʼ", name);
	char start;
	while (start = _getch() != ' ');
	menu();
}

void menu()
{
	char mode_c;
	system("cls");
	printf("    A-��ʼ��Ϸ\n    B-������Ϸ\n    C-�鿴��Ϸ˵��\n    D-�鿴���а�\n    Esc-�˳���Ϸ\n");
	c = getch();
	if (c == 'a')
	{
		printf("\n    ��ѡ��ģʽ��\n    L-�ؿ�ģʽ\n    I-����ģʽ\n    T-����ģʽ\n    D-˫��ģʽ\n");
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
			printf("\n���������2������");
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
		printf("\n    ��ѡ��Ҫ���ص�ģʽ��\n    L-�ؿ�ģʽ\n    I-����ģʽ\n    T-����ģʽ\n");
		mode = _getch();
		load();
	}
	else if (c == 'c')
	{
		printf("��Ϸ˵��\n");
		printf("������˵��\n");
		printf("WASD������������(˫��ģʽ���2JIKL������������)\n");
		printf("\033[32m��\033[0m��ʳ������߼�һ�����壬������10\n");
		printf("\033[35m��\033[0m�Ƕ��ݣ������߼�һ�����壬������20\n");
		printf("\033[31m��\033[0m��ը���������߼�һ�����壬������ը������������15\n");
		printf("\033[33m��\033[0m���ǻ۲ݣ��������Զ�Ѱ����һ��ʳ��Ե�ʳ���ͣ��һ��\n");
		printf("�Ե�ʳ������Խ�࣬���˶����ٶ�Խ��\n");
		printf("�ؿ�ģʽһ�������أ��ﵽһ�������ɽ�����һ��\n");
		printf("����ģʽû����һ�أ���¼����ʱ�ķ���\n");
		printf("����ģʽ����120��ʱ��õ��ķ���\n");
		printf("˫��ģʽ����λ��ң��ķ������ķ��ܱ�\n");
		char back_c;
		back_c = _getch();
		while (back_c != 13) // �س���ֵΪ13 
		{
			back_c = _getch();
		}
		system("cls");
		menu();
	}
	else if (c == 'd')
	{
		system("cls");
		printf("Ҫ�鿴�ĸ�ģʽ�����а�");
		printf("\n    ��ѡ��ģʽ��\n    L-�ؿ�ģʽ\n    I-����ģʽ\n    T-����ģʽ\n");
		mode_c = getch();
		if (mode_c == 'l')
		{
			printf("�ؿ�ģʽ���а�\n");
			printf("����      ����      ����      �ؿ�\n");
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
			printf("����ģʽ���а�\n");
			printf("����      ����      ����\n");
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
			printf("����ģʽ���а�\n");
			printf("����      ����      ����\n");
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
		while (back_c != 13) // �س���ֵΪ13 
		{
			back_c = _getch();
		}
		system("cls");
		menu();
	}
	else if (c == 27) //Esc��ֵΪ27 
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
			printf("\033[40;37;5m��\033[0m\n");
			n++;
		}
		else
		{
			gotoxy(p_2->x, p_2->y);
			printf("\033[40;37;5m��\033[0m\n");
		}
		p_2 = p_2->next;
	} while (p_2->next != NULL);
}

void init_view() // ��ʼ����Ϸ����
{
	system("cls");
	system("color 0B"); // ������Ϸǰ��Ϊ��ɫ������Ϊ��ɫ 
	int i;
	int j;
	//��һ��ѭ���ȴ�ӡ�����з���
	for (i = 0; i < WIDTH;)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			gotoxy(i, j);
			printf("��");
		}
		i += 2;
		Sleep(30);
	}
	//��һ��ѭ����ӡ�ո��γɵ�ͼ
	for (i = 2; i < WIDTH - 2;)
	{
		for (j = 1; j < HEIGHT - 1; j++)
		{
			gotoxy(i, j);
			printf("  "); // ע������Ҫ�������ո�
		}
		i += 2;
		Sleep(30);
	}
	if (mode != 'd')
	{
		gotoxy(94, 5);
		printf("��ң�%s", name);
	}
	else
	{
		gotoxy(94, 5);
		printf("���1��%s", name);
		gotoxy(94, 7);
		printf("���2��%s", name_2);
	}
	if (mode == 'l')
	{
		gotoxy(94, 3);
		printf("�ؿ�ģʽ");
		gotoxy(94, 4);
		printf("level:%d", level);
	}
	if (mode == 'i')
	{
		gotoxy(94, 3);
		printf("����ģʽ");
	}
	if (level == 2)
	{
		gotoxy(92, 17);
		printf("ͨ�����������250");
	}
	if (mode == 'd')
	{
		gotoxy(94, 3);
		printf("˫��ģʽ");
	}
	if (mode == 't')
	{
		gotoxy(94, 3);
		printf("����ģʽ");
	}
}

void gotoxy(int x, int y)  // ��꺯��������ƶ���(x,y)λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	//�����������ع�� 
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
			printf("\033[40;36;5m��\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("��");
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
			printf("\033[44;37;5m������%d\033[0m ", score);
		if (mode == 'l')
		{
			next_level();
		}
		gotoxy(106, 12);
		printf("      ");
		gotoxy(96, 12);
		if (mode != 'd')
			printf("�ߵĳ��ȣ�%d", snake_length);
		gotoxy(90, 38);
		about_time(); // ����ʱ��Ķ��������綾����˸ ,����ģʽʱ�����
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
			printf("\033[40;36;5m��\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("��");
		}
		p = p->next;
	} while (p->next != NULL);
	gotoxy(p->x, p->y);
	printf("  ");
	//������˫��ģʽ�´�ӡ�ڶ����� 
	if (mode == 'd')
	{
		p_2 = head_2;
		n = 1;
		do
		{
			if (n == 1)
			{
				gotoxy(p_2->x, p_2->y);
				printf("\033[40;37;5m��\033[0m\n");
				n++;
			}
			else
			{
				gotoxy(p_2->x, p_2->y);
				printf("\033[40;37;5m��\033[0m\n");
			}
			p_2 = p_2->next;
		} while (p_2->next != NULL);
		gotoxy(p_2->x, p_2->y);
		printf("  ");
	}
	//�ٶȿ���
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
	printf("\033[32m��\033[0m");
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
	//���������ԭ����ӡ�����ߵĳ��ȸ��ǵ����������ɲ��� 
	gotoxy(106, 7);
	printf("       ");
	gotoxy(92, 7);
	//���á�ʳ�Ϊ��ɫ 
	if (mode != 'd')
		printf("�Ե�\033[32mʳ���\033[0m����%d", food_count);
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
		//���������ԭ����ӡ�����ߵĳ��ȸ��ǵ����������ɲ��� 
		gotoxy(106, 7);
		printf("       ");
		gotoxy(92, 7);
		//���á�ʳ�Ϊ��ɫ 
		if (mode != 'd')
			printf("�Ե�\033[32mʳ���\033[0m����%d", food_count_2);
	}
}

void grass_born()
{
	if (!load_flag)
	{
		//����0 
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
		//����1 
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
		//����2 
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
		printf("�Ե�\033[35m���ݡ�\033[0m����%d", grass_count);
	// �����˫��ģʽ
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
			printf("�Ե�\033[35m���ݡ�\033[0m����%d", grass_count_2);
	}
}

void grass_reborn()
{
	// �Ȱ�ԭ���ĸ��ǵ� 
	gotoxy(grass.x, grass.y);
	printf("  ");
	gotoxy(grass_1.x, grass_1.y);
	printf("  ");
	gotoxy(grass_2.x, grass_2.y);
	printf("  ");
	// ���������ɶ��� 
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
		printf("�Ե�\033[31mը����\033[0m����%d", boom_count);
	//���2
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
			printf("�Ե�\033[31mը����\033[0m����%d", boom_count_2);
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
		if (head->x > food.x) // �����ͷ��ʳ���ұߣ������� 
		{
			dis = (head->x - food.x);
			int i;
			for (i = 2; i <= dis; i += 2)
			{
				if (i == 2 && current_dir == 'd') // ���ԭ���������ң������»�����һ�� 
					if (head->y != 38)
						move('s');
					else move('w');
				move('a');
			}
		}
		else // �����ͷ��ʳ����ߣ������� 
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
		if (head->y > food.y) // �����ͷ��ʳ�����棬������ 
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
	//���á��ǻ۲ݡ�Ϊ��ɫ 
	if (mode != 'd')
		printf("�Ե�\033[33m�ǻ۲ݡ�\033[0m����%d", wisdom_count);
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
		printf("��ϲ������һ��");
		gotoxy(50, 22);
		printf("������Զ�������һ��");
		Sleep(3500);
		restart();
		snake_length = INITSNAKELEN;
		printf("ͨ�����������250");
	}
	if (level == 2 && score >= 250)
	{
		level = 3;
		system("cls");
		gotoxy(50, 20);
		PlaySound(TEXT("next_level.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("��ϲ������һ��");
		gotoxy(50, 22);
		printf("������Զ�������һ��");
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
		printf("��Ϸʤ��");
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
	//�ٶȿ��� 
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
		printf("��ǰ���ٶȣ�%d", 100 - speed);
	if (mode == 'd') // �����˫��ģʽ��Sleepʱ����һ���ٶȲ����˫��ģʽʱ��ͬ 
		speed /= 2;
	Sleep(speed);
}

//�浵 
void save()
{
	//�Ѵ����Ĺر�������
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
	//����Ϣ��������
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
	//������ѡ��
	gotoxy(56, 10);
	printf("level 1");
	gotoxy(56, 20);
	printf("level 2");
	gotoxy(56, 30);
	printf("level 3");
	gotoxy(46, 36);
	printf("����ؿ������Խ���ؿ���");
	scanf("%d", &level);
	if (level > 3)
	{
		printf("�޴˹ؿ�");
		choose_level();
	}
	FILE * f_level_record;
	f_level_record = fopen(file_l_record, "r");
	int i_level_record;
	fscanf(f_level_record, "%d", &i_level_record);
	if (level > i_level_record)
	{
		printf("�˹ؿ�δ������������ѡ��ؿ�\n");
		system("pause");
		gotoxy(0, 37);
		printf("                                                      \n                                                  "); // �����������ָ��ǵ�
		choose_level();
	}
	switch (level)
	{
	case 1:
		init_data();
		init_view();
		gotoxy(92, 17);
		printf("ͨ�����������150");
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
			printf("��");
			gotoxy(barrier_i, 30);
			printf("��");
			barrier_i += 2;
		}
		for (barrier_i = 15; barrier_i < 25; barrier_i++)
		{
			gotoxy(10, barrier_i);
			printf("��");
			gotoxy(68, barrier_i);
			printf("��");
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
		//ײǽ������� 
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
		{
			mciSendString("close bgm.mp3", NULL, 0, NULL);
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("����ײǽ����");
			gotoxy(96, 31);
			printf("��ķ�����%d", score);
			gotoxy(96, 33);
			printf("��R�����¿�ʼ");
			gotoxy(96, 34);
			printf("��M���ص����˵�");
			gotoxy(96, 35);
			printf("���������˳�");
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
		//ײǽ������� 
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
		{
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("����ײǽ����");
			gotoxy(96, 31);
			printf("��ķ�����%d", score);
			gotoxy(96, 33);
			printf("��R�����¿�ʼ");
			gotoxy(96, 34);
			printf("��M���ص����˵�");
			gotoxy(96, 35);
			printf("���������˳�");
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
		if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39 // ײǽ
			|| (head->x == 10 && head->y >= 15 && head->y <= 24) //�����ĸ�ײ���ϰ� 
			|| (head->x == 68 && head->y >= 15 && head->y <= 24)
			|| (head->x >= 30 && head->x <= 48 && head->y == 10)
			|| (head->x >= 30 && head->x <= 48 && head->y == 30))
		{
			PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(96, 30);
			printf("����ײǽ����");
			gotoxy(96, 31);
			printf("��ķ�����%d", score);
			gotoxy(96, 33);
			printf("��R�����¿�ʼ");
			gotoxy(96, 34);
			printf("��M���ص����˵�");
			gotoxy(96, 35);
			printf("���������˳�");
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
		//������û���ǻ۲�
		wisdom.x = 200;
		wisdom.y = 200;
		if ((head->y == boom.y&&head->x >= boom.x - 4 && head->x <= boom.x + 4)
			|| (head->x == boom.x&&head->y >= boom.y - 2 && head->y <= boom.y + 2))
		{
			gotoxy(boom.x, boom.y);
			printf("\033[31m��\033[0m");
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
			printf("\033[40;36;5m��\033[0m");
			n++;
		}
		else
		{
			gotoxy(p->x, p->y);
			printf("��");
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

void death_judge() // �����ж� 
{
	//�ڶ���ײ���ϰ� 
	eat_barrier(level);
	//̫�̶���
	if (snake_length < 3)
	{
		mciSendString("close bgm.mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(96, 30);
		printf("����̫�̶���");
		gotoxy(96, 31);
		printf("��ķ�����%d", score);
		gotoxy(96, 33);
		printf("��R�����¿�ʼ");
		gotoxy(96, 34);
		printf("��M�ص����˵�");
		gotoxy(96, 35);
		printf("���������˳�");
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
	//��ʳ���� 
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
			printf("������ʳ����");
			gotoxy(96, 31);
			printf("��ķ�����%d", score);
			gotoxy(96, 33);
			printf("��R�����¿�ʼ");
			gotoxy(96, 34);
			printf("��M�ص����˵�");
			gotoxy(96, 35);
			printf("���������˳�");
			//������� 
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
		printf("���1������̫�̶��������2��ʤ\n");
		system("pause");
	}
	if (snake_length_2 < 3)
	{
		mciSendString("close bgm.mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("���2������̫�̶��������1��ʤ\n");
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
			printf("���1��������ʳ���������2��ʤ\n");
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
			printf("���2��������ʳ���������1��ʤ\n");
			system("pause");
		}
	}
	if (head->x == 0 || head->x == 78 || head->y == 0 || head->y == 39)
	{
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("���1������ײǽ���������2��ʤ\n");
		system("pause");
	}
	if (head_2->x == 0 || head_2->x == 78 || head_2->y == 0 || head_2->y == 39)
	{
		PlaySound(TEXT("death.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		gotoxy(60, 30);
		printf("���2������ײǽ���������1��ʤ\n");
		system("pause");
	}
	if (head->x == head_2->x&&head->y == head_2->y)
	{
		gotoxy(60, 30);
		printf("����ͷ��ײ��ƽ��\n");
		system("pause");
	}
	p_2 = head_2;
	while (p_2->next != NULL)
	{
		p_2 = p_2->next;
		if (head->x == p_2->x&&head->y == p_2->y)
		{
			gotoxy(60, 30);
			printf("���1����ײ�������2���������2��ʤ\n");
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
			printf("���2����ײ�������1���������1��ʤ\n");
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

//���治���� 
void move(char current_dir)
{
	switch (current_dir)
	{
	case 'd':
	case 'D':
		if (old_dir != 'a') // ������ǵ�ͷ�ߵ� 
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
			if (!food_flag) // ���food_flag=0,��û�гԵ�ʳ��Ͱ����һ������
			{
				p = head;
				while (p->next->next != NULL)
				{
					p = p->next;
				}
				p->next = NULL;
			} // ������ǳԵ�ʳ����������������������൱��������һ������
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
		if (old_dir_2 != 'j') // ������ǵ�ͷ�ߵ� 
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
	printf("\033[33m��\033[0m");
}

void clear_screen() // ��ͼ�������� 
{
	int i;
	int j;
	for (i = 2; i < WIDTH - 2;)
	{
		for (j = 1; j < HEIGHT - 1; j++)
		{
			gotoxy(i, j);
			printf("  "); // ע������Ҫ�������ո�
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

	//����һ��if-else�Ƕ���,ը����˸ 
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
		printf("\033[35m��\033[0m");
		gotoxy(grass_1.x, grass_1.y);
		printf("\033[35m��\033[0m");
		gotoxy(grass_2.x, grass_2.y);
		printf("\033[35m��\033[0m");
		gotoxy(boom.x, boom.y);
		printf("\033[31m��\033[0m");
	}
	else if (level == 3 && tmp_ptr->tm_sec % 3 == 0)
	{
		gotoxy(grass.x, grass.y);
		printf("\033[35m��\033[0m");
		gotoxy(grass_1.x, grass_1.y);
		printf("\033[35m��\033[0m");
		gotoxy(grass_2.x, grass_2.y);
		printf("\033[35m��\033[0m");
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
		if (now_time - start_time == TIME) // �������þ���ʱ��
		{
			save();
			while (1)
			{
				gotoxy(96, 30);
				printf("ʱ�䵽");
				gotoxy(96, 32);
				printf("��ķ�����%d", score);
			}
		}
	}
}

void set_windows() // ���ÿ���̨����
{
	system("mode con cols=120 lines=40"); //�趨���ڴ�Сco1s�ǿ�ȣ�1ines�ǳ��ȣ�
	HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
	RECT rc;
	GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����
	//�ı�cmd���ڷ��
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE)&~WS_THICKFRAME&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
	//��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
}

void grass_blink() // ������˸ 
{
	// ��about_time()�� 
}

void music_play()
{
	gotoxy(58, 20);
	printf("������......");
	typedef struct
	{
		int frequency;
		int duration;
	}PU;
	//���������ǡ��������á���һ�� 
	PU t[] = { B5,1,B5,2,B5,1,D6,2,B5,5,A5,2,G5,1,E5,2,G5,1,A5,2,B5,2,K,5,B5,1,B5,2,B5,1,D6,2,E6,4,D6,3,E5,1
			,E5,2,E5,1,G5,2,A5,2,K,5,B5,3,A5,1,G5,3,G5,2,E5,1,D5,3,B5,2,D6,1,B5,2,A5,1,G5,2,A5,1,G5,2,A5,2,B5,3,E5,
			3,G5,1,D5,2,K,5,B5,2,D6,1,B5,1,D6,2,E6,3,E6,2,D6,1,E6,5,B5,2,A5,3,B5,1,E6,3,D6,3,B5,3,A5,3,K,1,E6,2,D6,
			1,B5,2,A5,1,G5,4,K,3,E6,2,D6,1,B5,2,A5,1,G5,4, };
	int i;
	//�ṹ������ĳ���sizeof(t)/sizeof(PU)�õ����ܽṹ�������С / �����ṹ���С
	for (i = 0; i < sizeof(t) / sizeof(PU); i++)
	{
		Beep(t[i].frequency, t[i].duration*P);
		gotoxy(i, 21);
		printf("-");
	}
}
