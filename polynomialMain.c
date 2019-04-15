#include <stdio.h>
#include <stdlib.h>
#include "PolynomialADT.h"

typedef int ChoiceType;  // 菜单选项
typedef PolyPtr (*OpFuncPtr)(PolyPtr, PolyPtr);  // 函数指针，指向运算函数

#define EXIT      0
#define INPUT     1
#define ADD       2
#define SUB       3
#define MUL       4
#define OUTPUT    5
#define SET_DIGIT 6
#define UNKNOWN  -1

#ifdef linux
    #define ClearScreen() system("clear")  // 清屏宏函数
#else
    #define ClearScreen() system("cls")
#endif

void        buffClear   ();
OpFuncPtr   operate     (ChoiceType op);
ChoiceType  promptInput ();

/*
 * 函数: buffClear
 * 用法: buffClear();
 * ------------------------
 * 清空键盘缓冲区，防止干扰之后输入
 */
void buffClear()
{
    char ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

/*
 * 函数: operate
 * 用法: resultPoly = operate(choice) (poly1, poly2);
 * ------------------------
 * 根据 choice 选择不同的函数操作多项式
 * choice 可有三种：
 *      ADD --- 多项式加法
 *      SUB --- 多项式减法
 *      MUL --- 多项式乘法
 */
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

/*
 * 函数: promptInput
 * 用法: choice = promptInput();
 * ------------------------
 * 打印菜单，并返回用户选项
 */
ChoiceType promptInput()
{
    printf("\n请选择操作：\n");
    printf("--------------------------\n\n");
    printf("    1 - 多项式输入\n");
    printf("    2 - 多项式相加\n");
    printf("    3 - 多项式相减\n");
    printf("    4 - 多项式相乘\n");
    printf("    5 - 多项式输出\n");
    printf("    6 - 设置小数保留位数\n");
    printf("    0 - 退出程序\n");
    printf("--------------------------\n");

    char input;
    do {
        input = getchar();
    } while(input == '\n');

    buffClear();    // 清空缓存区

    if (input >= '0' && input <= '6')   // 检查有效操作范围
        return (ChoiceType)(input - '0');
    else
        return UNKNOWN;

}

int main()
{
    PolyPtr poly1, poly2, result;
    ChoiceType choice;
    int digit = 2;    // 默认保留两位小数

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
                printPolynomial(result, digit);
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
                poly1  = sortPolynomial(poly1); // 同次数合并，异次数按X降序
                poly2  = sortPolynomial(poly2);
                result = operate(choice) (poly1, poly2);
                printf("运算已完成.\n");
                break;
            }

            case SET_DIGIT:
            printf("请输入保留小数位数(0 ~ 5)：\n\n");
            int tmp;
            scanf("%d", &tmp);
            if (tmp >= 0 && tmp <= 5)
            {
                digit = tmp;
                printf("\n设置完成，保留 %d 位小数.\n", digit);
                break;
            }
            else
            {
                printf("\n无效范围，请重新输入.\n");
                break;
            }

            default:
            printf("无效操作，请重新选择.\n");
            break;
        }
    }
}
