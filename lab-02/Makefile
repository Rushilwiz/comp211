SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -Werror -g
DIFF_FLAGS=--ignore-blank-lines

all: signed twos negate2s f32

test: test_signed test_twos test_negate2s test_f32

signed: signed.c
	$(CC) $(CFLAGS) signed.c -o signed

twos: twos.c
	$(CC) $(CFLAGS) twos.c -o twos

negate2s: negate2s.c
	$(CC) $(CFLAGS) negate2s.c -o negate2s

f32: f32.c
# -lm is necessary if using `pow` from <math.h>, as mentioned in README
	$(CC) $(CFLAGS) f32.c -lm -o f32

test_signed: signed
	diff $(DIFF_FLAGS) <(echo 0000000011010011) <(./signed +211)
	diff $(DIFF_FLAGS) <(echo 1000000011010011) <(./signed -211)
	diff $(DIFF_FLAGS) <(echo not possible) <(./signed +100000)
	diff $(DIFF_FLAGS) <(echo 0000000000000000) <(./signed +0)
# You probably have to hardcode for this case because atoi("-0") is just 0
	diff $(DIFF_FLAGS) <(echo 1000000000000000) <(./signed -0)

test_twos: twos
	diff $(DIFF_FLAGS) <(echo 0000000011010011) <(./twos +211)
	diff $(DIFF_FLAGS) <(echo 1111111100101101) <(./twos -211)
	diff $(DIFF_FLAGS) <(echo not possible) <(./twos +100000)

test_negate2s: negate2s
	diff $(DIFF_FLAGS) <(echo 11111111111111111111111100101101) <(./negate2s 00000000000000000000000011010011)

test_f32: f32
	diff $(DIFF_FLAGS) <(echo 1.0000) <(./f32 00111111100000000000000000000000)
	diff $(DIFF_FLAGS) <(echo -1.0000) <(./f32 10111111100000000000000000000000)
	diff $(DIFF_FLAGS) <(echo 0.1375) <(./f32 00111110000011001100110011001101)

clean:
# Without 2> /dev/null, if these files didn't exist, rm would print "cannot remove... No such file..." to stderr
# 2> /dev/null redirects stderr (file descriptor 2) to /dev/null
# /dev/null is a place for junk, and it discards anything written to it
# || true makes the return code 0 unconditionally (even if the files don't exist so rm returns 1)
	rm signed twos negate2s f32 2> /dev/null || true
