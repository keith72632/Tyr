tyr: main.c 
	gcc -o tyr main.c port_scanner.c console.c banner.c server.c packet_sniffer.c tcp_packet_sniffer.c log_search.c ping.c port_scanner.h packet_sniffer.h tcp_packet_sniffer.h server.h log_search.h console.h colors.h ping.h -Wall
clean:
	rm -rf tyr
	rm -rf backup_log.txt
	rm -rf tcp_backup_log.txt
	rm -rf server_logs.txt
	mv tcp_log.txt tcp_backup_log.txt
	mv log.txt backup_log.txt
run:
	sudo ./tyr
