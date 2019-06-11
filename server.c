// C standards headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Unix headers
#include <unistd.h>
// Network headers:
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#define BUFFER_SIZE 256   // BUFFER SIZE

/// Global Variables :
time_t ticks;             //Make serveur on sleep mode
int server;              //Close Server when SIGUSR1 is received
int N;                    //Number of clients when SIGUSR2 is received
int tab[10]={};           //Table for clients sockets

/// Functions for colorful display
void blue (){
  printf("\033[0;34m");
}
void red () {
  printf("\033[1;31m");
}
void yellow() {
  printf("\033[1;33m");
}
void green() {
  printf("\033[1;32m");
}
void magenta() {
  printf("\033[0;35m");
}
void reset () {
  printf("\033[0m");
}
// Functions prototype
int cree_socket_tcp_ip();
int affiche_adresse_socket(int sock);
int affiche_adresse_distante(int sock);
int connexion(int contact_socket);
void handling( int tab[],int size, int i );
void usr1(int sig);
void usr2(int sig);

// Main Program
int main() {
    int i=0;                                         //Nombre of clients counter
    signal(SIGUSR1, usr1);                           //SIGUSR1
    signal(SIGUSR2, usr2);                           //SIGUSR2
    pid_t pid , fpid , p_main;
    int contact_socket;                              //Server Socket
    int connected_socket;                            //Client Socket
    char buffer[BUFFER_SIZE];
    blue();
    printf("[+][+][+]SERVER[+][+][+] \n");
    reset();
    /// Creation of contact socket:
    contact_socket = cree_socket_tcp_ip();
    server = contact_socket;
    /// Display local adress
    affiche_adresse_socket( contact_socket );
    /// Listening on the port , Max of 10 clients:
    listen( contact_socket , 10);
    magenta();
    printf(" [+][+][+] WAITING FOR CONNECTION [+][+][+] \n");
    while (1) {
        connected_socket = connexion(contact_socket);      // Acceptation of a client connection demand
        i++;                                               // update number of clients
        N=i;                                               // Number of connected clients
        tab[i]=connected_socket;                           // Save connected socket number of a client
        if (i%2==1) {
            strcpy(buffer,"YOU'RE CONNECTED TO : @MAIN SERVER" );
            write( tab[i], buffer, strlen(buffer));         //Sending welcome message to the first client
        }
        if ( (i%2==0) ){                                            // 2 clients are connected
                p_main=fork();                                     // fork
                if (p_main<0)
                    perror("fork");
                else if( p_main==0){      // Child Processus
                    close(contact_socket);
                    magenta();
                    printf("\n CLIENT  %d:\t",i-1);
                    affiche_adresse_distante( tab[i-1] );
                    green();
                    printf("\n CLIENT  %d:\t",i);
                    affiche_adresse_distante( tab[i] );
                    blue();
                    printf("TWO CLIENTS :  %d AND  %d ARE NOW CONNECTED\n\t\t***** ||*********\n",i-1,i);
                    handling( (int*)tab , 10 , i );
                    break;
                 }
                 else {                                 //Father Process
                 }
          }
          sleep(1);                                    //Sleep mode
     }
}
/**
 * Signal SIGUSR1 : Closing Server/client
 * @param sig
 */
void usr1(int sig){
    int cpt;                                         //counter for clients sockets table
    red();
    printf("\n\n SIGNAL USR1 WAS SENT\n\n");
    printf("[-][-][-] SERVEUR WILL DISCONNECT [-][-][-]\n");
     for (cpt=0;cpt<10;cpt++) {
                if( tab[cpt]!=0 ) {
                      write( tab[cpt] ,"SERVEUR WILL CLOSE NOW\n", strlen("SERVEUR WILL CLOSE NOW") );
                      if ( close(tab[cpt])==-1)
                           printf(" ERROR CLOSE \n");
                                  }
                              }
    close (server);                                 //Closing Server socket
    kill( -getpid(), SIGQUIT);                       //kill Child Process
    reset();
    exit(1);
}
/**
 * function Signal SIGUSR 2 : Number of connected clients
 * @param sig
 */
void usr2( int sig ) {
    red();
    printf("\n SIGNAL USR2 WAS SENT , NUMBER  = %d\n", sig);
    printf("NUMBER OF CLIENTS :  ** %d ** \n\n",N);
}

  /**
 * function connection socket : accepting a connection request
 * @param socket
 */
//
int connexion(int contact_socket) {
    struct sockaddr_in adresse;
    int connected_socket;
    int longueur = sizeof ( adresse );
    connected_socket = accept( contact_socket ,(struct sockaddr*)&adresse,&longueur);
    if ( connected_socket < 0 ){
        perror( "accept" );
        close(contact_socket);
        exit(1);
    }
     return connected_socket;
}
/**
* function Connection between two clients
* @param tab : sockets table
* @param size : table size
* @param i : clients number
*/
void handling( int tab [],int size, int i ) {
       pid_t pidt;
       char buffer[BUFFER_SIZE];
       int nb;
       pidt = fork();                         //fork
       if (pidt< 0)
           perror( "fork" );
       else if (pidt == 0) {                 //Child process
           while (1){
               nb = read(tab[i-1], buffer, BUFFER_SIZE);              //read client 1 message
               if (nb==0)
                   break;
               buffer[nb-1] = '\0';
               if ( !strncmp( buffer,"exit",4 ) ){
                   write( tab[i], buffer, strlen(buffer)+1 );     //Write "exit" message for the second client to quit
                   printf("ClIENTS : %d & %d ARE DISCONNECTED  \n",i,i-1);
                   tab[i-1]=0;
                   tab[i]=0;
                   break;
              }
              write( tab[i], buffer, strlen(buffer)+1 );                //Write the message for client 2
              bzero(buffer,BUFFER_SIZE);                                //clean the BUFFER
           }
      } else {                                                     //Father process
          while(1){
              nb = read(tab[i], buffer, BUFFER_SIZE);                   //read client 2 message
              if (nb==0)
                  break;
              buffer[nb-1] = '\0';
              if ( !strncmp( buffer,"exit",4 ) ){
                  write( tab[i-1], buffer, strlen(buffer)+1 );  //Write "exit" message  for the first client to quit
                  printf("ClIENTS : %d & %d ARE DISCONNECTED  \n",i,i-1);
                  tab[i-1]=0;
                  tab[i]=0;
                  break;
              }
              write( tab[i-1], buffer, strlen(buffer)+1 );               //Write the message for client 1
              bzero(buffer,BUFFER_SIZE);                                 //clean the BUFFER
          }
      }
}
/**
* function Creation of socket
* @return Socket Descriptor
*/
int cree_socket_tcp_ip(){
    int sock;
    struct sockaddr_in adresse;
    // IP et TCP :
    if ( ( sock = socket( AF_INET , SOCK_STREAM , 0 ) ) < 0) {
        fprintf(stderr, "Erreur socket.\n");
        exit(1);
    }
    int flag=1;                                  // FIX : "Address already in use" error message
    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof flag) == -1) {
        perror("setsockopt");
        exit(1);
    }
    memset(&adresse, 0, sizeof(struct sockaddr_in));
    adresse.sin_family = AF_INET;  // Protocol IP
    adresse.sin_port = htons(33016);  // port 33016
    inet_aton("127.0.0.1", &adresse.sin_addr); // IP localhost
    if (bind(sock, (struct sockaddr*) &adresse, sizeof(struct sockaddr_in)) < 0){
        close(sock);
        perror("Erreur bind");
        exit(2);
    }
    return sock;
}
/**
* function Display socket information
* @param sock : contact_socket
*/
int affiche_adresse_socket(int sock)
{
     struct sockaddr_in adresse;
     socklen_t longueur;
     longueur = sizeof(struct sockaddr_in);
     if (getsockname(sock, (struct sockaddr*)&adresse, &longueur) < 0){
          close(sock);
          perror("Erreur getsockname");
          exit(3);
          }
     printf("IP = %s, Port = %u\n", inet_ntoa(adresse.sin_addr), ntohs(adresse.sin_port));
     return 0;
}

/**
* function Display Server adress
* @param sock : contact_socket
*/
//
int affiche_adresse_distante(int sock)
{
    struct sockaddr_in adresse;
    socklen_t longueur;
    char buffer[BUFFER_SIZE];
    longueur = sizeof(struct sockaddr_in);
    if (getpeername(sock, (struct sockaddr*) &adresse, &longueur) < 0) {
        perror( "getpeername" );
        close(sock);
        exit(12);
    }
    printf( "IP distante = %s, port distant = %u is connected\n\n", inet_ntoa(adresse.sin_addr), ntohs(adresse.sin_port) );
    return 0;
}





