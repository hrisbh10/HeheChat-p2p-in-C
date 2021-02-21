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
#### Terminal 1 Interaction Output (shashwat)
```
Server Running! Start Conversation!
Welcome to Peer Chat!

These are the people available to chat:
anmol
balli
aryan
sunny
harsh

Enter ':q' for exiting application.

Use the following format for messaging:
receiver_name/message

anmol/Hey anmol!

anmol: Hello balli!

anmol/GTG. Bye!

:q
```
#### Terminal 2 Interaction Output (amish)
```
Server Running! Start Conversation!
Welcome to Peer Chat!

These are the people available to chat:
anmol
balli
aryan
sunny
harsh

Enter ':q' for exiting application.

Use the following format for messaging:
receiver_name/message

balli: Hey anmol!

balli/Hello Balli!

anmol: GTG. Bye!

:q
```
