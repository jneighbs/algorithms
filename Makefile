IDIR=./include
CFLAGS=-I$(IDIR)
CC=cc

sort: ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o
	$(CC) -o ./testSort ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o $(CFLAGS)
