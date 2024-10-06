#include "expression.h"
#include <ctype.h>
#include <stdbool.h>

int expression(char *string){
    if(string[1] == '\0')
        return (int)(string[0] - '0');
    else if(string[0] == '-')
        return -expression(string + 1);

}

