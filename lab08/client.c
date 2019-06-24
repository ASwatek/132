/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * client.c - Source file for the "thin client" you make in this lab.
 *            This program will connect to a server specified and let
 *            you issue commands.
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
#include <netinet/in.h>
#include <netdb.h>

/* Some constants for the servers and such */
//const char*               TRACKER_ADDR    = "137.112.40.250";
const char*		  TRACKER_ADDR	  = "137.112.45.240";
const unsigned short      TRACKER_PORT    = 22222;

/**
 * Connects to a server, handles interactions, then returns on disconnect.
 *
 * @param address: a string representing the server's address
 * @param port: the port to connect
 */
void
do_connect_to_server(const char* address, int port)
{
  // 1. Create the socket
  int sock;
  struct sockaddr_in srv_addr;

  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("Could not create socket for connection to server.");
    return;
  }

  // 2. Set the server address 
  //    Hint: convert the argument from string to address using "inet_addr(address)"
  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = inet_addr(address);
  srv_addr.sin_port = htons(port);

  // 3. Connect to the server and run the loop.
  if (connect(sock, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0) {
    printf("Could not connect to server.");
    return;
  }

  char send_string[512];
  char received_string[512];
  int received_bytes = 0;

  // runloop 
  for (;;) {
    // Hint: if you receive zero bytes from the server, it dropped your connection.
    // 1. read data from server (don't forget to null-terminate 
    //    the string after receiving it).
    received_bytes = recv(sock, (void *)received_string, 512, 0);

    if (received_bytes < 1) {
      printf("Disconnecting from %s ...\n", address);
      break;
    }
    received_string[received_bytes] = '\0';

    // 2. show it to the user.
    printf("%s", received_string);

    // 3. read a line of input from the user.
    fgets(send_string, 512, stdin);

    // 4. send input to the server.
    if (send(sock, (const void*) send_string, strlen(send_string), 0) != strlen(send_string)) {
      printf("Failed to send command to server.\n");
      break;
    }
  }

  // 5. disconnect
  close(sock);

  return;
}

/**
 * Gets the IP address (as a string) from either an IP or
 * hostname.  Puts the IP address into third argument.
 *
 * @param machine - the host or IP address as a string
 * @param portstr - the port (as a string)
 * @param output -  char array where the result goes.
 * @return 0 on success, -1 otherwise.
 */
int
getAddressForHostOrIP(const char* machine, const char* port, char* output)
{
  struct addrinfo *res; // where matches go
  getaddrinfo(machine, port, NULL, &res);

  // maybe we failed to get an address
  if (res == NULL || res->ai_addrlen < 1) {
    printf("Error in looking up host %s\n", machine);
    return -1;
  }

  // this is the address from IP or hostname.
  // struct addrinfo has a member "ai_addr" after
  // it has been created by getaddrinfo().
  // That's where the discovered address is stored.
  struct sockaddr_in* ipaddr = (struct sockaddr_in*)res->ai_addr;

  char* addr = inet_ntoa(ipaddr->sin_addr);
  // have to do this since getaddrinfo allocated it.
  freeaddrinfo(res);

  if (addr == NULL) { return -1; }
  strcpy(output, addr);
  return 0;
}

/**
 * TODO: implement a function that sends a command to the tracker.
 * Copy the body of sendTrackerCommand() from your server.c file and update it
 * to return the "Random" IP address in the "randomIP".  DOCUMENT how it works
 * in this comment block.
 */
void
getRandomServer(char* randomIP, int randomIP_len)
{
  // TODO: FINISH ME!
  // Hints:
  // * Look at the example communication on the lab web page to see
  //   the "protocol" for communicating with the tracker.
  // * Try connecting to the tracker with "nc" to see how the
  //   communication works.
  // * Figure out what order sends/receives are in, write some comments
  //   here describing what you'll do, then write the code to implement
  //   what the comments say.

  int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(TRACKER_ADDR);
  addr.sin_port = htons(TRACKER_PORT);
  connect(sock, (struct sockaddr*) &addr, sizeof(addr));

  char recvd[256];
  int taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);//initial prompt

  send(sock, "RANDOM", 6, 0);
  taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);
//  strcpy(randomIP, recvd);
 // for(int i=8; recvd[i]!='\0' || recvd[i]!='\n' || recvd[i]!=' ' || recvd[i]!='\t'; i++){//i=8 for "TALKTO "
  // randomIP[i-8]=recvd[i];
 // }

  strcpy(randomIP, recvd+7);

  close(sock);
/*
//1: Create a socket
  int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//2: Create an address struct
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(TRACKER_ADDR);
  addr.sin_port = htons(TRACKER_PORT);
//3: Connect to the tracker
  connect(sock, (struct sockaddr*) &addr, sizeof(addr));
//4: Receive a prompt
  //recv(sock, stdout, 255, 0);
  char recvd[256];
  int taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);
//5: Send a command
  send(sock, commandLine, strlen(commandLine), 0);
//6: Receive the result
  //recv(sock, stdout, 255, 0);
  taken = recv(sock, recvd, 255, 0);
  recvd[taken]='\0';
  printf("%s\n", recvd);
//7: Disconnect from the tracker
  close(sock);*/
}

/**
 * Runloop that accepts commands from the user and prints out results.
 *
 * Commands to implement:
 *
 * q - quits the program.
 *
 * c - connects to a remote server.  After connected, all lines of input get
 *     sent to the server.
 *
 * If given a command that doesn't match one in this list, print "help" to show
 * what commands are available.
 */
void
handleLocalInput()
{
  const char* instructions = "(c)onnect, (r)andom connect, or (q)uit";
  char buf[512];
  char buf2[512];
  char buf3[52];

  // loop forever
  for( ;; ) {
    printf("(Local)> ");

    // read input
    fgets(buf, 512, stdin);

    // check to make sure the instruction is not a blank line
    if(strlen(buf) < 1) {
      printf("Invalid instruction.\n");
      printf(" %s\n", instructions);
      continue;
    }

    // select instruction to run
    switch(buf[0]) {
    case 'q':
    case 'x':
      return;

    case 'r': // CONNECT TO RANDOM SERVER
      printf("Querying Tracker... ");
      fflush(stdout);

      //TODO: Finish me ... very similar to 'c'
      // but instead of asking the user for a server,
      // get a random one from the tracker using getRandomServer().
      // You still must prompt the user for which Port to use.
      getRandomServer(buf, 512);//unsure about size
      buf[strlen(buf)-1]='\0';
      printf("\tYou will connect to %s\n", buf);
      printf("\tPort? ");
      fgets(buf2,512, stdin);
      buf2[strlen(buf2)-1]='\0';

      getAddressForHostOrIP(buf, buf2, buf3);
      do_connect_to_server(buf3, atoi(buf2));

      break;

    case 'c': // CONNECT
      // 1. prompt for the address and port.
      printf("\t server address or hostname? ");
      fgets(buf, 512, stdin);
      buf[strlen(buf)-1] = '\0'; //chop off newline

      printf("\t port? ");
      fgets(buf2, 512, stdin);
      buf2[strlen(buf2)-1] = '\0'; //chop off newline

      // 2. call do_connect_to_server.
      getAddressForHostOrIP(buf, buf2, buf3);
      do_connect_to_server(buf3, atoi(buf2));
      break;

    default:
      printf("Invalid instruction.\n");
      printf(" %s\n", instructions);
      continue;
    }
  }
}

int
main(int argc, char** argv)
{
  handleLocalInput();

  return 0;
}
