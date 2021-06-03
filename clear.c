#include <stdio.h>
#include <windows.h>
char a[5][100]={"\0","多项式A为:","多项式B为:","多项式A与B的乘积为:","多项式A与B的和为:"};


void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clear()
{
    system("cls");
    gotoxy(10,10);
}
int main()
{
    clear();
    printf("%s",a[1]);

    return 0;
}