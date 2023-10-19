
output: main.o header1.o header2.o
	g++ main.o header1.o header2.o -o output

main.o: main.cpp
	g++ -c main.cpp

header1.o: header1.cpp header1.h
	g++ -c header1.cpp

header2.o: header2.cpp header2.h
	g++ -c header2.cpp

run:
	./output

clean:
	rm *.o
	rm *.png
	rm *.exe
	rm *.graphviz