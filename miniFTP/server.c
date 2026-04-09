#include "socketUtils.h"

int main(){
    int serverFD=makeIP4socket();
    struct sockaddr_in servAddr= assignSocketAddress();

    if(bind(serverFD,(struct sockaddr*)&servAddr, sizeof(servAddr)) = -1){
        perror("bind failed");
        return 1;
    }

    if(listen(serverFD,1) == -1){
        perror("listen failed");
        return 1;
    }

    printf("server lsitening on %s : %d \n",IP,PORT);

    int clientFD= accept(serverFD,NULL,NULL);
    if(clientFD == -1){
        perror("accept failed");
        return 1;
    }

    char filename[256];
    recv(clientFD,filename,sizeof(filename),0);
    printf("receiving file: %s\n", filename);
    file *fp = fopen(filename,"wb");
    if(!fp){
        perror("file open failed");
        return 1;
    } 

    char buffer[1024];
    ssize_t bytes;
    while((bytes=recv(clientFD,buffer,sizeof(buffer),0))>0){
        fwrite(buffer,1,bytes,fp);
    }
    printf("file received successfully!\n");
    fclose(fp);
    close(clientFD);
    close(serverFD);
    return 0;
}