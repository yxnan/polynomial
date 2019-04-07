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
    scanf("%lf", &factor);
    if(factor == 0) return NULL;
    p = newPolynomial();
    p->factor = factor;
    scanf("%d%lf", &p->power, &factor);
    head = p;
    while(factor != 0)
    {
        p->next = newPolynomial();
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
    PolyPtr head,list=NULL,ptr;
    list = newPolynomial();
    head=list;
    if(poly1 == NULL || poly2 == NULL) return NULL;
    while(poly1 != NULL && poly2 != NULL)
    {
        if(poly1->power > poly2->power){

            list->power = poly1->power;
            list->factor = poly1->factor;
            list=list->next;
            poly1=poly1->next;
        }
        else if(poly1->power < poly2->power){

            list->power = poly2->power;
            list->factor = poly2->factor;
            list=list->next;
            poly2=poly2->next;
        }
        else{
            if(poly1->factor + poly2->factor)
                {
                    list->power = poly1->power;
                    list->factor = poly1->factor + poly2->factor;
                    list = list->next;
                }
                poly1 = poly1->next;
                poly2 = poly2->next;
                break;
            }
    }
    for( ;poly1 != NULL;poly1 = poly1->next)
    {
        list->factor = poly1->factor;
        list->power =poly1->power;
        list = list->next;
    }
        for( ;poly2 != NULL;poly2 = poly2->next)
    {
        list->factor = poly2->factor;
        list->power =poly2->power;
        list = list->next;
    }
    list->next = NULL;
    ptr = head;
    head = head->next;
    free(ptr);
    return head;
}

PolyPtr subPoly(PolyPtr poly1, PolyPtr poly2)
{
    PolyPtr head,list=NULL,ptr;
    list = newPolynomial();
    head = list;
    if(poly1 == NULL || poly2 == NULL) return NULL;
    while(poly1 != NULL && poly2 != NULL)
    {
        if(poly1->power > poly2->power){

            list->power = poly1->power;
            list->factor = poly1->factor;
            list=list->next;
            poly1=poly1->next;
        }
        else if(poly1->power < poly2->power){

            list->power = poly2->power;
            list->factor = (-1) * poly2->factor;
            list=list->next;
            poly2=poly2->next;
        }
        else{
            if(poly1->factor - poly2->factor)
                {
                    list->power = poly1->power;
                    list->factor = poly1->factor - poly2->factor;
                    list = list->next;
                }
                poly1 = poly1->next;
                poly2 = poly2->next;
                break;
            }
    }
    for( ;poly1 != NULL;poly1 = poly1->next)
    {
        list->factor = poly1->factor;
        list->power =poly1->power;
        list = list->next;
    }
        for( ;poly2 != NULL;poly2 = poly2->next)
    {
        list->factor = (-1) * poly2->factor;
        list->power =poly2->power;
        list = list->next;
    }
    list->next = NULL;
    ptr = head;
    head = head->next;
    free(ptr);
    return head;
}

PolyPtr mulPoly(PolyPtr poly1, PolyPtr poly2)
{
    PolyPtr head,list,add,ptr;
    list = newPolynomial();
    add = newPolynomial();
    head = list;
    ptr = poly2;
    if(poly1 == NULL || poly2 == NULL) return NULL;
    while(poly1 != NULL)
    {
        for(;poly2 != NULL;poly2 = poly2->next)
        {
            list->power = poly1->power + poly2->power;
            list->factor = poly1->factor * poly2->factor;
            list = list->next;
        }
    poly2 = ptr;
    poly1 = poly1->next;
    add = addPoly(list,add);
    list = head;
    }
    return add;
}


