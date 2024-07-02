flightdata: main.c sort.c
	gcc -o flightdata.exe main.c sort.c

clean:
	rm -f flightdata.exe *.txt
