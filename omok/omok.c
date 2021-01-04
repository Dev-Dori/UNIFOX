#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                                 
#include <Windows.h>                               
#include <process.h>

int stone_turn = 1;  // (��������) �浹�� �鵹 ����   1=�� 2=��
int Omok_Board[20][20] = { 0, }; // ��ǥ�� �迭�� ǥ���Ҷ� ����ϴ� (�����迭)
int time = 0;   //�ð��� ��Ÿ���� ��������

int explain(); //��� ���� �Լ�
void Omok_Game_background();  //�ٵ���
void Gotoxy(int x, int y);  //�ٵ��� ��ǥ�� �����ϴ� �Լ�
void Put_stone(int color);    //���� ���� �Լ�
int control_stone(); // �ٵϾ� ��Ʈ�� �Լ�
void rm_stone(int x, int y); //�ٵϾ� �̵��� ��ĭ �� ����
int game_check(int x, int y);  //���и� �����ϴ� �Լ�
unsigned _stdcall timer(void *arg); //Ÿ�̸�

int main(void) {
	system("mode con cols=90 lines=22 | title ����");
	int cot= explain();
	if (cot == 0) return 0; 
	Omok_Game_background();
	control_stone();
}

int explain()
{
	char press;
	Gotoxy(15, 2);
	printf("*****  ���� ��   *****\n");
	Gotoxy(9,5);
	printf("* �浹�� ���� ���� �ΰ� �˴ϴ� *\n");
	Gotoxy(9, 7);
	printf("* ���� 5�� �̻� ����Ǹ� �¸��մϴ� *\n");
	Gotoxy(9, 9);
	printf("* ������ �����Ͻ÷��� Space Bar�� �����ּ��� *\n");
	Gotoxy(9, 11);
	printf("* ������ �����Ͻ÷��� Esc�� �����ּ��� *");


	Gotoxy(17, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("*** ���۹� ***\n\n\n");
	printf("����1 :: ���� �̵�: W    �Ʒ��� �̵�: W    ���� �̵�: A    ������ �̵�: D  ����: SPACEBAR\n\n");
	printf("����2 :: ���� �̵�: 8    �Ʒ��� �̵�: 5    ���� �̵�: 4    ������ �̵�: 6  ����:    0\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("                                                                           10320 - �ӵ���");


	for (; 1;) {
		press = _getch();
		if (press == 27) return 0;
		if (press == 32) {
			Gotoxy(0, 0);
			system("cls");
			return 1;
		}
	}
}

//��Ʈ�� �г�
int control_stone() {
	int x = 10, y = 10;
	char key;
	Gotoxy(10, 10);
	Put_stone(stone_turn);
	_beginthreadex(NULL, 0, timer, 0, 0, NULL);
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		Gotoxy(28, 10);
		printf("-[ ");
		Put_stone(stone_turn);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf(" �����Դϴ�. ]-");   //����

		key = _getch();

		if (65 <= key && key <= 90) key = +32;
		if (key == 56) key = 119;
		else if (key == 48	) key = 32;
		else if (key == 52) key = 97;
		else if (key == 54) key = 100;
		else if (key == 53) key = 115;

		switch (key) {     //a=97 d=100 w=119 s=115
		case 119:  //w
			if (1 <= y - 1 && y - 1 < 19) {
				rm_stone(x, y);
				y--;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 115:  //s
			if (1 < y + 1 && y + 1 <= 19) {
				rm_stone(x, y);
				y++;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 100:  //d
			if (1 < x + 1 && x + 1 <= 19) {
				rm_stone(x, y);
				x++;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 97:  //a
			if (1 <= x - 1 && x - 1 < 19) {
				rm_stone(x, y);
				x--;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;


		case 32:
			Gotoxy(29, 8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("��ǥ : [%d][%d]", x, y);
			Gotoxy(x, y);
			if (Omok_Board[x][y] == 0) {
				Omok_Board[x][y] = stone_turn;
				Put_stone(stone_turn);

				if (game_check(x, y) == 1) {
					Gotoxy(22, 12);
					printf("################################################");
					Gotoxy(22, 13);
					printf("##                  ");
					Put_stone(stone_turn);
					printf("�� �¸�                 ##");
					Gotoxy(22, 14);
					printf("################################################");
					Gotoxy(38, 1);  printf("                ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					Gotoxy(29, 16); printf("[ ���� :: ESC  ]");
					stone_turn = 4; // Ÿ�̸� ����
					
					while (1) {
						key = _getch();
						if(key==27) _endthread();
						
					}
				}

			if (stone_turn==1) stone_turn++;
			else if(stone_turn==2)stone_turn--;


			Gotoxy(27, 7);
			printf("                            ");

			break;
			} 
			else {
				Gotoxy(27, 7);
				printf("[����!!] �̹� ���� �ֽ��ϴ�");
				continue;
			}
		case 27:
			exit(0);
		}
	}
}

//���������� �����
void rm_stone(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);									// ���� ���� ��ġ�� ������ �̵� 

	if (Omok_Board[x][y] == 0) {
		if (x == 1 && y == 1)                           // �װ��� ���� 1,1 (���� �� �𼭸�)�� ���
			printf("����");
		else if (x == 19 && y == 1) {                     // �װ��� ���� 19,1 (������ �� �𼭸�)�� ���
			printf("  ");  //���� ó���뵵
			Gotoxy(x, y);
			printf("��");
		}
		else if (x == 1 && y == 19)                     // �װ��� ���� 0,19 (���� �Ʒ� �𼭸�)�� ���
			printf("����");
		else if (x == 19 && y == 19) {                  // �װ��� ���� 19,19 (������ �Ʒ� �𼭸�)�� ���
			printf("  ");
			Gotoxy(x, y);
			printf("��");
		}
		else if (x == 1)                                // �װ��� ���� 1,* (������)�� ���                 
			printf("����");
		else if (y == 1)                                // �װ��� ���� *,1 (����)�� ���
			printf("����");
		else if (x == 19) {								// �װ��� ���� 19,* (��������)�� ���
			printf("  ");
			Gotoxy(x, y);
			printf("��");
		}
		else if (y == 19)                               // �װ��� ���� *,19 (�Ʒ���)�� ���
			printf("����");
		else                                           // �� ���� ���
			printf("����");
	}else if(Omok_Board[x][y]==1){
		Put_stone(1);
	}else if(Omok_Board[x][y] == 2){
		Put_stone(2);
	}
}

//��ǥ
void Gotoxy(int x, int y){
	COORD Pos;
	Pos.X = 2*x-2;   // ù�ٿ� x��ǥ�� 1�� ����
	Pos.Y = y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//����ȭ�� ����
void Omok_Game_background(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	int i, j;
	printf("����");
	for (i = 0; i < 17; i++) printf("����");

	printf("��  %d\n",1);

	for (i = 0; i < 17; i++) {
		printf("����");
		for (j = 0; j < 17; j++)
			printf("����");
		printf("��  %d\n",i+2);
	}
	printf("����");
	for (i = 0; i < 17; i++)printf("����");
	printf("��  %d\n",19);

	Gotoxy(1, 48);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("==========================================================================================\n");
	printf("����1 :: ���� �̵�: W    �Ʒ��� �̵�: W    ���� �̵�: A    ������ �̵�: D  ����: SPACEBAR\n");
	printf("����2 :: ���� �̵�: 8    �Ʒ��� �̵�: 5    ���� �̵�: 4    ������ �̵�: 6  ����:    0");

	Gotoxy(30, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("<----����---->\n");
	Gotoxy(24, 4);
	printf("W A S D �� �����̰� �����̽�Ű�� �����ÿ�\n");
	Gotoxy(39, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("<ESC :: ���� >");
}

//�� ���
void Put_stone(int color) {
	if (color==1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //��
		printf("��");
	}
	else if(color==2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //��
		printf("��");
	}
}


//���� üũ
int game_check(int x, int y) {
	int i, j = 0, k = 1, count = 0;
	int a[20] = { 0, };   //5�� üũ�Ҷ� ����ϴ� �迭 �ʱ�ȭ
	for (i = 0; i <= 5; i++) a[i] = 0; j = 0;  //5�� üũ�Ҷ� ����ϴ� �迭 �ʱ�ȭ
	for (i = 1; i <= 19; i++) {    //���� üũ
		for (j = 0; j <= 4; j++) {  // 
			a[j] = Omok_Board[i + j][y];
		}
		for (j = 0; j <= 4; j++) {  // 
			if (a[j] == stone_turn) count++;
		}
		if (count == 5) return 1;
		for (j = 0; j < 5; j++) a[i] = 0;
		count = 0;
	}

	for (i = 0; i <=5; i++) a[i] = 0; j = 0;  //5�� üũ�Ҷ� ����ϴ� �迭 �ʱ�ȭ
	for (i = 1; i <= 19; i++) {    //���� üũ
		for (j = 0; j <= 4; j++) {  // 
			a[j] = Omok_Board[x][i + j];
		}
		for (j = 0; j <= 4; j++) {  // 
			if (a[j] == stone_turn) count++;
		}
		if (count == 5) return 1;
		for (j = 0; j < 5; j++) a[i] = 0;
		count = 0;
	}

	for (i = 0; i <= 5; i++) a[i] = 0;  j = 0;//5�� üũ�Ҷ� ����ϴ� �迭 �ʱ�ȭ
	for (i = x - y + 1; i+5 <= 19; i++) {    //�밢���� üũ
		if (i > 0) {
			for (j = 0; j <= 4; j++) {  // 
				a[j] = Omok_Board[i+j][k+j];
			}
			for (j = 0; j <= 4; j++) {  // 
				if (a[j] == stone_turn) count++;
			}
			if (count == 5) return 1;
			for (j = 0; j < 5; j++) a[i] = 0;
			count = 0;
		}
		k++;
	}

	k = 1; 	for (i = 0; i <= 5; i++) a[i] = 0;  j = 0;//5�� üũ�Ҷ� ����ϴ� �迭 �ʱ�ȭ
	for (i = x + y - 1; i >= 1; i--) {    //�밢���� üũ
		if (i > 0) {
			for (j = 0; j <= 4; j++) {  // 
				a[j] = Omok_Board[k + j][i - j];
			}
			for (j = 0; j <= 4; j++) {  //  
				if (a[j] == stone_turn) count++;
			}
			if (count == 5) return 1;
			for (j = 0; j < 5; j++) a[j] = 0;
			count = 0;
		}
		k++;
	}
}
unsigned _stdcall timer(void *arg) {
	while (1) {
		Gotoxy(22, 1);
		printf("[�÷��̽ð� : %d sec]", time);
		if (stone_turn == 4) return 1;
		Sleep(1040);
		time++;
	}
}