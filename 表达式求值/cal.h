#ifndef _CAL__H
#define _CAL__H

#define MAX_STACK_DEPTH 1000
#define IS_OP(c) ((c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='(')||(c==')'))

int calculate(char *exp);

//字符串处理
int deal_with_brackets(char *exp);
int add_prefix(char *exp);
int rm_space(char *exp);
//辅助函数
int cut_num(char *exp, int *offset);
int len_of_int(int n);
int compute(int a, int b, char op);

typedef struct stack
{
    int *top;
    int *bottom;
    int height;
}stack_t;
stack_t *stack_init(int len);
stack_t stack_destroy(stack_t *sp);
int is_empty(stack_t *sp);
int is_full(stack_t *sp);
void push(stack_t *sp , int n);
int pop(stack_t *sp);

//内存接口
void *mem_alloc(int sz);
void mem_free(void *p);

#endif

