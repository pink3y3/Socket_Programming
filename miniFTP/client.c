#include "socketUtils.h"

int main(){
    int clientFD=makeIP4Socket(); // create socket
    struct sockaddr_in servAddr = assignSocketAddress();

    if(connect(clientFD,(struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){ //connect to server(ip+port)
        perror("connect failed");
        return 1;
    }

    char filename[256];
    printf("enter filename to send: ");
    scanf("%s",filename);

    FILE *fp = fopen(filename,"rb"); //read file in bin mode
    if(!fp){
        perror("file open failed");
        return 1;
    }

    send(clientFD,filename,sizeof(filename),0); //firs thing sent- > filenmae, server uses this to create file

    char buffer[1024];
    size_t bytes;
    while((bytes = fread(buffer,1,sizeof(buffer),fp))>0){ //read file, send to server
        send(clientFD,buffer,bytes,0);
    }

    printf("file sent successfully");
    fclose(fp);
    close(clientFD);
    return 0;
} 