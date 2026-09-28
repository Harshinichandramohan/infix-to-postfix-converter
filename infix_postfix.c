#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char value)
{
    stack[++top] = value;
}

char pop()
{
    return stack[top--];
}

char peek()
{
    return stack[top];
}

int isEmpty()
{
    return top == -1;
}

int precedence(char operator)
{
    if (operator == '^')
        return 3;

    if (operator == '*' || operator == '/' || operator == '%')
        return 2;

    if (operator == '+' || operator == '-')
        return 1;

    return 0;
}

int isOperator(char character)
{
    return character == '+' ||
           character == '-' ||
           character == '*' ||
           character == '/' ||
           character == '%' ||
           character == '^';
}

void infixToPostfix(char infix[], char postfix[])
{
    int i = 0;
    int j = 0;
    char character;

    while (infix[i] != '\0')
    {
        character = infix[i];

        // If operand, add to postfix
        if (isalnum(character))
        {
            postfix[j++] = character;
        }

        // If opening bracket, push into stack
        else if (character == '(')
        {
            push(character);
        }

        // If closing bracket
        else if (character == ')')
        {
            while (!isEmpty() && peek() != '(')
            {
                postfix[j++] = pop();
            }

            if (!isEmpty() && peek() == '(')
            {
                pop();
            }
        }

        // If operator
        else if (isOperator(character))
        {
            while (!isEmpty() &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(character))
            {
                postfix[j++] = pop();
            }

            push(character);
        }

        i++;
    }

    // Pop remaining operators
    while (!isEmpty())
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[MAX];
    char postfix[MAX];

    printf("=====================================\n");
    printf("   INFIX TO POSTFIX CONVERTER\n");
    printf("=====================================\n\n");

    printf("PSEUDOCODE:\n\n");

    printf("1. Read infix expression\n");
    printf("2. Initialize empty stack\n");
    printf("3. Scan expression from left to right\n");
    printf("4. If operand, add to postfix\n");
    printf("5. If '(', push into stack\n");
    printf("6. If ')', pop until '('\n");
    printf("7. If operator, check precedence\n");
    printf("8. Push operator into stack\n");
    printf("9. Pop remaining operators\n");
    printf("10. Display postfix expression\n\n");

    printf("-------------------------------------\n");

    printf("Enter an infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression  : %s", infix);
    printf("\nPostfix Expression: %s\n", postfix);

    printf("-------------------------------------\n");

    return 0;
}