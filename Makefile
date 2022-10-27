all: server client tclient mserver tserver sserver pserver eserver 

server: server.c
	gcc server.c -o server

client: client.c 
	gcc client.c -o client

tclient: tclient.c
	gcc tclient.c -o tclient -lpthread

mserver: mserver.c
	gcc mserver.c -o mserver

tserver: tserver.c
	gcc tserver.c -o tserver -lpthread

sserver: sserver.c
	gcc sserver.c -o sserver

pserver: pserver.c
	gcc pserver.c -o pserver

eserver: eserver.c
	gcc eserver.c -o eserver

clean: 
	rm server client tclient mserver tserver sserver pserver eserver 

