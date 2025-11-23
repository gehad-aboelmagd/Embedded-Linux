#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int soc_fd;
    struct sockaddr_in serv_addr;
    char buff[100] = "Hi, how are thigns?";
    int status;

    soc_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(soc_fd < 0)
    {
        perror("Unable to assigne a socket\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    status = connect(soc_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(status < 0)
    {
        perror("Unable to connect to remote server\n");
        return 1;
    }
    else
    {
        printf("connecting...\n");
    }

    // write(soc_fd, buff, sizeof(buff)/sizeof(buff[0]));
    status = send(soc_fd, buff, strlen(buff)+1, 0);
    if(status < 0)
    {
        perror("Unable to send my message to server\n");
        return 1;
    }
    else
    {
        printf("sending...\n");
        printf("%s\n", buff);
    }

    // read(soc_fd, buff, sizeof(buff));
    status = recv(soc_fd, buff, sizeof(buff), 0);
    if(status < 0)
    {
        perror("Error while recieving response\n");
        return 1;
    }
    else
    {
        printf("receiving...\n");
    }

    close(soc_fd);

    return 0;
}