#include <stdio.h>
#include <stdlib.h>
#include "PolynomialADT.h"

void printPolynomial(PolyPtr head)
{
    PolyPtr p = head;
    while(p != NULL)
    {
        printf("%.1lf %d\n", p->factor, p->power);
        p = p->next;
    }
}

PolyPtr inputPolynomial()
{
    PolyPtr p, head;
    double factor;
    printf("\n");
    scanf("%lf", &factor);
    if(factor == 0) return NULL;
    p = (PolyPtr)malloc(sizeof(struct polynomial));
    p->factor = factor;
    scanf("%d%lf", &p->power, &factor);
    head = p;
    while(factor != 0)
    {
        p->next = (PolyPtr)malloc(sizeof(struct polynomial));
        p = p->next;
        p->factor = factor;
        scanf("%d%lf", &p->power, &factor);
    }
    p->next = NULL;
    return head;
}

PolyPtr sortPolynomial(PolyPtr head)
{
    PolyPtr p, p1, p2;
    if(head == NULL)return NULL;
    p1 = head->next;
    head->next = NULL;
    if(p1 == NULL)return head;

    while(p1 != NULL)
    {
        p2 = p1->next;
        if(head->power == p1->power)
        {
            head->factor += p1->factor;
            free(p1);
            p1 = p2;
            continue;
        }
        if(head->power > p1->power)
        {
            p1->next = head;
            head = p1;
            p1 = p2;
            continue;
        }
        p = head;
        while(p->next != NULL && p->next->power < p1->power)
            p = p->next;
        if(p->next == NULL || p->next->power > p1->power)
        {
            p1->next = p->next;
            p->next = p1;
        }
        else
        {
            p->next->factor += p1->factor;
            free(p1);
        }
        p1 = p2;
    }

    return head;
}

PolyPtr addPoly(PolyPtr poly1, PolyPtr poly2)
{
    printf("Pretend to add\n");
    return NULL;
}

PolyPtr subPoly(PolyPtr poly1, PolyPtr poly2)
{
    printf("Pretend to sub\n");
    return NULL;
}
PolyPtr mulPoly(PolyPtr poly1, PolyPtr poly2)
{
    printf("Pretend to mul\n");
    return NULL;
}


