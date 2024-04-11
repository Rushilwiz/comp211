# Do not modify! If you do, your changes will be overwritten during autograding.
CC=gcc
# -c says to not run the linker and output object files (.o)
# We manually link the object files into an executable to save time compiling
# -g includes debugging symbols for gdb
CFLAGS=-c -Wall -Werror -g
SO_FLAGS=-fPIC -shared

# Builds the test executable but does not run
all: test for_autograder

test: bit_utils.o test.o
	${CC} bit_utils.o test.o -o test

# This runs the tests
test_all: test_mask test_set test_inverse test_bit_select test_barrel_shift

test_mask: test
	./test mask

test_set: test
	./test set

test_inverse: test
	./test inverse

test_bit_select: test
	./test bit_select

test_barrel_shift: test
	./test barrel_shift

bit_utils.o: bit_utils.c bit_utils.h
	$(CC) $(CFLAGS) bit_utils.c

test.o: test.c
	$(CC) $(CFLAGS) test.c

# This will work if bit_utils.o works
for_autograder: bit_utils.o
	$(CC) $(SO_FLAGS) -o bit_utils.so bit_utils.o

clean:
	-rm -f test *.o *.so
