tyr: main.c 
	gcc -o tyr main.c port_scanner.c console.c banner.c port_scanner.h console.h -Wall
clean:
	rm -rf tyr