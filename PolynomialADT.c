#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PolynomialADT.h"

static void    swapData       (PolyPtr node1, PolyPtr node2);
static void    mergeDup       (PolyPtr poly);
static void    bubbleSortPoly (PolyPtr poly);
static PolyPtr copyNode       (PolyPtr node);

/*
 * 函数: printPolynomial
 * 用法: printPolynomial(poly);
 * ------------------------
 * 打印多项式
 */
void printPolynomial(PolyPtr poly, int digit)
{
    if (fabs(poly->factor) < 1e-6)    // 零多项式
        printf("0");
    else
    {
        char format[30];
        sprintf(format, "%%.%dlf(x^%%d)(y^%%d) ", digit);

        PolyPtr p = poly;
        printf(format, p->factor, p->powerX,p->powerY);
        p = p->next;

        while (p)
        {
            if (p->factor > 0) printf("+");
            printf(format, p->factor, p->powerX,p->powerY);
            p = p->next;
        }
    }
    printf("\n");
}

/*
 * 函数: inputPolynomial
 * 用法: poly = inputPolynomial();
 * ------------------------
 * 从标准输入读入一个多项式，返回头指针
 * 可保证不会返回空指针
 * 输入格式：
 *      系数(double) x幂指数(int) y幂指数(int)
 *      ... (重复 N 次)
 *      0   (结束)
 */
PolyPtr inputPolynomial()
{
    double factor;
    PolyPtr head = newPolynomial();
    PolyPtr prev = head, tmp;

    head->factor = 0.0;
    head->next   = NULL;   // 舍弃头结点，从下一个结点开始存放数据

    while (1)
    {
        scanf("%lf", &factor);
        if (fabs(factor) < 1e-6)     // 输入结束
        {
            if (fabs(prev->factor) < 1e-6)  // 零多项式
                return head;
            else                      // 一般情况
                return head->next;
        }

        tmp = newPolynomial();
        tmp->factor = factor;
        scanf("%d%d", &(tmp->powerX), &(tmp->powerY));
        tmp->next = NULL;

        prev->next = tmp;
        prev = tmp;
    }
}

/*
 * 函数: sortPolynomial
 * 用法: sortPolynomial(poly);
     或  newPoly = sortPolynomial(poly);
 * ------------------------
 * 按降序排序 + 合并同类项
 * 原地修改，同时返回头指针
 */
PolyPtr sortPolynomial(PolyPtr poly)
{
    bubbleSortPoly(poly);
    mergeDup(poly);
    return poly;
}

/*
 * 函数: swapData『内部函数』
 * 用法: swapData(node1, node2);
 * ------------------------
 * 交换两个项的所有数据
 */
void swapData(PolyPtr node1, PolyPtr node2)
{
    double tmp_factor;
    int    tmp_X, tmp_Y;

    tmp_factor = node1->factor;
    tmp_X = node1->powerX;
    tmp_Y = node1->powerY;

    node1->factor = node2->factor;
    node1->powerX = node2->powerX;
    node1->powerY = node2->powerY;

    node2->factor = tmp_factor;
    node2->powerX = tmp_X;
    node2->powerY = tmp_Y;
}

/*
 * 函数: mergeDup『内部函数』
 * 用法: mergeDup(poly);
 * ------------------------
 * 合并同类项（原地修改）
 */
void mergeDup(PolyPtr poly)
{
    PolyPtr prev = poly, cur = poly->next;
    while (cur)
    {
        if (prev->powerX == cur->powerX
         && prev->powerY == cur->powerY)
        {
            prev->factor += cur->factor;
            cur = cur->next;
            free(prev->next);    // 舍弃重复项
            prev->next = cur;
        }
        else
        {
            prev = cur;
            cur  = cur->next;
        }
    }
}

/*
 * 函数: bubbleSortPoly『内部函数』
 * 用法: bubbleSortPoly(poly);
 * ------------------------
 * 改进后的冒泡排序法
 * 为多项式降序排序（原地修改）
 */
void bubbleSortPoly(PolyPtr poly)
{
    PolyPtr tailNode = NULL;
    PolyPtr flagNode = NULL;  // 标记最近一次交换的前一个位置

    while (flagNode != poly)
    {
        tailNode = flagNode;
        flagNode = poly;
        PolyPtr prev = poly;
        while (prev->next != tailNode)
        {
            PolyPtr cur = prev->next;
            if (prev->powerX < cur->powerX)  // 按 x 降序
            {
                swapData(prev, cur);
                flagNode = cur;
            }
            else if (prev->powerX == cur->powerX)
            {
                if (prev->powerY < cur->powerY)  // x 相同，则按 y 降序
                {
                    swapData(prev, cur);
                    flagNode = cur;
                }
            }
            prev = prev->next;
        }
    }
}

/*
 * 函数: copyNode『内部函数』
 * 用法: newNode = copyNode(node);
 * ------------------------
 * 返回一个与 node 数据相同的多项式项
 */
PolyPtr copyNode(PolyPtr node)
{
    PolyPtr cp = newPolynomial();

    cp->factor = node->factor;
    cp->powerX = node->powerX;
    cp->powerY = node->powerY;
    return cp;
}

/*
 * 函数: addPoly
 * 用法: resultPoly = addPoly(poly1, poly2);
 * ------------------------
 * 多项式加法
 * 不改变原多项式，返回新的结果多项式
 */
PolyPtr addPoly(PolyPtr poly1, PolyPtr poly2)
{
    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr cur;

    resPoly->factor = 0.0;      // 一般情况下，舍弃头结点
    resPoly->next   = NULL;     // 结果为零多项式时才返回头结点

    while (ptr1 && ptr2)
    {
        if (ptr1->powerX > ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY > ptr2->powerY))
        {
            cur = copyNode(ptr1);
            ptr1 = ptr1->next;
        }
        else if (ptr1->powerX < ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY < ptr2->powerY))
        {
            cur = copyNode(ptr2);
            ptr2 = ptr2->next;
        }
        else  // x 和 y 次数相同，直接相加
        {
            cur = copyNode(ptr1);
            cur->factor += ptr2->factor;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        if (fabs(cur->factor) > 1e-6)  // 结果系数不为 0
        {
            prev->next = cur;
            prev = cur;
        }
    }


    ptr1 = (ptr1 == NULL)? ptr2:ptr1;
    while (ptr1)                    // 剩下部分直接连到尾端
    {
        cur = copyNode(ptr1);
        ptr1 = ptr1->next;
        prev->next = cur;
        prev = cur;
    }

    prev->next = NULL;
    if (fabs(prev->factor) < 1e-6)  // 结果为零多项式
        return resPoly;
    else                            // 一般情况
        return resPoly->next;
}

/*
 * 函数: subPoly
 * 用法: resultPoly = subPoly(poly1, poly2);
 * ------------------------
 * 多项式减法
 * 不改变原多项式，返回新的结果多项式
 */
PolyPtr subPoly(PolyPtr poly1, PolyPtr poly2)
{

    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr cur;

    resPoly->factor = 0.0;      // 一般情况下，舍弃头结点
    resPoly->next   = NULL;     // 结果为零多项式时才返回头结点

    while (ptr1 && ptr2)
    {
        if (ptr1->powerX > ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY > ptr2->powerY))
        {
            cur = copyNode(ptr1);
            ptr1 = ptr1->next;
        }
        else if (ptr1->powerX < ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY < ptr2->powerY))
        {
            cur = copyNode(ptr2);
            cur->factor = -(cur->factor);
            ptr2 = ptr2->next;
        }
        else  // x 和 y 次数相同，直接相减
        {
            cur = copyNode(ptr1);
            cur->factor -= ptr2->factor;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        if (fabs(cur->factor) > 1e-6)  // 结果系数不为 0
        {
            prev->next = cur;
            prev = cur;
        }
    }

    if (ptr1 == NULL)           // 剩下部分为减数
    {
        while (ptr2)
        {
            cur = copyNode(ptr2);
            cur->factor = -(cur->factor);
            ptr2 = ptr2->next;
            prev->next = cur;
            prev = cur;
        }
    }
    else                        // 剩下部分为被减数
    {
        while (ptr1)
        {
            cur = copyNode(ptr1);
            ptr1 = ptr1->next;
            prev->next = cur;
            prev = cur;
        }
    }

    prev->next = NULL;
    if (fabs(prev->factor) < 1e-6)  // 结果为零多项式
        return resPoly;
    else                            // 一般情况
        return resPoly->next;
}

/*
 * 函数: mulPoly
 * 用法: resultPoly = mulPoly(poly1, poly2);
 * ------------------------
 * 多项式乘法
 */
PolyPtr mulPoly(PolyPtr poly1, PolyPtr poly2)
{
    // 先判断其中一个为零多项式的情况
    if (fabs(poly1->factor) < 1e-6 || fabs(poly2->factor) < 1e-6)
        return (fabs(poly1->factor) < 1e-6)? poly1:poly2;

    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr tmp;

    resPoly->next = NULL;

    while (ptr1)     // 逐项相乘
    {
        ptr2 = poly2;
        while (ptr2)
        {
            tmp = copyNode(ptr1);
            tmp->factor *= ptr2->factor;
            tmp->powerX += ptr2->powerX;
            tmp->powerY += ptr2->powerY;

            ptr2 = ptr2->next;
            prev->next = tmp;
            prev = tmp;
        }
        ptr1 = ptr1->next;
    }

    prev->next = NULL;

    sortPolynomial(resPoly->next);
    return resPoly->next;
}