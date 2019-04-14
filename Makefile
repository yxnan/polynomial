# Project: polynomial
# This is for Linux

CC       = gcc
TMPDIR   = obj/
OBJ      = obj/PolynomialADT.o obj/polynomialMain.o
INCS     = -I "./"
BIN      = polynomial
CFLAGS   = $(INCS)
RM       = rm -f

.PHONY: all clean

all: $(TMPDIR) $(BIN)

clean:
	${RM} $(OBJ) $(BIN)
	${RM} -r $(TMPDIR)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

$(TMPDIR):
	mkdir $(TMPDIR)

obj/polynomialMain.o : polynomialMain.c
	$(CC) -c polynomialMain.c -o obj/polynomialMain.o $(CFLAGS)

obj/PolynomialADT.o : PolynomialADT.c PolynomialADT.h
	$(CC) -c PolynomialADT.c -o obj/PolynomialADT.o $(CFLAGS)