# name
# id

a.out: compileAll
	g++ *.o -pthread 
	rm -f *.o

compileAll: *.h *.cpp
	g++ -c *.cpp -pthread
