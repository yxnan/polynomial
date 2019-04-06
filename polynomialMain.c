#include <stdio.h>
#include <stdlib.h>
#include "PolynomialADT.h"

typedef int ChoiceType;
typedef PolyPtr (*OpFuncPtr)(PolyPtr, PolyPtr);

#define EXIT     0
#define INPUT    1
#define ADD      2
#define SUB      3
#define MUL      4
#define OUTPUT   5
#define UNKNOWN -1

#ifdef linux
    #define ClearScreen() system("clear")
#else
    #define ClearScreen() system("cls")
#endif

void        buffClear   ();
OpFuncPtr   operate     (ChoiceType op);
ChoiceType  promptInput ();

void buffClear()
{
    char ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

OpFuncPtr operate(ChoiceType op)
{
    switch (op)
    {
        case ADD:
            return &addPoly;
            break;
        case SUB:
            return &subPoly;
            break;
        case MUL:
            return &mulPoly;
            break;
        default:
            return NULL;
            break;
    }
}

ChoiceType promptInput()
{
    printf("\n请选择操作：\n");
    printf("-----------------------\n\n");
    printf("    1 - 多项式输入\n");
    printf("    2 - 多项式相加\n");
    printf("    3 - 多项式相减\n");
    printf("    4 - 多项式相乘\n");
    printf("    5 - 多项式输出\n");
    printf("    0 - 退出程序\n");
    printf("-----------------------\n");

    char input;
    do {
        input = getchar();
    } while(input == '\n');

    buffClear();    // 清空缓存区

    if (input >= '0' && input <= '5')   // 检查有效操作范围
        return (ChoiceType)(input - '0');
    else
        return UNKNOWN;

}

int main()
{
    PolyPtr poly1, poly2, result;
    ChoiceType choice;

    poly1  = NULL;
    poly2  = NULL;
    result = NULL;

    while (1)
    {
        choice = promptInput();
        ClearScreen();
        switch (choice)
        {
            case EXIT:
            exit(0);

            case INPUT:
            printf("请输入第一个多项式：\n\n");
            poly1 = inputPolynomial();
            printf("\n请输入第二个多项式：\n\n");
            poly2 = inputPolynomial();

            break;

            case OUTPUT:
            if (poly1 == NULL || poly2 == NULL)
            {
                printf("请先输入多项式！\n");
                break;
            }
            else if (result == NULL)
            {
                printf("请先对多项式进行运算！\n");
                break;
            }
            else
            {
                printf("结果多项式：\n");
                printPolynomial(result);
                break;
            }

            case ADD: case SUB: case MUL:
            if (poly1 == NULL || poly2 == NULL)
            {
                printf("请先输入多项式！\n");
                break;
            }
            else
            {
                poly1  = sortPolynomial(poly1); // 同次数合并，异次数按X升序
                poly2  = sortPolynomial(poly2);
                result = operate(choice) (poly1, poly2);
                printf("运算已完成.\n");
                break;
            }

            default:
            printf("无效操作，请重新选择.\n");
            break;
        }
    }
}
