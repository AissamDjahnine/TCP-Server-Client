# TCP-Server-Client :e-mail: :busts_in_silhouette:

Implementation of TCP-Server/client system to contact two clients. 

* TCP is suited for applications that require high reliability, and transmission time is relatively less critical. It is used by other protocols like HTTP, HTTPs, FTP, SMTP, Telnet. TCP rearranges data packets in the order specified. There is absolute guarantee that the data transferred remains intact and arrives in the same order in which it was sent. TCP does Flow Control and requires three packets to set up a socket connection, before any user data can be sent. TCP handles reliability and congestion control. It also does error checking and error recovery. Erroneous packets are retransmitted from the source to the destination.
source : [TCP Server-Client](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)

## Getting Started & Prerequisites 

**Step #1: Install C/C++ compiler and related tools**

If you are using Fedora, Red Hat, CentOS, or Scientific Linux, use the following yum command to install GNU c/c++ compiler:

           yum groupinstall 'Development Tools'
           
If you are using Debian or Ubuntu Linux, type the following apt-get command to install GNU c/c++ compiler:

           $ sudo apt-get update
           $ sudo apt-get install build-essential manpages-dev

**Step #2: Verify installation**

Type the following command to display the version number and location of the compiler on Linux:

           $ whereis gcc
           $ which gcc
           $ gcc --version
           
## Execution :  

**Use the makefile to compile the cpp files :**

You can check the [makefile](https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/makefile)  :ballot_box_with_check:

**Execute the program :**
* Server :

        ./Server 
   
* Client :

        ./Client Username
        
**Example :** 

* Server example :

<img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./server.jpg" >    

* Client  example :

**CLient 1 : Recieving the Welcome message ( Status : WRITE )**

<img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./client1.jpg" > 

**CLient 2 : Waiting to read the client1 message ( Status : READ )**

<img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./client2.jpg" > 


## Tests & results :
* Message-vs-Message Chat : while the client 1 is on **WRITING MODE** , the client 2 is on **READING MODE**
* when a third client is connected , he must wait for the 4 th client since the chat rooms are 2-Max clients.
* The Server displays the information about the : distant port of the two clients,IP adresses and the status of the clients ( Connected , disconnected ) 

**Example :** 

 <img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./chat.jpg" > 

* **Sending Signal SIGUSR1 :** 

The signal " SIGUSR1 " ends the connections established between the two clients ( or more ) by closing the server and clients sockets.
In order to send the signal , we use the command **top** to get the Server and the clients PID and then we use : 

                      kill -SIGUSR2 PID_Server PID_client1 PID_client2
                      
The figure below demonstrates the steps above with a display **" THE SERVER WILL DISCONNECT "** :

 <img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./sigusr1.jpg" > 

* **Sending Signal SIGUSR2 :**

The signal " SIGUSR2 " gives us the information about the number of clients already connected to the server.
In order to send the signal , we use the command **top** to get the Server PID ( in this case : 181 ) and then we use : 

                      kill -SIGUSR2 PID 
The figure below demonstrates the steps above with a display **" NUMBER OF CLIENTS : ** 2 ** "** :

 <img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./sigusr2.jpg" > 



## Authors

* **Djahnine Aissam**  - [Profile](https://github.com/AissamDjahnine)

## Acknowledgments

* Part of this job was supported by : Vincent Fraillon-maison  :thumbsup:


