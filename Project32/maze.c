#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 10
#define MAX_STACK_SIZE 100

typedef struct {
    short r;
    short c;
} struct_element;

typedef struct {
    struct_element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s)
{
    s->top = -1;
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, struct_element item)
{
    if (is_full(s)) {
        fprintf(stderr, "Stack overflow error\n");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

struct_element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow error\n");
        exit(1);
    }
    else {
        return s->data[(s->top)--];
    }
}

struct_element here = { 1,0 };
struct_element entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1','1','1','1','1'},
    {'e','1','0','1','0','0','0','1','0','1'},
    {'0','0','0','1','0','0','0','1','0','1'},
    {'0','1','0','0','0','1','1','0','0','1'},
    {'1','0','0','0','1','0','0','0','0','1'},
    {'1','0','0','0','1','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','0','1','1'},
    {'1','0','1','1','1','0','1','1','0','1'},
    {'1','1','0','0','0','0','0','0','0','x'},
    {'1','1','1','1','1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c)
{
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        struct_element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

void print_path(StackType* s)
{
    int i;
    printf("Path: ");
    for (i = 0; i <= s->top; i++) {
        printf("(%d,%d) ", s->data[i].c, s->data[i].r);
    }
    printf("\n");
}

int main(void)
{
    int r = 0;
    int c = 0;
    StackType s;
    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);

        if (is_empty(&s)) {
            printf("실패\n");
            return 1;
        }
        else
            here = pop(&s);
    }
    printf("성공\n");
    return 0;
}
