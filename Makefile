all: server client tclient mserver tserver sserver pserver eserver 

server: server.c
	gcc server.c -o server

client: client.c 
	gcc client.c -o client

tclient: tclient.c
	gcc tclient.c -o tclient -lpthread

mserver: fork_server.c
	gcc fork_server.c -o mserver

tserver: tserver.c
	gcc tserver.c -o tserver -lpthread

sserver: select_server.c
	gcc select_server.c -o sserver

pserver: poll_server.c
	gcc poll_server.c -o pserver

eserver: epoll_server.c
	gcc epoll_server.c -o eserver

clean: 
	rm server client tclient mserver tserver sserver pserver eserver 

