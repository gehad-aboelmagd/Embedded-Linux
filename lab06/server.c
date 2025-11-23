#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
    int soc_fd, conn_fd;
    struct sockaddr_in serv_addr;
    int serv_addr_len = sizeof(serv_addr);
    char buff[100];
    int status, bytes;

    soc_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(soc_fd < 0)
    {
        perror("Unable to assigne a socket\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);
    
    status = bind(soc_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(status < 0)
    {
        perror("Unable to assign a server address...\n");
        close(soc_fd);
        return 1;
    }
    else
    {
        printf("binding...\n");
    }

    status = listen(soc_fd, 3);
    if(status < 0)
    {
        perror("Unable to listen for incomming request...\n");
        close(soc_fd);
        return 1;
    }
    else
    {
        printf("listening...\n");
    }

    conn_fd = accept(soc_fd, (struct sockaddr *)&serv_addr, &serv_addr_len);
    if(conn_fd < 0)
    {
        perror("Unable to accept request...\n");
        close(soc_fd);
        return 1;
    }
    else
    {
        printf("connection accepted...\n");
    }

    bytes = recv(conn_fd, buff, sizeof(buff)-1, 0);
    if(bytes <= 0)
    {
        printf("Nothing received\n");
        close(soc_fd);
        close(conn_fd);
        return 1;
    }
    else
    {
        buff[bytes] = '\0';
        printf("receiving %d bytes...\n", bytes);
    }

    // buff[100] = '\0';
    if(0 == strcmp(buff, "Hi, how are thigns?"))
    {
        strcpy(buff, "I'm fine, thanks\n");
    }
    else
    {
        strcpy(buff, "Mmmm, can't resolve your message.\n");
    }

    status = send(conn_fd, buff, sizeof(buff), 0);
    if(status < 0)
    {
        perror("Unable to reply\n");
    }
    else
    {
        printf("replying...\n");
        printf("%s\n", buff);
    }

    close(soc_fd);
    close(conn_fd);

    return 0;
}