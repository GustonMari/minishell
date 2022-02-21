#include "../function.h"

int check_double_quote(char *arg, int *i)
{
    *i += 1;
    while (arg[*i])
    {
        if (arg[*i] == '\"')
            return (0);
        *i += 1;
    }
    return (1);
}

int check_simple_quote(char *arg, int *i)
{
    *i += 1;
    while (arg[*i])
    {
        if (arg[*i] == '\'')
            return (0);
        *i += 1;
    }
    return (1);
}

int check_quote(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '\'')
        {
            if(check_simple_quote(arg, &i))
                return (1);
        }
        else if (arg[i] == '\"')
        {
            if(check_double_quote(arg, &i))
                return (1);
        }
        i++;
    }
    return (0);
}

int main()
{
    char *str = "     \'echo\" \'  \"lol  \' pouet\'         ";
    printf("result = %d\n", check_quote(str));
    return (0);
}
