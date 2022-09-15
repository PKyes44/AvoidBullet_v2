#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Console.h"

#define MAX 10
#define MAP 50
#define BackColor 15

struct ST_OBJ {
	int x = 0;
	int y = 0;
	int way = 0;
	int directx = 0;
	int directy = 0;
	bool BActive = false;
};

ST_OBJ g_stBullet[MAX];
ST_OBJ g_stPlayer;
int g_iScore = 0;

int Map[MAP][MAP];

// �Ѿ˻���
void SpawnBullet();
// �Է�Ű
void InputProcess();
// �Ѿ�ó��
void DisBullet();
// ����üũ
void CheckFail();
// �� ����
void CreateMap();
// ���۸޴�
void StartMenu();
// ���� ����
void GameMain();
// �Ѿ� ��ǥ �Ҵ�
void SB_Process(int way, int i);
// �� ���
void DrawMap();
// ���� rand()
int randx();
// ������Ʈ �ʿ� ���� 
void MinOBJ();
// ������Ʈ �ʱ�ȭ
void ResetOBJ();
// ���� ���
void Score() {
	g_iScore++;
	GotoXY(0, 0);
	printf("Score : %d", g_iScore);
}
// ���Ӽ���
void Init() {
	// ��� Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));

	g_stPlayer.x = 25;
	g_stPlayer.y = 25;
	g_stPlayer.BActive = true;

	srand(time(NULL));

	SetColor(BackColor, 0);
	system("mode con cols=100 lines=50");
}

// ������Ʈ �ʱ�ȭ
void ResetOBJ() {
	for (int i = 0; i < MAX; i++) {
		g_stBullet[i].BActive = false;
	}
}

int main() {
	// ���Ӽ���
	Init();

	// ���۸޴�
	StartMenu();
	
	// ������Ʈ �ʱ�ȭ
	ResetOBJ();

	// �� ����
	CreateMap();

	// ���� ����
	GameMain();

	return 0;
}

// �Ѿ˻���
void SpawnBullet() {
	// 1 : U , 2 : D , 3 : L , 4 : R
	int way = 1;
	for (int i = 0; i < MAX; i++) {
		if (!g_stBullet[i].BActive) {
			switch (i) {
			case 1: way = 1; break;
			case 2: way = 1; break;
			case 3: way = 2; break;
			case 4: way = 2; break;
			case 5: way = 3; break;
			case 6: way = 3; break;
			case 7: way = 4; break;
			case 8: way = 4; break;
			}
			SB_Process(way, i);
			g_stBullet[i].directx = MAP - g_stBullet[i].x;
			g_stBullet[i].directy = MAP - g_stBullet[i].y;
		}
	}
}

// ������Ʈ �ʿ� ����
void MinOBJ() {
	for (int x = 0; x < MAP; x++) {
		for (int y = 0; y < MAP; y++) {
			// �Ѿ� �ε���
			for (int i = 0; i < MAX; i++) {
				if (g_stBullet[i].BActive) {
					// ��ǥ�� ���� ��� �ʿ� ����
					if (x == g_stBullet[i].x && y == g_stBullet[i].y) {
						Map[y][x] = 'B';
					}
				}
			}
		}
	}
	// �÷��̾� ����
	Map[g_stPlayer.y][g_stPlayer.x] = 'P';
}

// �� ���
void DrawMap() {
	for (int x = 0; x < MAP; x++) {
		for (int y = 0; y < MAP; y++) {
			GotoXY(x * 2, y);
			if (Map[y][x] == 'B') {
				printf("��");
			}
			else if (Map[y][x] == 'P') {
				printf("��");
			}
		}
	}
}

// �Ѿ� ��ǥ �Ҵ�
void SB_Process(int way, int i) {
	switch (way) {
	case 1: g_stBullet[i].x = randx(); g_stBullet[i].y = 0; break;
	case 2: g_stBullet[i].x = randx(); g_stBullet[i].y = 50; break;
	case 3: g_stBullet[i].y = randx(); g_stBullet[i].x = 0; break;
	case 4: g_stBullet[i].y = randx(); g_stBullet[i].x = 50; break;
	}
	g_stBullet[i].way = way;
	g_stBullet[i].BActive = true;
}

// �Է�Ű
void InputProcess() {
	bool Check_pm = false;
	int tmpx = g_stPlayer.x;
	int tmpy = g_stPlayer.y;
	if (GetAsyncKeyState(VK_DOWN) && 0x8000) {
		g_stPlayer.y++;
		if (g_stPlayer.y > MAP) {
			g_stPlayer.y = MAP;
		}
		Check_pm = true;
	}
	if (GetAsyncKeyState(VK_UP) && 0x8000) {
		g_stPlayer.y--;
		if (g_stPlayer.y < 0) {
			g_stPlayer.y = 0;
		}
		Check_pm = true;
	}
	if (GetAsyncKeyState(VK_LEFT) && 0x8000) {
		g_stPlayer.x--;
		if (g_stPlayer.x < 0) {
			g_stPlayer.x = 0;
		}
		Check_pm = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) && 0x8000) {
		g_stPlayer.x++;
		if (g_stPlayer.x > MAP) {
			g_stPlayer.x = MAP;
		}
		Check_pm = true;
	}
	// ��ǥ �̵� �� �� �� ��ǥ ����
	if (Check_pm) Map[tmpy][tmpx] = 0;
}

// ���� ����
void GameFail() {
	while (1) {
		Clear();
		GotoXY(42, 10);
		printf("Ŭ���� ����!");
		GotoXY(0, 30);
		printf("%47s : %d", "Score", g_iScore);
		GotoXY(40, 33);
		printf("�ٽ� ���� : ENTER");
		GotoXY(40, 34);
		printf("���� ���� : ESC");
		if (GetAsyncKeyState(VK_SPACE) && 0x8000) {
			main();
			break;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) && 0x8000) {
			exit(0);
		}
		Sleep(100);
	}
}

// �Ѿ� ó��
void DisBullet() {
	for (int i = 0; i < MAX; i++) {
		Map[g_stBullet[i].y][g_stBullet[i].x] = 0;
		int minusx = g_stBullet[i].directx - g_stBullet[i].x;
		int minusy = g_stBullet[i].directy - g_stBullet[i].y;

		if (abs(minusx) >= abs(minusy)) {
			if (minusx < 0)	g_stBullet[i].x--;
			else if (minusx > 0) g_stBullet[i].x++;
			// �밢�� �̵�
			minusx = g_stBullet[i].directx - g_stBullet[i].x;
			if (minusx < minusy) {
				if (minusy < 0) g_stBullet[i].y--;
				else if (minusy > 0) g_stBullet[i].y++;
			}
		}
		else if (abs(minusx) < abs(minusy)) {
			if (minusy < 0) g_stBullet[i].y--;
			else if (minusy > 0) g_stBullet[i].y++;
			// �밢�� �̵�
			minusy = g_stBullet[i].directy - g_stBullet[i].y;
			if (minusy < minusx) {
				if (minusy < 0) g_stBullet[i].y--;
				else if (minusy > 0) g_stBullet[i].y++;
			}
		}
		if (minusx == 0 || minusy == 0) {
			g_stBullet[i].BActive = false;
			g_stBullet[i].y = 0;
			g_stBullet[i].x = 0;
		}
	}
}

// ���۸޴�
void StartMenu() {
	while (1) {
		Clear();
		GotoXY(43, 10);
		printf("�Ѿ����ϱ�");
		GotoXY(33, 30);
		printf("�����Ϸ��� �ƹ� Ű�� �����ּ���");

		if (GetAsyncKeyState(VK_RETURN) && 0x8000) {
			break;
		}
		Sleep(100);
	}
}

// ���� ����
void GameMain() {
	while (1) {
		Clear();

		// �Ѿ� ����
		SpawnBullet();

		// �ʿ� OBJ ����
		MinOBJ();

		// �� ����
		DrawMap();

		// input
		InputProcess();

		// �Ѿ� ó��
		DisBullet();

		// ���ӽ���üũ
		CheckFail();

		// ����
		Score();

		Sleep(5);
	}
}

// ����
int randx()
{
	static int flag = 0;
	int retVal;
	if (flag == 0)
	{
		srand(time(NULL));
		rand(); rand(); rand(); rand();
		srand(rand());
		flag = 1;
	}
	retVal = rand() % MAP;
	return retVal;
}

// �� ���� �� �ʱ�ȭ
void CreateMap() {
	for (int i = 0; i < MAP; i++) {
		for (int j = 0; j < MAP; j++) {
			Map[i][j] = 0;
		}
	}
}

// ����üũ
void CheckFail() {
	for (int i = 0; i < MAX; i++) {
		if (g_stPlayer.y == g_stBullet[i].y) {
			if (g_stPlayer.x == g_stBullet[i].x) {
				GameFail();
			}
		}
	}
}