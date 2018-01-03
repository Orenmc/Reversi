# Snir Hazan
# ID: 308045137
# Oren Cohen
# ID: 305164295

a.out: compileAll
	g++ *.o 
#	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c -g src/*.cpp

run:
	./a.out
