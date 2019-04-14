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

void    swapData            (PolyPtr node1, PolyPtr node2);
void    printPolynomial     (PolyPtr poly);
PolyPtr inputPolynomial     ();
PolyPtr sortPolynomial      (PolyPtr poly);
void    mergeDup            (PolyPtr poly);
void    bubbleSortPoly      (PolyPtr poly);
PolyPtr copyNode            (PolyPtr node);
PolyPtr addPoly             (PolyPtr poly1, PolyPtr poly2);
PolyPtr subPoly             (PolyPtr poly1, PolyPtr poly2);
PolyPtr mulPoly             (PolyPtr poly1, PolyPtr poly2);

#endif
