#make file :
CXX=cc
all:	client server
	$(CXX) -o client client.c	
	$(CXX) -o server server.c
clean:
	rm server client


