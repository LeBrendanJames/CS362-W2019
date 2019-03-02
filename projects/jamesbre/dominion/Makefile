CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomTest/randomtestadventurer.c dominion.h dominion_helpers.h dominion.c
	echo "Results of running random tests on the Adventurer cardEffect" >> randomtestadventurer.out
	gcc -o randomtestadventurer randomTest/randomtestadventurer.c dominion.h dominion_helpers.h dominion.c rngs.h rngs.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out 
	gcov dominion.c -b -f >> randomtestadventurer.out 
	
randomtestcard1: randomTest/randomtestcard1.c dominion.h dominion_helpers.h dominion.c
	echo "Results of running random tests on the Village cardEffect" >> randomtestcard1.out
	gcc -o randomtestcard1 randomTest/randomtestcard1.c dominion.h dominion_helpers.h dominion.c rngs.h rngs.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out 
	gcov dominion.c -b -f >> randomtestcard1.out 
	
randomtestcard2: randomTest/randomtestcard2.c dominion.h dominion_helpers.h dominion.c
	echo "Results of running random tests on the Smithy cardEffect" >> randomtestcard2.out
	gcc -o randomtestcard2 randomTest/randomtestcard2.c dominion.h dominion_helpers.h dominion.c rngs.h rngs.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out 
	gcov dominion.c -b -f >> randomtestcard2.out 

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f randomtestadventurer randomtestcard1 randomtestcard2 
