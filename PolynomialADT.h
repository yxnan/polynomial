#ifndef _POLYADT_H_
#define _POLYADT_H_

#define newPolynomial() (PolyPtr)malloc(sizeof(struct polynomial))

typedef struct polynomial* PolyPtr;

struct polynomial
{
    double  factor;
    int     powerX;
    int     powerY;
    PolyPtr next;
};

/*
 * 函数: printPolynomial
 * 用法: printPolynomial(poly);
 * ------------------------
 * 打印多项式
 */
extern void printPolynomial(PolyPtr poly, int digit);

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
extern PolyPtr inputPolynomial();

/*
 * 函数: sortPolynomial
 * 用法: sortPolynomial(poly);
     或  newPoly = sortPolynomial(poly);
 * ------------------------
 * 按降序排序 + 合并同类项
 * 原地修改，同时返回头指针
 */
extern PolyPtr sortPolynomial(PolyPtr poly);

/*
 * 函数: addPoly
 * 用法: resultPoly = addPoly(poly1, poly2);
 * ------------------------
 * 多项式加法
 * 不改变原多项式，返回新的结果多项式
 */
extern PolyPtr addPoly(PolyPtr poly1, PolyPtr poly2);

/*
 * 函数: subPoly
 * 用法: resultPoly = subPoly(poly1, poly2);
 * ------------------------
 * 多项式减法
 * 不改变原多项式，返回新的结果多项式
 */
extern PolyPtr subPoly(PolyPtr poly1, PolyPtr poly2);

/*
 * 函数: mulPoly
 * 用法: resultPoly = mulPoly(poly1, poly2);
 * ------------------------
 * 多项式乘法
 */
extern PolyPtr mulPoly(PolyPtr poly1, PolyPtr poly2);

#endif
