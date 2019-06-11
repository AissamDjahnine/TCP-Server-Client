// C standards headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Unix headers
#include <unistd.h>
// Network headers
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
////////// NOTE //////////

#define BUFFER_SIZE 256         //BUFFER size
#define IP "127.0.0.1"          //IP adress
#define PORT "33016"            //PORT

/// Global variables :
unsigned char port_client;

/// Functions for colorful display
void blue () {
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
int cree_socket_tcp_ip_client();
int affiche_adresse_socket(int sock);
void communication( int socket,char name[],int taille );
// Main program
int main(int argc, char *argv[] ) {
    if ( argc!=2 ){
         red();
         printf("Usage : Connect Username , by default Username is client\n");
         argv[1]="client";
         reset();
    }
    magenta();
    printf("HELLO , YOUR USER NAME IS : %s!\n",argv[1]);
    reset();
    int port;
    int socket;
    int sortie;
    /// conversion char table -> integer:
    sscanf( PORT, "%d", &port );
    /// creation connection socket
    socket = cree_socket_tcp_ip_client( IP, port );
    /// Display socket information :
    affiche_adresse_socket( socket );
    communication(socket,argv[1],10);     // Communication
    red();
    printf("GOOD BYE\n");
    reset();
    close(socket);                        ///Close socket
    exit(EXIT_SUCCESS);                   /// exit
}

/// functions Implementation
/**
* function communication , processing the connection between two clients
* @param socket : client socket
* @param name : client name
* @param size : name table size
*/
void communication( int socket,char name [],int taille) {
    char buffer[BUFFER_SIZE];
    int nb=0;
    while (1){
         nb=read( socket , buffer, BUFFER_SIZE );
         buffer[nb] ='\0';
          if ( !strncmp( buffer,"YOU'RE CONNECTED TO : @MAIN SERVER",34) ){
              printf(" %s \n", buffer );
          } else if( !strncmp( buffer,"SERVEUR WILL CLOSE NOW",22) )
              printf(" %s\n",buffer);
          else  {
              green();
              printf("Other User : ");
              reset();
              printf(" %s\n ",buffer);
         }
         if ( !strncmp( buffer,"exit",4 ) ){
             printf("ClIENT %s IS DISCONNECTED\n",name);
             close(socket);
             break;
         }
         if ( !strncmp( buffer,"SERVEUR WILL CLOSE NOW",strlen("SERVEUR WILL CLOSE NOW" ) )) {
             yellow();
             printf(" --- SIGNAL USR1 RECIEVED --- \n");
             reset();
             close(socket);
             break;
         }
         yellow();
         printf("%s : ",name);
         reset();
         fgets( buffer, BUFFER_SIZE, stdin );
         write( socket, buffer, strlen(buffer) );
         if ( !strncmp( buffer,"exit",4 ) ){
             printf("ClIENT %s IS DISCONNECTED\n",name);
             close(socket);
             break;
         }
     }
}
/**
* function creation clients socket
* @return Socket  Descriptor
*/
int cree_socket_tcp_ip_client( char *ip, int port )
{
    int socket_contact;
    struct sockaddr_in adresse;
    /// IP and TCP:
    if ((socket_contact = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erreur socket");
        exit(1);
        }
    memset(&adresse, 0, sizeof( struct sockaddr_in ) );
    adresse.sin_family = AF_INET;            // Protocol IP
    adresse.sin_port = htons(port);          // port 33016
    inet_aton(ip, &adresse.sin_addr);        // IP internet
    // connexion au site local:
    if (connect(socket_contact, (struct sockaddr*) &adresse, sizeof(struct sockaddr_in)) < 0)
    {
        close(socket_contact);
        perror("Erreur connect");
        exit(2);
    }else{
        yellow();
        printf("\n CONNECTION REQUEST IS ACCEPTED \n");
        reset();
        }
    return socket_contact;
}
/**
* function Display socket information
* @param sock : socket_contact
*/
int affiche_adresse_socket(int sock)
{
    struct sockaddr_in adresse;
    socklen_t longueur;
    longueur = sizeof(struct sockaddr_in);
    if (getsockname(sock, (struct sockaddr*)&adresse, &longueur) < 0)
    {
        close(sock);
        perror("Erreur getsockname");
        exit(3);
    }
    printf("IP = %s, Port = %u\n", inet_ntoa(adresse.sin_addr), ntohs(adresse.sin_port));
    return 0;
}
