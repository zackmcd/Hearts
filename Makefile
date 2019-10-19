hearts.out : main.o card.o deck.o player.o cpu.o scoreboard.o trick.o 
	g++ -o hearts.out main.o card.o deck.o player.o cpu.o scoreboard.o trick.o

main.o : main.cpp card.h deck.h player.h cpu.h scoreboard.h trick.h
	g++ -c main.cpp

trick.o : trick.cpp trick.h card.h scoreboard.h
	g++ -c trick.cpp

scoreboard.o : scoreboard.cpp scoreboard.h player.h cpu.h
	g++ -c scoreboard.cpp

cpu.o : cpu.cpp cpu.h card.h
	g++ -c cpu.cpp

player.o : player.cpp player.h card.h
	g++ -c player.cpp

deck.o : deck.cpp deck.h card.h
	g++ -c deck.cpp

card.o : card.cpp card.h
	g++ -c card.cpp

clean :
	rm -f hearts.out main.o card.o deck.o player.o cpu.o scoreboard.o trick.o
