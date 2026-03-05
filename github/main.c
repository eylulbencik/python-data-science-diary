#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 5


int isValid(char attempt)
{

    FILE *fp = fopen("password.txt", "r");
    if (fp == NULL )
    {
        fprintf(stderr, "Error opening file\n");
        return 0;
    }
    char password[256];
    if (fgets(password, sizeof(password),fp) == NULL)
    {
        fclose(fp);
        fprintf(stderr, "Cannot read the password.txt or it is empty \n");
        return 0;
    }
    fclose(fp);
}

void bruteForce()
{
    char charset[] = "abcdefghijklmnopqrstuvwyz";
    int charSetSize = strlen(charset);
    char attempt[MAX_LEN];
    clock_t start = clock();

    printf("Brute force is start! ");

    for (int len = 1; len < MAX_LEN; len++)
    {
        int index[MAX_LEN]={0};
        while (1)
        {
            for (int i = 0; i<len; i++)
            {
                attempt[i] = charset[index[i]];
                attempt[len] = '0';

                printf("Trying...");

                if (isValid(attempt))
                {
                    clock_t end = clock();
                    double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
                    printf("Password found!");
                    printf("Time spent is %f seconds\n", time_spent);
                    return;
                }
                int pos = len - 1;
                while (pos >= 0 )
                {
                    index[pos]++;
                    if (index[pos] < charSetSize)
                    {
                        break;
                    }
                        index[pos] = 0;
                        pos--;
                    if (pos <0){
                        break;
                    }
                    printf("Password is not found!");
                }
            }
        }
    }
}
int main()
{
    bruteForce();
    return 0;
}