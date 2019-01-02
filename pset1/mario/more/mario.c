#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // pyramid height
    int h = 0;
    while (h < 1 || h > 8)
    {
        h = get_int("Height: ");
    }

    // pyramid gap
    int g = 2;



    for (int i = 0; i < h; i++)
    {
        for (int j = 1; j <= h; j++)
        {
            if (j<(h-i)) printf(" ");
            else printf("#");
        }

        for (int k = 0; k < g; k++)
        {
            printf(" ");
        }

        for (int l = 1; l <= h; l++)
        {
            if (l<=i+1) printf("#");
        }

        printf("\n");
    }

}