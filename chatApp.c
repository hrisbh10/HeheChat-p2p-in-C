// Name: Hrishabh Raj       Roll: 1801CS22
#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <errno.h>
#define MSG_SIZE 1024

typedef struct User{
    char name[30];
    char ip[16];
    int port;
}User;

void error(char *msg,int v){
    fprintf(stderr,"\n%s\n",msg);
    if(v)
        exit(0);
}

// Function to read users.txt at the beginning to gain user-info
void initUserTable(User *users){
    FILE *fp = fopen("users.txt","r");
    if(fp == NULL){
        error("First create user_info table as users.txt with 5 entries\nExiting...\n",1);
    }
    for(int i=0;i<5;++i)
        fscanf(fp,"%s %s %d",users[i].name,users[i].ip,&(users[i].port));
    fclose(fp);
}

// Function to send Message to a user
void sendMsg(char* buffer,User *users,int userId){
    char person[30],msg[MSG_SIZE];
    bzero(person,30);
    bzero(msg,MSG_SIZE);

    // Checking if the stdin format is correct
    sscanf(buffer,"%[^/]%*c%[^\n]%*c",person,msg);

    // return if incorrect format
    if(strlen(msg) == 0){
        fprintf(stderr,"Usage: <friendname>/<msg> Use '/' as separator\n");
        return;
    }

    // check if the person is a user or not
    int checkValid = -1;
    for(int i=0;i<5;++i){
        if(!strcmp(person,users[i].name)){
            checkValid = i;
            break;
        }
    }
    // return if not present
    if(checkValid == -1){
        error("Invalid User: Not found in user-list\n",0);
        return;
    }

    // create new sockfd to connect to the user's ip and port
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
        error("Creating socket for communication\n",1);

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(users[checkValid].ip); 
    servaddr.sin_port = htons(users[checkValid].port);

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
        error("Error on connect()ing. User maybe offline.\n",0);
        if(errno == ECONNREFUSED)
            return;
    }

    //prepare the message to be sent
    sprintf(buffer,"%s: %s",users[userId].name,msg);

    send(sockfd, buffer, MSG_SIZE, 0);
    printf("-----------Message Sent-----------\n\n");

    close(sockfd);

}

int main(int argc,char* argv[]){
    User users[5];
    char buffer[MSG_SIZE];
    // to read users.txt file to take Users data
    initUserTable(users);

    int servsock,peersock;
    int maxfd,port,result;
    fd_set readfd, masterfd;
    struct sockaddr_in servaddr,clientaddr;
    int addrlen = sizeof(struct sockaddr);

    if(argc != 2){
        printf("Usage: %s <port_no>\n",argv[0]);
        return 0;
    }
    port = atoi(argv[1]);
    if((servsock = socket(AF_INET,SOCK_STREAM,0)) < 0){
        error("Error: Creating server socket\n",1);
        return 0;
    }
    else
        printf("Server socket created.\n");

    //check if the port is registered with a user or not
    int checkPort = -1;
    for(int i=0;i<5;++i){
        if(users[i].port == port){
            printf("\nWelcome %s to HeheChat\n",users[i].name);
            checkPort = i; 
            break;
        }
    }
    if(checkPort == -1){
        close(servsock);
        error("Error: Port number not found in users.txt\n",1);
    }

    // to reuse port even if program crashes
    int enable = 1;
    setsockopt(servsock,SOL_SOCKET,SO_REUSEADDR,&enable,sizeof(int));

    // starting the server side for other peers to connect
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port);

    if(bind(servsock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        error("Error on Binding socket\n",1);
    else
        printf("Server binding successful.\n");

    if(listen(servsock,5) < 0)
        error("Error on listening...\n",1);
    else
        printf("Server is listening...\n");

    // creating master file descriptor set which will contain every connected fds
    FD_ZERO(&masterfd);
    FD_SET(servsock,&masterfd); // adding serversocket to listen for peers connection
    FD_SET(0,&masterfd); //Adding stdin to fdset

    maxfd = servsock;
    printf("\nEnter msg to send <friendname>/<msg>.(Enter :q to quit)\n");
    while(1){
        
        readfd = masterfd;  // make a copy of the masterfd set
        // monitor all the fds < maxfd+1
        result = select(maxfd+1,&readfd,NULL,NULL,NULL);

        if(result < 0)
            error("Error on select()\n",1);

        // if the servsock fd is ready, then call accept() to accept incoming connections
        if(FD_ISSET(servsock,&readfd)){
            peersock = accept(servsock,(struct sockaddr*)&clientaddr,&addrlen);
            if(peersock < 0)
                error("Error in accept()ing connection\n",0);
            else{
                FD_SET(peersock,&masterfd);
                maxfd = (peersock > maxfd)?peersock:maxfd;
                // printf("New connection received from %s\n",inet_ntoa(clientaddr.sin_addr));
            }
            //removing server socket from the readfdset temporarily
            FD_CLR(servsock,&readfd); 
        }
        // if the stdin is ready for input
        if(FD_ISSET(0,&readfd)){
            result = read(0,buffer,MSG_SIZE);
            if(result < 0)
                error("Error reading from stdin\n",0);
            buffer[result] = '\0';
            if(!strcmp(":q\n",buffer)){
                close(servsock);
                printf("User is exiting...\n");
                exit(0);
            }
            else{
                sendMsg(buffer,users,checkPort);
            }
        }
        // look over peers sockets for msg receiving
        for(int i=1;i<=maxfd;++i){
            if(FD_ISSET(i,&readfd)){
                result = recv(i,buffer,MSG_SIZE,0);
                if(result == 0){    //if doesn't recv anything, close that socket
                    close(i);
                    FD_CLR(i,&masterfd);
                }
                else if(result > 0){
                    buffer[result] = '\0';
                    printf("%s",buffer);
                    printf("\n----------------------------------\n\n");

                }
                else
                    error("Error in recv()ing msg",0);
            }
        }
    }

    return 0;  
}
