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
	
unittestresults: test/unittest1.c test/unittest2.c test/unittest3.c test/unittest4.c test/cardtest1.c test/cardtest2.c test/cardtest3.c test/cardtest4.c dominion.h dominion_helpers.h dominion.c
	echo "Results of running unit tests:" >> unittestresults.out
	
	gcc -c test/unittest1.c test/unittest2.c test/unittest3.c test/unittest4.c test/cardtest1.c test/cardtest2.c test/cardtest3.c test/cardtest4.c dominion.h dominion_helpers.h dominion.c rngs.h rngs.c -g $(CFLAGS)
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.o dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.o dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.o dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.o dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.o dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.o dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.o dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.o dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	
	gcov dominion.c -b -f >> unittestresults.out
	

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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.gch *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestadventurer randomtestcard1 randomtestcard2 
