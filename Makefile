polynomial : PolynomialADT.o polynomialMain.o
	gcc -o polynomial polynomialMain.o PolynomialADT.o

polynomialMain.o : polynomialMain.c
	gcc -c polynomialMain.c

PolynomialADT.o : PolynomialADT.c PolynomialADT.h
	gcc -c PolynomialADT.c

clean :
	rm polynomial polynomialMain.o PolynomialADT.o