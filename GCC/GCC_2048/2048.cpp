//
//  2048.cpp
//  GCC_2048
//
//  Created by Niu Panfeng on 6/28/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int M[16],X=16,W,k,K[]={2,3,1};

int w(int d,int i,int j)
{
    if(d<=0)
        return 4*i+j;
    return w(d-1,j,3-i);
}
void s(int f,int d)
{
    int i=4,j,l,P;
    for (; i--; )
    {
        j = k = l = 0;
        for (; k<4; )
        {
            if(j<4)
            {
                P = M[w (d, i, j++)];
                W |= P >> 11;
                l *P && (f ? M[w (d, i, k)] = l << (l == P) : 0, k++);
                l = l ? (P ? (l - P ? P : 0) : l) : P;
            }
            else
            {
                f ? M[w (d, i, k)] = l : 0;
                ++k;
                W |= 2 * !l;
                l = 0;
            }
        }
    }
}
void T()
{
    
    int i=X+rand()%X;
    for (; M[i % X] * i; i--);
    i ? M[i % X] = 2 << rand () % 2 : 0;
    W = i = 0;
   
    for (; i < 4; i++)
    {
       s (0, i);
    }
   
    // Prints the tiles onto the terminal
    i = X;
    puts ("\e[2J\e[H");
    
    for (; i--;)
    {
        if (M[i])
            printf ("%4d|", M[i]);
        else
            printf ("%s", "    |");
        
       
        // every 4th cell is followed by a line-break
       if (0 == (i & 3))
             putchar ('\n');

    }
        // read input from keyboard
    if (!(W - 2))
    {
        read (0, &k, 3);
        s (1, K[(k >> X) % 4]);
        T ();
    }
   
}


int main()
{
    system("stty cbreak");
    
    /* Intializes random number generator */
    srand ((unsigned) time (NULL));
    
    T ();
    
    // Game has finished by this point
    // If win, display "WIN". Otherwise, display "LOSE".
    puts (W & 1 ? "WIN" : "LOSE");
    
    return 0;
}