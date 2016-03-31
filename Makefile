IDIR=./include
CFLAGS=-Wall -g -I$(IDIR)
CC=cc

# TODO: create a 'make clean' rule
# TODO: improve current rules. Just do some research

sorting: ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o
	$(CC) -o ./testSort ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o $(CFLAGS)

counting: ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o
	$(CC) -o ./testCount ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o $(CFLAGS)
