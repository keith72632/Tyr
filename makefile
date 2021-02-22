tyr: main.c 
	gcc -o tyr main.c port_scanner.c console.c banner.c packet_sniffer.c port_scanner.h packet_sniffer.h console.h colors.h -Wall
clean:
	rm -rf tyr