#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int WINDOW_HEIGHT = 10;
int WINDOW_WIDTH = 10;
SNAKE[10*10][2] = {{0, 3}, {0, 2}, {0, 1}, {0, 0}};
SNAKE_LENGTH = 4;
SNAKE_DIRECTION = 1;
APPLE[2] = {5, 5};
GAME_OVER = 0;

int min(int a, int b)
{
    return a > b ? b : a;
}

void delay(float number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void prints()
{
    for(int i = 0;i<WINDOW_HEIGHT*2;i++) printf("\033[F");
    printf("\033[K");

    for(int i = 0;i<WINDOW_HEIGHT;i++)
    {
        for(int j = 0; j<WINDOW_WIDTH; j++)
        {
            char print = '.';

            if(APPLE[0] == j && APPLE[1] == i) print = '0';

            for(int k = 0;k<SNAKE_LENGTH; k++)
            {
                if(SNAKE[k][0] == i && SNAKE[k][1] == j) print = '#';
                if(SNAKE[0][0] == i && SNAKE[0][1] == j) print = '@';
            }


            printf("%c ", print);
        }
        printf("\n\n");
    }
}

void snake_long(int l)
{
    int old = SNAKE_LENGTH;
    SNAKE_LENGTH = l;

    if(old > SNAKE_LENGTH) for(int i = SNAKE_LENGTH - 2; i > old - 1;i--)
    {
        SNAKE[i+1][0] = SNAKE[i][0];
        SNAKE[i+1][1] = SNAKE[i][1];
    }
}

void snake_move(int direction)
{
    for(int i = min(SNAKE_LENGTH-1, WINDOW_HEIGHT*WINDOW_WIDTH-1);i >= 0; i--)
    {
        SNAKE[i+1][0] =  SNAKE[i][0];
        SNAKE[i+1][1] =  SNAKE[i][1];
    }

    switch(direction)
    {

    case 0:
        SNAKE[0][0]--;
        if(SNAKE[0][0] < 0) GAME_OVER = 1;
        break;
    case 1:
        SNAKE[0][1]++;
        if(SNAKE[0][1] > WINDOW_WIDTH-1) GAME_OVER = 1;
        break;
    case 2:
        SNAKE[0][0]++;
        if(SNAKE[0][0] > WINDOW_HEIGHT-1) GAME_OVER = 1;
        break;
    case 3:
        SNAKE[0][1]--;
        if(SNAKE[0][1] < 0) GAME_OVER = 1;
        break;
    }
}

int main()
{
    char press = '\0';

    while(GAME_OVER != 1)
    {
        char press = '\0';
        if (kbhit()) press = getch();

        if(press == 'w') snake_move(0);
        if(press == 'd') snake_move(1);
        if(press == 's') snake_move(2);
        if(press == 'a') snake_move(3);

        if(press == 'q') snake_long(SNAKE_LENGTH-1);
        if(press == 'ed') snake_long(SNAKE_LENGTH+1);

        prints();

        delay(0.2);
    }
}
