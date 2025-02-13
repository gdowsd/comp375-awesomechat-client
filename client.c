/*
 * client.c
 *
 * Authors:
 *  1) Gabby Dow (gdow@sandiego.edu)
 *  2) Natalia Orlof-Carson (norlofcarson@sandiego.edu)
 *  3) Dr. Sat Garcia (sat@sandiego.edu)
 *
 * 	USD COMP 375: Computer Networks
 * 	Mini Project #1
 *
 * This is the client that will talk to the chat server.
 *
 * Clients can do one of the following:
 * 	- Introduce themself (MYNAMEIS foo)
 * 	- List current users (LIST)
 * 	- Send a message to another user (SENDTO bar : hello world)
 * 	- Get messages (GET)
 *
 */

#define _XOPEN_SOURCE 600

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define BUFF_SIZE 1024

/**
 * Type that represents the possible actions that a user could select while running
 * the program.
 */
typedef enum UserAction {
	LIST = 1,
	SEND = 2,
	PRINT = 3,
	QUIT = 4,
	INVALID
} UserAction;

// C's a bit weird: we need to declare (or define) functions before we use
// them, unlike modern languages (e.g. Python) where it doesn't matter what
// order you define your functions/classes.
UserAction get_user_selection();
int connect_to_host(char *hostname, char* port);
void get_user_list(int socket_fd);
void send_message(int socket_fd);
void print_messages(int socket_fd);
void set_username(int socket_fd);


int main() {
	printf("Welcome to the AwesomeChat: The COMP375 chat server.\n\n\n");

	// TODO: connect to hopper.sandiego.edu on port 7099 by calling the
	// connect_to_host function. Note that the second parameter should be a
	// string (e.g. "7099", not an integer (i.e. 7099).
	int server_socket = 0; // replace 0 with a call to connect_to_host

	set_username(server_socket);

	// Connect to server until ctl-c and return sensor reading or error message
	while (true) {
		UserAction selection = get_user_selection();

		switch (selection) {
			case LIST:
				get_user_list(server_socket);
				break;

			case SEND:
				send_message(server_socket);
				break;

			case PRINT:
				print_messages(server_socket);
				break;

			case QUIT:
				printf("Thanks for using AwesomeChat!\n");

				// TODO: close the connection using the close function

				exit(0);
				break;

			default:
				printf("\n*** Invalid selection.\n\n");
				break;
		}
	}

	// Should never get to this point so return 1 for "error"

	// TODO: close the connection
	return 1;
}

/**
 * Uses the MYNAME command to set the username.
 * 
 * @param socket_fd The socket used to communicate with the chat server.
 */
void set_username(int socket_fd) {
	printf("Please enter a username: ");

	// mynameis_message will be the array we use to send and receive data to/from the
	// server
	char mynameis_message[BUFF_SIZE];
	memset(mynameis_message, 0, BUFF_SIZE); // this makes every character '\0', i.e. NUL

	// Start by sending username request to server
	strcpy(mynameis_message, "MYNAMEIS ");

	char username[100];
	memset(username, 0, 100);

	// TODO: use fgets() to store user entered name in username. Check the
	// use of fgets in the get_user_selection function later in this file and/or review
	// the fgets manual (i.e. "man fgets") to find the number and type of
	// parameters needed when calling this function.

	strcat(mynameis_message, username); // append username to end of mynameis_message

	// TODO: send the message in mynameis_message using send() function (Beej's Guide,
	// Section 5.7 talks about send()).
	// TODO (later): error check send result

	char response[BUFF_SIZE];
	memset(response, 0, BUFF_SIZE); // this makes every character '\0', i.e. NUL

	// TODO: receive response from server for MYNAMEIS command
	// Use recv() to store the message in the response array (again, see Beej's Guide,
	// Section 5.7).

	// TODO (later): error check recv() result

	// TODO: Use the strstr function to see if response starts with "BAD"
}

/**
 * Uses the LIST command to get and print the list of users that are currently online.
 * 
 * @param socket_fd The socket used to communicate with the chat server.
 */
void get_user_list(int socket_fd) {
	// Send request to server for a list of users
	// TODO: send LIST request

	// TODO: receive and handle server response to LIST
}

/**
 * Uses the SENDTO command to send a message to another user.
 * 
 * @param socket_fd The socket used to communicate with the chat server.
 */
void send_message(int socket_fd) {
	

	char sendto_message[BUFF_SIZE];
	memset(sendto_message, 0, BUFF_SIZE);

	char receipient_name[100];
	memset(receipient_name, 0, 100);

	strcpy(sendto_message, "SENDTO ");

	printf("Enter username of recipient: ");
	// TODO: use fgets to read user input into receipient_name

	// TODO: use strcat to append receipient_name to sendto_message

	// TODO: use strcat to append " : " to sendto_message

	// prompt user for message
	char message_body[BUFF_SIZE];
	memset(message_body, 0, BUFF_SIZE);

	printf("Enter the message to send: ");

	// use fgets to read input into message_body
	fgets(message_body, BUFF_SIZE, stdin);

	// TODO: use strcat to append message_body to sendto_message

	// TODO: send the completed SENDTO request (stored in sendto_message)

	memset(sendto_message, 0, BUFF_SIZE);

	// TODO: receive and handle server response
	// Make sure it doesn't start with "BAD"

	printf("Message sent\n");
}

/**
 * Uses the GET command to get and print our messages.
 * 
 * @note This is a destructive action, meaning that it not only gets the messages from the server
 * but also deletes them so future requests for messages don't return the same messages.
 * 
 * @param socket_fd The socket used to communicate with the chat server.
 */
void print_messages(int socket_fd) {
	char get_message[BUFF_SIZE];
	memset(get_message, 0, BUFF_SIZE);

	// TODO: send the GET message

	
	char response[BUFF_SIZE];
	memset(response, 0, BUFF_SIZE);

	// TODO: receive and process server response

	// In response to a GET, the server will send each message on
	// its own line. Often this will require only a single recv,
	// but be safe, you should continually call recv until you
	// get "DONE\n" as part of the message.

	// You can use the strstr function to check whether one string
	// (e.g. "DONE\n") is contained within another one (i.e. the
	// full buffer).
}

/* 
 * Print command prompt to user and obtain user input.
 *
 * @return The user's desired selection.
 */
UserAction get_user_selection() {
	printf("What would you like to do?\n\n");
	printf("\t(1) Print list of users that are currently online.\n");
	printf("\t(2) Send a message to another user.\n");
	printf("\t(3) Print your messages.\n");
	printf("\t(4) Quit Program\n\n");
	printf("Selection: ");

	char input[10];
	memset(input, 0, 10); // set all characters in input to '\0' (i.e. NUL)
	fgets(input, 10, stdin); // get input from the standard (command line) input

	// get rid of newline, if there is one
	char *new_line = strchr(input, '\n');
	if (new_line) new_line[0] = '\0';

	// convert string to a long int
	char *end;
	long sensor = strtol(input, &end, 10);

	if (end == input || *end != '\0') {
		// the user entered something other than an integer
		return INVALID;
	}

	if (sensor < 0 || sensor > 4) {
		return INVALID;
	}
	else {
		return sensor;
	}
}

/*
 * Socket implementation of connecting to a host at a specific port.
 *
 * @param hostname The name of the host to connect to (e.g. "foo.sandiego.edu")
 * @param port The port number to connect to
 * @return File descriptor of new socket to use.
 */
int connect_to_host(char *hostname, char *port) {
	// Step 1: fill in the address info in preparation for setting up the socket.
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	// Get ready to connect to the hostname and port given as parameters to
	// this (i.e. connect_to_host) function.
	status = getaddrinfo(hostname, port, &hints, &servinfo);

	// Step 2: Make a call to socket() to create a socket.

	int fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	// make a call to connect
	connect(fd, servinfo->ai_addr, servinfo->ai_addrlen);
	// free memory that was allocated by getaddrinfo
	freeaddrinfo(servinfo);

	// return the file descriptor for the socket
	return fd;
}
