tyr: main.c 
	gcc -o tyr main.c port_scanner.c console.c banner.c packet_sniffer.c ping.c port_scanner.h packet_sniffer.h console.h colors.h ping.h -Wall
clean:
	rm -rf tyr
	rm -rf backup_log.txt
	mv log.txt backup_log.txt
run:
	sudo ./tyr