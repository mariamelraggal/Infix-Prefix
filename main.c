#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define size 100

typedef union
{
    float fData;
    char  cData;
} Item;

typedef struct
{
    Item arr[size];
    int top;
} Stack;

Stack * initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}

int isEmpty(Stack *s)
{
    if(s->top==0)
    {
        return 1;
    }
    return -1;
}

Item top(Stack *s)
{
    Item m2;
    m2=s->arr[s->top-1];
    return m2;
}

Item pop(Stack *s)
{
    Item m1;
    s->top--;
    m1=s->arr[s->top];
    return m1;
}

void push(Stack *s, Item val)
{
    //printf("\n hello 1 \n");
    s->arr[s->top]=val;
    s->top++;
}


int precidence(char b)
{

    if(b=='^')
        return 6;
    else if(b=='*' || b=='/')
        return 5;
    else if(b=='+' || b=='-')
        return 2;
    else if(b=='(' || b==')')
            return 7;
            return 0;
}
int isnumber(char * token)
{
    int i;
    int flag=0;
    for(i=0; i<strlen(token); i++)
    {
        if(isdigit(token[i]))
            flag=1;
    }
    return flag;
}


void infixToPostfix(char* infix, char* postfix)
{

    postfix[0]='\0';
    Item m;
    Stack *s=initialize();
    char* token =strtok(infix,"  ");
    while(token!=NULL)
    {
        if(isnumber(token))
        {
            strcat(postfix,token);
            strcat(postfix," ");
        }
        else
        {
            if((isEmpty(s)==1||top(s).cData=='(') && *token!=')')
            {
                m.cData=*token;
                push(s,m);
            }
            else if (*token == '(')
            {
                m.cData=*token;
                push(s, m);
            }
            else if (*token == ')')
            {
                while (top(s).cData != '(' && isEmpty(s)!=1)
                {
                    char c = (pop(s).cData);
                    strncat(postfix,&c,1);
                    strcat(postfix," ");
                }
                pop(s);
            }
            else if(precidence(*token)>precidence(top(s).cData))
            {
                m.cData=*token;
                push(s,m);

            }

            else
            {
                while(isEmpty(s)== -1 && precidence(*token)<=precidence(top(s).cData))
                {
                    char c = (pop(s).cData);
                    if(c!='(')
                    {
                        strncat(postfix, &c, 1);
                        strcat(postfix," ");
                    }

                }
                m.cData=*token;
                push(s,m);
            }
        }
        token =strtok(NULL," ");
    }
    while(isEmpty(s)==-1)
    {
        char c = (pop(s).cData);
        if(c!='(')
        {
            strncat(postfix, &c, 1);
            strcat(postfix," ");
        }


    }
    strcat(postfix,"\0"); // extra space
    free(s);

}



float evaluatePostfix(char* postfix)
{
    Stack *s1=initialize();
    float op1,op2,result;
    Item m;
    char *token=strtok(postfix," ");
    while(token!=NULL)
    {
        if (isnumber(token))
        {
            float f=atof(token);
            m.fData=f;
            push(s1,m);
        }
        // If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else
        {
            op2 = pop(s1).fData;
            op1= pop(s1).fData;
            switch (*token)
            {
            case '+':
                m.fData=op2+op1;
                push(s1,m);
                break;
            case '-':
                m.fData=op1-op2;
                push(s1,m);
                break;
            case '*':
                m.fData=op2*op1;
                push(s1,m);
                break;
            case '/':
                m.fData=op1/op2;
                push(s1,m);
                break;
            case '^':
                m.fData=pow(op1,op2);
                push(s1,m);
                break;
            }
        }
        token=strtok(NULL," ");

    }
    result=pop(s1).fData;
    if(token==NULL)
    {
        free(s1);
        return result;
    }
    else
        return -1;

}


void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}


int main(int argc,char**argv)
{
    char infixExpr[256]="";
    char postfix[256]="";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr,255,stdin)!=NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr,postfix);
        printf("Postfix: %s\n",postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %.2f\n\n",result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
