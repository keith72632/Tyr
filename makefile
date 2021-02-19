main: main.c 
	gcc -o main main.c port_scanner.c console.c banner.c port_scanner.h console.h -Wall
clean:
	rm -rf main