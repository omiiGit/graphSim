#include "utils.h" 

static void itoa(int num,char* s,int* i)
{
    if(num < 0)
    {
        s[(*i)++] = '-';
        num = -num;
    }

    if(num / 10)
    {
        itoa(num/10,s,i);
        s[(*i)++] = num % 10 + '0';
    }
    else
    {
        s[(*i)++] = num % 10 + '0';
    }
}

void i_toa(int num,char* s)
{
    int i = 0;

    itoa(num,s,&i);

    s[i] = '\0';

}

void appendStr(char** dest,const char* src)
{
    if(*dest == NULL)
    {
        int len = strlen(src);

        *dest = malloc(len + 1);

        strcpy(*dest,src);
    }
    else 
    {
        size_t len = strlen(src) + strlen(*dest) + 1;

        char* temp = realloc(*dest,len);

        *dest = temp;

        strcat(*dest,src);
    }
}

static void ftoa(int num,char* s,int* i,int p)
{
    if(num < 0)
    {
        s[(*i)++] = '-';
        num = -num;
    }

    

    if(num / 10)
    {
        
        ftoa(num/10,s,i,p);
        if(*i == p)
        {
            s[(*i)++] = '.';
        }
        s[(*i)++] = num % 10 + '0';
    }
    else
    {
        s[(*i)++] = num % 10 + '0';
    }
}

void f_toa(float num,char* s)
{
    float temp = num;
    int i;

    if(num < 0) num = -num;

    for(i = 0;num > 1.0f;num /= 10,i++)
    {
        //printf("%f\n",num);
    }
    
    int value = num * power(10,i+1);

    //printf("count %d\n",i);
    //printf("%d\n",value);

    int j = 0;
    ftoa(value,s,&j,i);

    s[j] = '\0';

}

int getRandom(int upper,int lower)
{
    return rand() % (upper - lower + 1) + lower;
}

int power(int num,int n)
{
    int base = num;

    while(n > 1)
    {
        base *= num;
        n--;
    }

    return base;
}
