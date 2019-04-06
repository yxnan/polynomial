#ifndef _POLYADT_H_
#define _POLYADT_H_

typedef struct polynomial* PolyPtr;

struct polynomial
{
    double  factor;
    int     power;
    PolyPtr next;
};

extern inline PolyPtr newPolynomial()
{
    return (PolyPtr) malloc(sizeof(struct polynomial));
}

void    printPolynomial     (PolyPtr head);
PolyPtr inputPolynomial     ();
PolyPtr sortPolynomial      (PolyPtr head);
PolyPtr addPoly             (PolyPtr poly1, PolyPtr poly2);
PolyPtr subPoly             (PolyPtr poly1, PolyPtr poly2);
PolyPtr mulPoly             (PolyPtr poly1, PolyPtr poly2);

#endif