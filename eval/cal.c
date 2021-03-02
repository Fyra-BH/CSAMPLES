#include "cal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//表达式求值
int calculate(char *exp)
{
    deal_with_brackets(exp);
    add_prefix(exp);
    rm_space(exp);
    stack_t *st_num = stack_init(MAX_STACK_DEPTH);
    stack_t *st_op = stack_init(MAX_STACK_DEPTH);
    int offset = 0;
    while (1)
    { 
        if(offset >= strlen(exp))break;

        if(isdigit(exp[offset]))
        {
            int n = cut_num(exp,&offset);
            push(st_num,n);
        }else
        {
            int key = exp[offset];
            if (key == '(' || is_empty(st_op))
            {
                push(st_op,key);
            }else if(key == '+' || key == '-')
            {
                while (!is_empty(st_op) && *(st_op->top) != '(')
                {
                    int n = pop(st_num);
                    push(st_num,compute(pop(st_num),n,pop(st_op)));
                }
                push(st_op,key);
                
            }else if(key == '*' || key == '/')
            {
                while (!is_empty(st_op)&&(*(st_op->top) == '*')||(*(st_op->top) == '/'))
                {
                    int n = pop(st_num);
                    push(st_num,compute(pop(st_num),n,(char)pop(st_op)));
                }
                push(st_op,key);
            }else if(key==')')
                {
                    while(!is_empty(st_op)&&*(st_op->top)!='(')
                    {
                        int n = pop(st_num);
                        push(st_num,compute(pop(st_num),n,(char)pop(st_op)));
                    }
                    pop(st_op);
                }
                offset ++;
        }
    }
    int ans = pop(st_num);
    while (!is_empty(st_op))
    {
        if(*(st_op->top)=='('||*(st_op->top)==')')pop(st_op);
        else ans = compute(pop(st_num),ans,pop(st_op));
    }
    stack_destroy(st_num);
    stack_destroy(st_op);
    // printf("%d\n",ans);
    return ans;
    
}


//处理括号
int deal_with_brackets(char *exp)
{
    int index_l = -1;
    int index_r = -1;
    int cnt_l = 0;
    int cnt_r = 0;
    for (int i = 0; i < strlen(exp); i++)
    {
        char key = exp[i];
        if(key == '{'||key == '[')key = '(';
        else if(key == '}'||key == ']')key = ')';
        if (key == '(')
        {
            if(index_l == -1 )index_l = i;
            cnt_l ++;
        }else if (key == ')')
        {
            if(index_r == -1 )index_r = i;
            cnt_r ++;
        }
        exp[i] = key;
    }
    if(index_l > index_r || cnt_l != cnt_r)return 1;
    return 0;
}
//负号前添加0
int add_prefix(char *exp)
{
    char falg_num = 0;
    int len = strlen(exp);
    int index = -1;
    for (int i = 0; i < len; i++)
    {
        if(exp[i] == '-')
        {
            if (i == 0) index = 0;
            else if(!isdigit(exp[i - 1])&&exp[i - 1] != ')')
            {
                index = i;
                break;
            }
        }
    }
    if (index != -1)
    {
        for (int  i = 0; i < len-index; i++)
        {
            exp[len - i] = exp[len - i - 1];
        }
    }
    exp[index] = '0';
    if(index != -1)add_prefix(exp);//递归
}
//消除空格
int rm_space(char *exp)
{
    int len = strlen(exp);
    int index = -1;
    for (int i = 0; i < len; i++)
    {
        if(exp[i] == ' ')
        {
            index = i;
            break;
        }
    }
    if(index == -1)return 0;
    for (int i = index; i < len - 1; i++)
    {
        exp[i] = exp[i+1];
    }
    exp[len - 1] = '\0';
    rm_space(exp);//递归
}
//初始化栈
stack_t *stack_init(int len)
{
    stack_t *sp = (stack_t *)malloc(sizeof(stack_t));
    sp->height = len;
    sp->top = sp->bottom = malloc(len * sizeof(int));
    return sp;
}
//销毁栈
stack_t stack_destroy(stack_t *sp)
{
    free(sp->bottom);
    free(sp);
}

int is_empty(stack_t *sp)
{
    return sp->bottom == sp->top;
}
int is_full(stack_t *sp)
{
    return sp->height ==(sp->top - sp->bottom);
}
void push(stack_t *sp , int n)
{
    if (IS_OP(n))printf("push %c\n",(char)n);
    else  printf("push %d\n",n);
    if(!is_full(sp))
    {
        *(++(sp->top)) = n;
    }
}
int pop(stack_t *sp)
{
    if(!is_empty(sp))
    {
        int res = *(sp->top--);
        if (IS_OP(res))printf("pop %c\n",(char)res);
        else  printf("pop %d\n",res);
        return res;
    }
}

//说明：从exp表达式的offset处开始，剪取一个数字,修改结束处的索引
int cut_num(char *exp, int *offset)
{
    int res = 0;
    if(!isdigit(exp[*offset]))return 0;//非法
    else{
        res= atoi(exp + *offset);
        *offset += len_of_int(res);
    }
    return res;
}
//返回int的位数
int len_of_int(int n)
{
    int res = 1;
    while (n/=10)res+=1;
    return res;
}
//简单表达式求值
int compute(int a, int b, char st_op)
{
    switch (st_op)
    {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
        default:break;
    }
}