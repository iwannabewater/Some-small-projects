#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 20
#define COL 20

#define NEXT 0
#define PLAYER1_WIN 1
#define PLAYER2_WIN 2
#define DRAW 3

#define PLAYER1 1
#define PLAYER2 2

enum Dir
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFT_UP,
    RIGHT_DOWN,
    RIGHT_UP,
    LEFT_DOWN
};

//computer or player move postion,just for simple
int x = 0;
int y = 0;

void Menu()
{
    printf("############################\n");
    printf("## 0. Exit        1. Play ##\n");
    printf("############################\n");
    printf("Please Select# ");
}

void PlayerMove(int board[ROW][COL], int who)
{
    while (1)
    {
        printf("\nPlayer[ %d ] Please Enter Your Postion# ", who);
        scanf("%d%d", &x, &y);
        if (x < 0 || y > COL)
        {
            printf("Postion Error!\n");
        }
        else if (board[x][y] != 0)
        {
            printf("Postion Is Occupied!\n");
        }
        else
        {
            board[x][y] = who;
            break;
        }
    }
}

int ChessCount(int board[ROW][COL], enum Dir d)
{
    int _x = x;
    int _y = y;

    int count = 0;
    while (1)
    {
        switch (d)
        {
        case LEFT:
            _y--;
            break;
        case RIGHT:
            _y++;
            break;
        case UP:
            _x--;
            break;
        case DOWN:
            _x++;
            break;
        case LEFT_UP:
            _x--, _y--;
            break;
        case RIGHT_DOWN:
            _x++, _y++;
            break;
        case RIGHT_UP:
            _x--, _y++;
            break;
        case LEFT_DOWN:
            _x++, _y--;
            break;
        }
        if (_x < 0 || _x > ROW - 1 || _y < 0 || _y > COL - 1)
        {
            break;
        }
        if (board[x][y] == board[_x][_y])
        {
            count++;
        }
        else
        {
            break;
        }
    }
    return count;
}
int IsOver(int board[ROW][COL])
{
    int count1 = ChessCount(board, LEFT) + ChessCount(board, RIGHT) + 1;
    int count2 = ChessCount(board, UP) + ChessCount(board, DOWN) + 1;
    int count3 = ChessCount(board, LEFT_UP) + ChessCount(board, RIGHT_DOWN) + 1;
    int count4 = ChessCount(board, LEFT_DOWN) + ChessCount(board, RIGHT_UP) + 1;
    if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)
    {
        if (board[x][y] == PLAYER1)
        {
            return PLAYER1_WIN;
        }
        else
        {
            return PLAYER2_WIN;
        }
    }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == 0)
            {
                return NEXT;
            }
        }
    }
    return DRAW;
}

void ShowBoard(int board[ROW][COL])
{
    printf("\033c");
    printf("\n\n  ");
    for (int i = 0; i < COL; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < ROW; i++)
    {
        printf("%-3d", i);
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == PLAYER1)
            {
                //player1
                printf(" ¡ñ ");
            }
            else if (board[i][j] == PLAYER2)
            {
                //player2
                printf(" ¡ð ");
            }
            else
            {
                //Space
                printf(" . ");
            }
        }
        printf("\n");
    }
}

void Game()
{
    int board[ROW][COL];
    memset(board, '\0', sizeof(board));
    int result = NEXT;
    do
    {
        ShowBoard(board);
        PlayerMove(board, PLAYER1);
        result = IsOver(board);
        if (NEXT != result)
        {
            break;
        }
        ShowBoard(board);
        PlayerMove(board, PLAYER2);
        result = IsOver(board);
        if (NEXT != result)
        {
            break;
        }
    } while (1);

    ShowBoard(board);
    switch (result)
    {
    case PLAYER1_WIN:
        printf("Player1 win!\n");
        break;
    case PLAYER2_WIN:
        printf("Player2 win!\n");
        break;
    case DRAW:
        printf("Player1 darw Player2!\n");
        break;
    }
}
int main()
{
    int quit = 0;
    int select = 0;
    while (!quit)
    {
        Menu();
        scanf("%d", &select);
        switch (select)
        {
        case 0:
            quit = 1;
            break;
        case 1:
            Game();
            break;
        defalut:
            printf("Please Select Again!\n");
            break;
        }
    }
}
