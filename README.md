# Peer-2-Peer-Chat-in-C
A Peer to Peer(P2P) Chat Application in C using TCP Protocols for connections within a defined closed set of users.

## Adding Users
The users.txt file defines the closed set of users that you want to chat to. The first line should be the total number of users followed by data of users (IPv4 Address and Port).

## Compilation of Source Code
Compile the source code using the following command:
```
gcc -o chatApp chatApp.c
or
make
```
## Running the application
Run the application using the following format:
```
./app <YOUR PORT>
```
### For testing on local machine
For testing on a single machine, run the executable in multiple instances of the terminal. It would act similar to multi-computer network.

### For example (local machine):
#### Terminal 1
```
./chatApp 3000
```
#### Terminal 2
```
./chatApp 8000
```
#### Terminal 1 Interaction Output (Balli)
```
Server socket created.

Welcome Balli to HeheChat
Server binding successful.
Server is listening...

Enter msg to send <friendname>/<msg>.(Enter :q to quit)
Aryan: How everything?
----------------------------------

(Input)Aryan/Fine. how you?
-----------Message Sent-----------
```
#### Terminal 2 Interaction Output (Aryan)
```
Server socket created.

Welcome Aryan to HeheChat
Server binding successful.
Server is listening...

Enter msg to send <friendname>/<msg>.(Enter :q to quit)
(Input)Balli/How everything?
-----------Message Sent-----------

Output: Balli: Fine. how you?
----------------------------------
:q
```
