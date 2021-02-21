Name: Hrishabh Raj 
Roll: 1801CS22


CS359 Assignment-4
------------------
A p2p chat server with TCP as underlying transport layer.

The application takes user data from 'users.txt'.
For your custom users, put exactly 5 users' name, ip and port in the 'users.txt' file.
Each user in each line, with name, ip and port space separated. Sample file is included.

Compile the application as:
-> gcc -o chatapp chatApp.c

Run the application as:
-> ./chatApp <port>

Note: <port> must be already existing in the user-info i.e. 'users.txt'.

To send a message, type <friendname>/<Your message>.

Note: <friendname> must be already existing in the user-info i.e. 'users.txt'. Also for successful communication, <friendname> must be running its own chat app. Else, an error showing "Error in connect()ing" will be reported.

To quit the app, type ':q'. 






Sample peer 1:
--------------
Server socket created.

Welcome Aryan to HeheChat
Server binding successful.
Server is listening...

Enter msg to send <friendname>/<msg>.(Enter :q to quit)
(Input)Balli/How everything?
-----------Message Sent-----------

Output: Balli: Fine. how you?
----------------------------------


Sample peer 2:
--------------
Server socket created.

Welcome Balli to HeheChat
Server binding successful.
Server is listening...

Enter msg to send <friendname>/<msg>.(Enter :q to quit)
Aryan: How everything?
----------------------------------

(Input)Aryan/Fine. how you?
-----------Message Sent-----------
