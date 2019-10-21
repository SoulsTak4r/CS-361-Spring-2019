
all: server server_concurrent

server_concurrent: server.c 
	gcc  -o server_concurrent -D CONCURRENT server.c -lpthread

server: server.c 
	gcc -o server server.c -lpthread

clean: 
	rm server server_concurrent 