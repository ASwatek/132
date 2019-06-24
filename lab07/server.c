/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * server.c - Source file with your solutions to the lab.  The
 *            main functionality for this lab should be implemented
 *            in data.c and in here.  This file is used for running the lab's
 *            program as a SERVER.
 *
 *            This is a file you need to hand in!
 *
 * This file contains code used by labs in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES:
 * Austin Swatek
 * Steven Jung
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "data.h"

/* Some constants for the servers and such */
const char*               TRACKER_ADDR    = "127.0.0.1"; /*"137.112.40.225" */
const unsigned short      TRACKER_PORT    = 22222;
const unsigned short      SERVER_PORT     = 20000;


/**
 * Remotely lists the database.
 * Very much like do_list_database, but uses sockets.
 */
void
do_remote_list_database(int sock, struct db_entry** db)
{
  // ODO: implement this.
  // It is very similar to do_list_database, but instead of using
  // printf, you'll be sending to the socket "sock".
  //
  // Hint: use sprintf and a local string variable to construct each
  //       text line you want to send, then send it.
  int i;
  char data[512];//size??
  for(i=0; i<DB_MAX_SIZE && db[i]!=NULL; i++){
   //dbe_print(db[i], stdout);
   sprintf(data, "%s => %s\n", db[i]->name, db[i]->value);
   send(sock, data, strlen(data), 0);
  }
//  send(sock, data, strlen(data), 0);
}

/**
 * Remotely finds some matches.
 * Very much like do_find_all_matches, but uses sockets.
 *
 * @param db: a pointer to the database structure
 * @param target: a string to match in names of entries to find
 */
void
do_remote_find_all_matches(int sock, struct db_entry** db, const char* target)
{
  // ODO: implement this.
  // It is very similar to do_find_all_matches, but instead of using
  // printf, you'll be sending to the socket "sock".  The changes to
  // this function are almost identical to the changes you made for
  // do_remote_list_database.
  //
  // Hint: use sprintf and a local string variable to construct each
  //       text line you want to send, then send it.
  int index=0;
  int initial = db_find_one(db, target, index);
  char data[256];
  while(initial!=-1){
   sprintf(data, "%s => %s\n", db[index]->name, db[index]->value);
   send(sock, data, strlen(data), 0);
   initial = db_find_one(db, target, index+1);
   index = initial;
//   initial = db_find_one(db, target, index+1);
  }
}


/**
 * Runloop that accepts commands from a client socket and responds with
 * results.
 *
 * Commands to implement:
 *
 * q - disconnects client.
 *
 * l - lists the database entries
 *       (do_remote_list_database)
 *
 * a - adds an entry, prompting the user for name and values
 *       (do_add_entry)
 *
 * f - finds an entry, prompting user for a target and
 *       printing the first entries with a matching name.
 *       (do_remote_find_all_matches)
 *
 * r - prompts user for a target and removes the first matching
 *       entry from the database.  No effect if nothing matches.
 *       (do_remove_first_match)
 *
 * If given a command that doesn't match one in this list, print "help" to show
 * what commands are available.
 *
 * @param db: a pointer to the database structure
 * @param clientsock: the socket descriptor for a remote client
 */
void
handleRemoteInput(struct db_entry** db, int clientsock)
{
  // ODO: Implement the command/response run loop.
  // It will be very similar to the handleLocalInput() in your local.c file.
  // The main difference is that instead of getALine and printf, you'll be
  // sending and receiving to and from clientsock.
  //
  // Some hints: see the manpages for send and recv.  (They're in section 2 of the manual).
  const char* instructions = "(a)dd, (r)emove, (l)ist, (f)ind, or (q)uit\n";
  char buf[512];
  char buf2[512];
  int recvd=0;
  for( ;; ) {
//  printf("(Remote)> ");
  send(clientsock, "(Remote)> ", 10, 0);
  // read input
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd]='\0';
 // getALine(buf, 512, stdin);
  // select instruction to run based on the input
  switch(buf[0]) {
  case 'q':
  case 'x':
  return;

  case 'l': // LIST
  do_remote_list_database(clientsock, db);
  break;

  case 'a':
  // 1. prompt for the name and value (use printf) and
  // read the name and value into buffers (use getALine).
//  printf("\t name? ");
  send(clientsock, "name? ", 7, 0);
//  getALine(buf, 512, stdin);
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd-1]='\0';
  printf("%s", buf);
//  printf("\t value? ");
  send(clientsock, "value? ", 8, 0);
//  getALine(buf2, 512, stdin);
  recvd = recv(clientsock, buf2, 511, 0);
  buf2[recvd-1]='\0';
  // 2. call do_add_entry to add it to the database
  do_add_entry(db, buf, buf2);
  break;

  case 'r': // FIND and REMOVE ONE
  // prompt for the name
//  printf("\t name to remove? ");
  send(clientsock, "name to remove? ", 16, 0);
//  getALine(buf, 512, stdin);
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd-1]='\0';
  // remove the first entry that matches the name.
  do_remove_first_match(db, buf);
  break;

  case 'f': // FIND
  // ODO:
  // prompt for the name
  // find and print all the matches.
//  printf("\t name to find? ");
  send(clientsock, "name to find? ", 14, 0);
//  getALine(buf, 511, stdin);
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd-1]='\0';
  do_remote_find_all_matches(clientsock, db, buf);
  break;

/**
  case 'e': // EXPORT
  // 1. prompt for the file name
//  printf("\t file name to create? ");
  send(clientsock, "export to file?\n", 14, 0);
  // 2. read the file name into a buffer
//  getALine(buf, 512, stdin);
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd]='\0';
  // 3. run the export function you implemented.
  do_export_db(db, buf);
  break;

  case 'i': // IMPORT
  // prompt for the file name
//  printf("\t file name to read? ");
  send(clientsock, "import from file?\n", 16, 0);
//  getALine(buf, 512, stdin);
  recvd = recv(clientsock, buf, 511, 0);
  buf[recvd]='\0';
  do_import_db(db, buf);
  break;
*/

  default:
  // The instruction was not one of the above instructions.
  // Print out a help screen that explains what instructions
  // are available.
//  printf("Invalid instruction.\n");
  printf("received remote input: %s", buf);
  send(clientsock, "Invalid instructions.\n", 22, 0);
//  printf(" %s\n", instructions);
  send(clientsock, instructions, strlen(instructions)+1, 0);
//  send(clientsock, "\n", 2, 0);
  break;
    }
  }
}

void
runServer(struct db_entry** database)
{
  // In this function you'll want to open a server socket, set it up, then loop
  // forever while listening for clients and handling them one at a time.

  // The first step is to create a server socket.  For this, you must create an
  // address structure (type: struct sockaddr_in). We'll do this for you:
  int sock;       // server socket
  int clientsock; // client socket

  struct sockaddr_in serv_addr;   // local address
  struct sockaddr_in cli_addr;    // remote address

  int cli_addr_len = sizeof(struct sockaddr_in);

  // Construct local addr structure
  memset(&serv_addr, 0, sizeof(serv_addr));   //zero out
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // accept on any interface
  serv_addr.sin_port = htons(SERVER_PORT);

  // ODO: Create a socket (family is AF_INET, type is stream, and protocol
  // is TCP).  See the manpage for socket for more info.
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sock<1){
   printf("No connect\n");
   exit(1);
  }
  


  // These two lines let us rerun the server immediately after we kill it
  int optval = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));



  // ODO: bind and listen!
  // To convert a variable of type (struct sockaddr_in*) to a (struct sockaddr*)
  // you will have to typecast it.
  int result;
  result = bind(sock, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in));
  if(result<0){
   printf("No bind\n");
   exit(1);
  }

  result = listen(sock, 5);
  if(result<0){
   printf("No listen\n");
   exit(1);
  }


  // run loop
  while(1)
  {
    // ODO: accept a connection
    // It may be helpful to display the remote client's IP address after
    // accepting a connection. TO do this, you can use the address that 
    // accept puts into its sockaddr argument and convert it to a string using
    // inet_ntoa().  See the manpage for details on how to use inet_ntoa().
    unsigned int sock_addr_len = sizeof(struct sockaddr_in);
    clientsock = accept(sock, (struct sockaddr*)&cli_addr, &sock_addr_len);
    // HANDLE ONE CLIENT
    printf("Connected to client socket %d\n", clientsock);
  //  inet_ntoa(cli_addr.sin_addr);
    handleRemoteInput(database, clientsock);

    // ODO: shut down and close the client socket.
    // When handleRemoteInput() returns, the client is done interacting.
    printf("Closing connection to client %s\n", inet_ntoa(cli_addr.sin_addr));
    shutdown(clientsock, SHUT_RDWR);
    close(clientsock);
  }

  // ODO: outside the loop, the server has nothing left to do.  Close the
  // server socket.
  close(sock);
}


int
main(int argc, char** argv)
{
  // make a big, empty database in the heap
  // this is a _pointer_ to an _array_ of db_entry structs.
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));

  // zero out the memory, just in case.
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));

  runServer(db);

  // return the used memory
  free(db);

  return 0;
}
