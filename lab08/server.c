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
//const char*               TRACKER_ADDR    = "127.0.0.1"; /*"137.112.40.225" */
const char*		  TRACKER_ADDR	  = "137.112.45.240";
const unsigned short      TRACKER_PORT    = 22222;
const unsigned short      SERVER_PORT     = 20000;


struct sendPrep {
  char buffer[1000];
  int  length;
};

/**
 * Appends to sendPrep buffer.
 */
void
prep(const char* toSend, int len, struct sendPrep* sp)
{
  if (sp->length + len > 1000) {
    return;
  }
  // append toSend to buffer
  strncpy(sp->buffer + sp->length, toSend, len);
  sp->length += len;
}

/**
 * Sends prepared buffer and resets it.
 */
void
send_prepared(int clientsock, struct sendPrep* sp)
{
  send(clientsock, (const void *) sp->buffer, sp->length, 0);//(const void *) to prevent warning on compile since send expects a const void*, not char*
  memset(sp->buffer, '\0', 1000);
  sp->length=0;
}

/**
 * Remotely lists the database.
 * Very much like do_list_database, but uses sockets.
 */
void
do_remote_list_database(struct db_entry** db, struct sendPrep* buffer)
{
  char strTmp[1000]; // for formatting the string
  int i;
  for (i=0; i < DB_MAX_SIZE && db[i] != NULL; i++) {
    sprintf(strTmp, "%s => %s\n", db[i]->name, db[i]->value);
    prep((void *)strTmp, strlen(strTmp), buffer);
  }
}

/**
 * Remotely finds some matches.
 * Very much like do_find_all_matches, but uses sockets.
 *
 * @param db: a pointer to the database structure
 * @param target: a string to match in names of entries to find
 */
void
do_remote_find_all_matches(struct db_entry** db,
                           const char* target,
                           struct sendPrep* buffer)
{
  char strTmp[1000]; // for formatting the string
  int i = 0;
  // while we don't go past the array end AND we find a match,
  // try to find another match.
  while(i < DB_MAX_SIZE && (i = db_find_one(db, target, i)) > -1) {
    sprintf(strTmp, "[%s]\t %ld bytes\n", db[i]->name,
                    strlen(db[i]->value) * sizeof(char));
    prep(strTmp, strlen(strTmp), buffer);
    i++;
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
 * k - shuts down server.
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
 * @returns 1 if server needs to shutdown, 0 otherwise.
 */
int
handleRemoteInput(struct db_entry** db, int clientsock)
{
  const char* instructions = " (a)dd, (r)emove, (l)ist, (f)ind (k)ill server or (q)uit";
  // begin the REPL
  char buf[512];
  char buf2[512];
  buf[0] = '\0';
  buf2[0] = '\0';

  char received_string[512];
  int received_bytes = 0;

  struct sendPrep sendBuffer;
  sendBuffer.length = 0;
  sendBuffer.buffer[0] = '\0';


  // loop forever
  for( ;; ) {
    prep("(Remote)> ", 10, &sendBuffer);
    send_prepared(clientsock, &sendBuffer);

    // read input
    received_bytes = recv(clientsock, (void *)received_string, 512, 0);
    received_string[received_bytes] = '\0';

    // do we need this?
    if (received_bytes < 1) {
      continue;
    }

    printf("received remote command: %s\n", received_string);

    // check to make sure the instruction is not a blank line
    if(strlen(received_string) < 1) {
      prep("Invalid instruction.\n", 20, &sendBuffer);
      sprintf(buf, " %s\n", instructions);
      prep(buf, strlen(buf), &sendBuffer);
      continue;
    }

    // select instruction to run
    switch(received_string[0]) {
    case 'q':
    case 'x':
      return 0;

    // "kill" to shut the server down.
    case 'k':
      send(clientsock, (const void *) "Shutting down\n", 14, 0);
      return 1;

    case 'a': // ADD
      // prompt for the name and value.
      send(clientsock, (const void *) "\t name? ", 8, 0);
      received_bytes = recv(clientsock, (void *)buf, 512, 0);
      buf[received_bytes-1] = '\0'; //chop off newline

      send(clientsock, (const void *) "\t value? ", 9, 0);
      received_bytes = recv(clientsock, (void *)buf2, 512, 0);
      buf2[received_bytes-1] = '\0'; //chop off newline

      do_add_entry(db, buf, buf2);
      break;

    case 'f': // FIND
      // prompt for the name
      send(clientsock, (const void *)"\t name to find? ", 16, 0);
      received_bytes = recv(clientsock, (void *)buf, 512, 0);
      buf[received_bytes-1] = '\0'; //chop off newline

      do_remote_find_all_matches(db, buf, &sendBuffer);
      break;

    case 'r': // FIND and REMOVE ONE
      // prompt for the name
      send(clientsock, (const void *) "\t name to remove? ", 18, 0);
      received_bytes = recv(clientsock, (void *)buf, 512, 0);
      buf[received_bytes-1] = '\0'; //chop off newline

      do_remove_first_match(db, buf);
      break;

    case 'l': // LIST
      do_remote_list_database(db, &sendBuffer);
      break;

    /* doesn't make sense for remote client, but would be easy to create:
    case 'e': // EXPORT
      // prompt for the file name
      printf("\t file name to create? ");
      getALine(buf, 512, stdin);

      do_export_db(db, buf);
      break;

    case 'i': // IMPORT
      // prompt for the file name
      printf("\t file name to read? ");
      getALine(buf, 512, stdin);

      do_import_db(db, buf);
      break;
    */

    default:
      prep("Invalid instruction.\n", 20, &sendBuffer);
      sprintf(buf, " %s\n", instructions);
      prep(buf, strlen(buf), &sendBuffer);
      continue;
    }
  }
}

void
runServer(struct db_entry** database)
{
  // open server socket
  int sock;       // server socket
  int clientsock; // client socket

  struct sockaddr_in serv_addr;   // local address
  struct sockaddr_in cli_addr;    // remote address

  int cli_addr_len = sizeof(struct sockaddr_in);

  int rv;

  // Construct local addr structure
  memset(&serv_addr, 0, sizeof(serv_addr));   //zero out
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // accept on any interface
  serv_addr.sin_port = htons(SERVER_PORT);

  sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 1) { exit(1); }

  // These two lines let us rerun the server immediately after we kill it
  int optval = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

  // bind and listen!
  if(bind(sock, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in)) < 0) {
    exit(1);
  }
  if (listen(sock, 5) < 0) { exit(1); }

  // run loop
  while(1)
  {
    // accept a connection
    unsigned int sock_addr_len;
    clientsock = accept(sock,
                        (struct sockaddr*)&cli_addr,
                        &cli_addr_len);
    getpeername(clientsock, (struct sockaddr*)&cli_addr, &sock_addr_len);
    printf("Connected to client %s\n", inet_ntoa(cli_addr.sin_addr));

    // HANDLE ONE CLIENT
    rv = handleRemoteInput(database, clientsock);

    // shut down and close the client socket.
    // When handleRemoteInput() returns, the client is done interacting.
    printf("Closing connection to client %s\n", inet_ntoa(cli_addr.sin_addr));
    shutdown(clientsock, SHUT_RDWR);
    close(clientsock);

    if (rv == 1) {
      // end server command
      break;
    }
  }

  close(sock);
}

/**
 * ODO: implement a function that sends a command to the tracker.
 * Use this for registering and unregistering your server.
 * DOCUMENT how it works in this comment block.
 *
 * Create a socket for connecting to the Tracker
 * Connect to the Tracker
 * Listen for Tracker's response
 * Send "commandLine" to Tracker
 * Listen for Tracker's response
 * The job is finished, so close the socket
 *
 * param: commandLine
 *	  the command to be sent to the Tracker
 *
 * You will copy this code into your client.c file too (and then modify it
 * there).
 */
void
sendTrackerCommand(const char* commandLine)
{
  // ODO: finish me!
  // Hint: This is where your server acts like a client.
  // 1. Create a socket
  // 2. Create an address struct (sockaddr_in)
  // USE TRACKER_ADDR and TRACKER_PORT here!
  // 3. Connect to the tracker
  // 4. Receive a prompt (and print it)
  // 5. Send a command
  // 6. Receive the result (and print it)
  // 7. Disconnect from the tracker.
//1:
  int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//2:
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(TRACKER_ADDR);
  addr.sin_port = htons(TRACKER_PORT);
//3:
  connect(sock, (struct sockaddr*) &addr, sizeof(addr));
//4:
  //recv(sock, stdout, 255, 0);
  char recvd[256];
  int taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);
//5:
  send(sock, commandLine, strlen(commandLine), 0);

//6:
  //recv(sock, stdout, 255, 0);
  taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);
//7:
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

  // : import database from the file specified on the command line
  // If no file is specified, skip the import.
  // HINT: use do_import_db() -- it's already implemented!

  if(argc==2){
   do_import_db(db, argv[1]);
  }

  // ODO: register with tracker (use sendTrackerCommand)
  sendTrackerCommand("REGISTER");
  runServer(db);

  // ODO: unregister with tracker (use sendTrackerCommand)
  sendTrackerCommand("UNREGISTER");
  // return the used memory
  free(db);

  return 0;
}
