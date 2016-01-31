IDIR=./include
CFLAGS=-Wall -g -I$(IDIR)
CC=cc

sorting: ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o
	$(CC) -o ./testSort ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o $(CFLAGS)

counting: ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o
	$(CC) -o ./testCount ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o $(CFLAGS)
