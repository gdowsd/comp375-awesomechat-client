CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

TARGETS = chat-client
CLIENT_SRC = client.c

all: $(TARGETS)

chat-client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGETS)
