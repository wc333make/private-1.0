#include <stdio.h>
#include <stdlib.h>

int board[19][19];
int flag;

void init();
int isWin(int x, int y);
int playerMove(int x, int y);
void menuView();
void gameView_ShowBoard();
void winView();
void gameView();
void waitKey();

int main()
{
    menuView();
    return 0;
}

void waitKey() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void init() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            board[i][j] = 0;
        }
    }
    flag = 0;
}

int isWin(int x, int y) {
    int color;
    if (flag % 2 == 0) {
        color = 1;
    }
    else {
        color = 2;
    }

    int dx[4] = { 0, 1, 1, 1 };
    int dy[4] = { 1, 0, 1, -1 };

    for (int dir = 0; dir < 4; dir++) {
        int count = 1;

        for (int step = 1; step < 5; step++) {
            int nx = x + dx[dir] * step;
            int ny = y + dy[dir] * step;
            if (nx >= 0 && nx < 19 && ny >= 0 && ny < 19 && board[nx][ny] == color) {
                count++;
            }
            else {
                break;
            }
        }

        for (int step = 1; step < 5; step++) {
            int nx = x - dx[dir] * step;
            int ny = y - dy[dir] * step;
            if (nx >= 0 && nx < 19 && ny >= 0 && ny < 19 && board[nx][ny] == color) {
                count++;
            }
            else {
                break;
            }
        }

        if (count >= 5) {
            return color;
        }
    }

    return 0;
}

int playerMove(int x, int y) {
    if (x < 0 || x >= 19 || y < 0 || y >= 19) {
        return 0;
    }

    if (board[x][y] == 0) {
        if (flag % 2 == 0) {
            board[x][y] = 1;
        }
        else {
            board[x][y] = 2;
        }
        return 1;
    }

    return 0;
}

void menuView() {
    int choice;
    while (1) {
        system("cls");
        printf("====================\n");
        printf("     五子棋游戏\n");
        printf("====================\n");
        printf("1. 进入游戏\n");
        printf("2. 进入设置\n");
        printf("3.进入排行榜\n");
        printf("4.进入皮肤商店\n");
        printf("5.充值\n"
        printf("6. 退出游戏\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            gameView();
        case 2:
        case 3:
        case 4:
        case 5:
                printf("敬请期待...\n");
                printf("按任意键继续...\n");
                waitKey();
        case 6:
            exit(0);
        default: 
                printf("输入无效，请重新输入！\n");
                printf("按任意键继续...\n");
                waitKey();
        }
    }
}

void gameView_ShowBoard() {
    system("cls");

    printf("   ");
    for (int i = 0; i < 19; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < 19; i++) {
        printf("%2d ", i);
        for (int j = 0; j < 19; j++) {
            if (board[i][j] == 0) {
                printf(" . ");
            }
            else if (board[i][j] == 1) {
                printf(" X ");
            }
            else if (board[i][j] == 2) {
                printf(" O ");
            }
        }
        printf("\n");
    }
}

void winView() {
    if (flag % 2 == 0) {
        printf("\n\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*        黑子 胜利！      *\n");
        printf("*                            *\n");
        printf("******************************\n");
    }
    else {
        printf("\n\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*        白子 胜利！      *\n");
        printf("*                            *\n");
        printf("******************************\n");
    }

    printf("\n按任意键返回主菜单...\n");
    waitKey();
}

void gameView() {
    init();

    while (1) {
        gameView_ShowBoard();

        int x, y;
        if (flag % 2 == 0) {
            printf("当前轮到 黑子(1) 落子\n");
        }
        else {
            printf("当前轮到 白子(2) 落子\n");
        }

        printf("请输入落子坐标 (行 列，用空格隔开): ");
        scanf("%d %d", &x, &y);

        if (playerMove(x, y) == 0) {
            printf("落子失败！坐标无效或该位置已有棋子。\n");
            printf("按任意键重新输入...\n");
            waitKey();
            continue;
        }

        int winStatus = isWin(x, y);
        if (winStatus != 0) {
            gameView_ShowBoard();
            winView();
            break;
        }

        flag++;
    }
}