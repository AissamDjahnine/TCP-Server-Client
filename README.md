# TCP-Server-Client

Implementation of Server/client system to contact two client via network. 

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

**Use of the csv files as database :**

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

**CLient 1 : Waiting to read the client1 message ( Status : READ )**

<img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./client2.jpg" > 

## Tests & results : 
* Message-vs-Message Chat : while the client 1 is on **WRITING MODE** , the client 2 is on **READING MODE** 

Example : 

 <img src="https://github.com/AissamDjahnine/TCP-Server-Client/blob/master/files./chat_test.jpg" > 

* Sending Signal SIGUSR1 : 

* Sending Signal SIGUSR2 :


## Authors

* **Djahnine Aissam**  - [Profile](https://github.com/AissamDjahnine)

## Acknowledgments

* Part of this job was supported by : Vincent Fraillon-maison  :thumbsup:


