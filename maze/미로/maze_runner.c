#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                                 
#include <Windows.h>                               
#include <process.h>


int t_set = 0;
int time = 0;   //�ð��� ��Ÿ���� ��������
char map[26][26] = {
 {0  ,1  ,2  ,3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24, 25},
 {1  ,1  ,0  ,1  ,1  ,1  ,1  ,1  ,1  ,1   ,1   ,1   ,1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,  1  ,1},
 {2  ,1  ,0  ,0  ,1  ,0  ,1  ,0  ,1  ,0   ,0   ,1   ,0,   0,   0,   0,   0,   0,   0,   1,   1,   0,   0,   0,  0  ,1},
 {3  ,1  ,1  ,0  ,1  ,0  ,0  ,0  ,0  ,0   ,1   ,0   ,0,   1,   1,   1,   1,   1,   0,   0,   0,   0,   1,   1,  0  ,1},
 {4  ,0  ,0  ,0  ,1  ,0  ,1  ,0  ,1  ,1   ,1   ,1   ,0,   1,   0,   0,   0,   1,   0,   1,   1,   0,   1,   0,  0  ,1},
 {5  ,0  ,1  ,0  ,0  ,0  ,1  ,0  ,1  ,0   ,0   ,0   ,0,   1,   1,   0,   0,   0,   0,   0,   1,   0,   0,   1,  1  ,1},
 {6  ,0,1,0,1,0,0,0,1,0,1,1,1,0,0,1,1,1,1,0,1,1,0,0,0,1},
 {7  ,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1},
 {8  ,0,0,0,1,0,0,1,0,1,1,0,0,0,1,0,1,1,1,1,0,1,1,1,0,1},
 {9  ,1,0,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1},
 {10 ,1,0,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0,1,1},//
 {11 ,0,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,1,0,0,1},
 {12 ,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1},
 {13 ,0,0,0,1,0,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,1},
 {14 ,0,1,0,1,0,0,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1},
 {15 ,0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
 {16 ,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1},
 {17 ,0,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,1,1},
 {18 ,0,0,0,1,0,0,1,1,1,0,1,1,1,1,0,1,0,1,1,0,0,1,0,1,1},
 {29 ,0,1,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1,0,1,0,1,0,1},
 {20 ,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,1,1},
 {21 ,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1},
 {22 ,0,0,1,1,0,0,0,1,1,1,1,1,0,0,1,0,0,0,1,0,0,1,1,0,1},
 {23 ,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1},
 {24 ,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1},
 {25 ,1  ,1  ,1  ,1  ,1  ,1  ,1  ,1  ,1   ,1   ,1   ,1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,  0  ,1}


};

void Gotoxy(int x, int y);
void Put_stone();    //�� ���
int control_stone(); // �� ��Ʈ�� �Լ�
unsigned _stdcall timer(void *arg); //Ÿ�̸�



int main(void) {
	system("mode con cols=100 lines=30 | title �̷�");

	int i, j, key;

	FILE *fp = fopen("save//save.txt", "r");

	if (fp != NULL) {

		Gotoxy(13, 15);
		printf("���̺� ������ �ֽ��ϴ�. ����� ���� ����Ͻðڽ��ϱ�?");
		Gotoxy(15, 16);
		printf("[ ��� : ENTER ]  [ �⺻�� : ESC ]");

		key = _getch();
		printf("%d ", key);
		if (key == 13) {
			system("cls");
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 26; j++)  fscanf(fp, "%d", &map[i][j]);
			}
		}
		else{
			system("cls");
		}
	}

	map[24][25] = 1;

	for (i = 1; i <= 25; i++) {
		for (j = 1; j <= 25; j++) {
			if (map[i][j] == 1) printf("��");
			if (map[i][j] == 0) printf("  ");
		}
		printf("\n");
	}
	Gotoxy(24, 25);
	printf("��");
	map[25][24] = 0;
	control_stone();
}


//��Ʈ�� �г�
int control_stone() {
	int x = 2, y = 1;
	char key;
	Gotoxy(x, y);
	Put_stone();
	_beginthreadex(NULL, 0, timer, 0, 0, NULL);
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  //��y �� x
		key = _getch();
		if (65 <= key && key <= 90) key = +32;
		if (key == 56) key = 119;
		else if (key == 48) key = 32;
		else if (key == 52) key = 97;
		else if (key == 54) key = 100;
		else if (key == 53) key = 115;

		switch (key) {     //a=97 d=100 w=119 s=115
		case 119:  //w
			if (1 <= y - 1 && map[y - 1][x] == 0) {
				Gotoxy(x, y);
				printf("  ");
				y--;
				Gotoxy(x, y);
				Put_stone();
			}
			break;

		case 115:  //s
			if (y + 1 <= 25 && map[y + 1][x] == 0) {
				Gotoxy(x, y);
				printf("  ");
				y++;
				Gotoxy(x, y);
				Put_stone();
			}
			break;

		case 100:  //d
			if (map[y][x + 1] == 0) {
				Gotoxy(x, y);
				printf("  ");
				x++;
				Gotoxy(x, y);
				Put_stone();
			}
			break;

		case 97:  //a
			if (map[y][x - 1] == 0) {
				Gotoxy(x, y);
				printf("  ");
				x--;
				Gotoxy(x, y);
				Put_stone();
			}
			break;

		case 27:
			exit(0);
		}

		Gotoxy(38, 15);
		printf("  %d %d  ", x, y);

		if (x == 24 && y == 25) {
			t_set = -1;
			Gotoxy(38, 15);
			printf("Ż�� ����!");
			while (1);
			break;
		}
	}
}

void Gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x - 2;   // ù�ٿ� x��ǥ�� 1�� ����
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}



void Put_stone() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //��
		printf("��");
}


unsigned _stdcall timer(void *arg) {
	while (1) {
		Gotoxy(40, 1);
		printf("[�÷��̽ð� : %d sec]", time);
		if (t_set == -1) return 1;
		Sleep(1040);
		time++;
	}
}