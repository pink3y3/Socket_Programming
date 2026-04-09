#include "socketUtils.h"

int main(){
    int serverFD=makeIP4Socket(); // opens tcp socket - ready to communicate
    struct sockaddr_in servAddr= assignSocketAddress();

    if(bind(serverFD,(struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){ //bind socket to ip+port(send all traffic here)
        perror("bind failed");
        return 1;
    }

    if(listen(serverFD,1) == -1){ // wait for incoming clients
        perror("listen failed");
        return 1;
    }

    printf("server lsitening on %s : %d \n",IP,PORT);

    int clientFD= accept(serverFD,NULL,NULL); // accept connection - block until client connects
    if(clientFD == -1){
        perror("accept failed");
        return 1;
    }
    /*serverFD->waiting socket, clientFD->actual communication socket*/
    char filename[256];
    recv(clientFD,filename,sizeof(filename),0); //receive filename
    printf("receiving file: %s\n", filename);
    FILE *fp = fopen(filename,"wb"); //prep to write incoming file
    if(!fp){
        perror("file open failed");
        return 1;
    } 

    char buffer[1024];
    ssize_t bytes;
    while((bytes=recv(clientFD,buffer,sizeof(buffer),0))>0){ // does it, client closes connctn when recv=0
        fwrite(buffer,1,bytes,fp);
    }
    printf("file received successfully!\n");
    fclose(fp);
    close(clientFD);
    close(serverFD);
    return 0;
}