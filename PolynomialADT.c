#include <stdio.h>
#include <stdlib.h>
#include "PolynomialADT.h"

void printPolynomial(PolyPtr poly)
{
    if (poly->factor < 1e-6)
        printf("0");
    else
    {
        PolyPtr p = poly;
        printf("%.4lf(x^%d)(y^%d)", p->factor, p->powerX,p->powerY);
        p = p->next;

        while (p)
        {
            if (p->factor > 0) printf(" +");
            printf("%.4lf(x^%d)(y^%d)", p->factor, p->powerX,p->powerY);
            p = p->next;
        }
    }
    printf("\n");
}

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

PolyPtr inputPolynomial()
{
    double factor;
    PolyPtr head = newPolynomial();
    PolyPtr prev = head, tmp;
    head->factor = 0;
    head->next   = NULL;

    while (1)
    {
        scanf("%lf", &factor);
        if (factor == 0) return head->next;

        tmp = newPolynomial();
        tmp->factor = factor;
        scanf("%d%d", &(tmp->powerX), &(tmp->powerY));
        tmp->next = NULL;

        prev->next = tmp;
        prev = tmp;
    }
}

PolyPtr sortPolynomial(PolyPtr poly)
{
    bubbleSortPoly(poly);
    mergeDup(poly);
    return poly;
}

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
            free(prev->next);
            prev->next = cur;
        }
        else
        {
            prev = cur;
            cur  = cur->next;
        }
    }
}

void bubbleSortPoly(PolyPtr poly)
{
    PolyPtr tailNode = NULL;
    PolyPtr flagNode = NULL;

    while (flagNode != poly)
    {
        tailNode = flagNode;
        flagNode = poly;
        PolyPtr prev = poly;
        while (prev->next != tailNode)
        {
            PolyPtr cur = prev->next;
            if (prev->powerX < cur->powerX)
            {
                swapData(prev, cur);
                flagNode = cur;
            }
            else if (prev->powerX == cur->powerX)
            {
                if (prev->powerY < cur->powerY)
                {
                    swapData(prev, cur);
                    flagNode = cur;
                }
            }
            prev = prev->next;
        }
    }
}

PolyPtr copyNode(PolyPtr node)
{
    PolyPtr cp = newPolynomial();

    cp->factor = node->factor;
    cp->powerX = node->powerX;
    cp->powerY = node->powerY;
    return cp;
}

// PolyPtr addPoly             (PolyPtr poly1, PolyPtr poly2){};
// PolyPtr subPoly             (PolyPtr poly1, PolyPtr poly2){};
// PolyPtr mulPoly             (PolyPtr poly1, PolyPtr poly2){};

PolyPtr addPoly(PolyPtr poly1, PolyPtr poly2)
{
    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr tmp;

    resPoly->next = NULL;

    while (ptr1 && ptr2)
    {
        if (ptr1->powerX > ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY > ptr2->powerY))
        {
            tmp = copyNode(ptr1);
            ptr1 = ptr1->next;
        }
        else if (ptr1->powerX < ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY < ptr2->powerY))
        {
            tmp = copyNode(ptr2);
            ptr2 = ptr2->next;
        }
        else
        {
            tmp = copyNode(ptr1);
            tmp->factor += ptr2->factor;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        if (tmp->factor > 1e-6)
        {
            prev->next = tmp;
            prev = tmp;
        }
    }

    prev->next = NULL;
    return resPoly->next;
}

PolyPtr subPoly(PolyPtr poly1, PolyPtr poly2)
{

    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr tmp;

    resPoly->next = NULL;

    while (ptr1 && ptr2)
    {
        if (ptr1->powerX > ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY > ptr2->powerY))
        {
            tmp = copyNode(ptr1);
            ptr1 = ptr1->next;
        }
        else if (ptr1->powerX < ptr2->powerX
            ||(ptr1->powerX == ptr2->powerX && ptr1->powerY < ptr2->powerY))
        {
            tmp = copyNode(ptr2);
            tmp->factor = -(tmp->factor);
            ptr2 = ptr2->next;
        }
        else
        {
            tmp = copyNode(ptr1);
            tmp->factor -= ptr2->factor;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        if (tmp->factor > 1e-6)
        {
            prev->next = tmp;
            prev = tmp;
        }
    }

    prev->next = NULL;
    if (resPoly->next == NULL)
    {
        tmp->factor = 0.0;
        return tmp;
    }
    return resPoly->next;
}

PolyPtr mulPoly(PolyPtr poly1, PolyPtr poly2)
{
    if (poly1->factor < 1e-6 || poly2->factor < 1e-6)
    {
        return poly1;
    }

    PolyPtr resPoly = newPolynomial(), prev = resPoly;
    PolyPtr ptr1 = poly1, ptr2 = poly2;
    PolyPtr tmp;

    resPoly->next = NULL;

    while (ptr1 && ptr2)
    {
        tmp = copyNode(ptr1);
        tmp->factor *= ptr2->factor;
        tmp->powerX += ptr2->powerX;
        tmp->powerY += ptr2->powerY;

        ptr1 = ptr1->next;
        ptr2 = ptr2->next;

        prev->next = tmp;
        prev = tmp;
    }

    prev->next = NULL;

    sortPolynomial(resPoly->next);
    return resPoly->next;
}