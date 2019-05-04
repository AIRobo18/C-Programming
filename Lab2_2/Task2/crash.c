#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct name
{
    char *first, *last;
} NAME;

typedef NAME        *NAME_PTR;

void get_name(NAME_PTR);

int main(void)
{
    NAME_PTR me;
    me = malloc(sizeof(NAME));
    me->first = malloc(sizeof(char));
    me->last = malloc(sizeof(char));
    get_name(me);
    printf("Hello %s %s!\n", me->first, me->last);
    free(me);
    free(me->first);
    free(me->last);
}

void get_name(NAME_PTR ptr)
{
    printf("What's your first name?\n");
    scanf("%s", ptr->first);
    printf("What's your last name?\n");
    scanf("%s", ptr->last);
}
