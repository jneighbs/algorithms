IDIR=./include
CFLAGS=-Wall -g -std=c99 -I$(IDIR) #-Ofast
CC=cc

# TODO: create a 'make clean' rule
# TODO: improve current rules. Just do some research

sorting: ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o
	$(CC) -o ./testSort ./sorting/testSort.o ./sorting/sort.o ./utilities/utilities.o $(CFLAGS)

counting: ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o
	$(CC) -o ./testCount ./counting/testCount.o ./counting/sortAndCountInversions.o ./utilities/utilities.o $(CFLAGS)

selecting: ./selecting/testSelect.o ./selecting/select.o ./utilities/utilities.o
	$(CC) -o ./testSelect ./selecting/testSelect.o ./selecting/select.o ./utilities/utilities.o $(CFLAGS)

graphs: ./graphs/testGraphs.o ./graphs/graph.o ./utilities/utilities.o
	$(CC) -o ./testGraphs ./graphs/testGraphs.o ./graphs/graph.o ./utilities/utilities.o $(CFLAGS)
