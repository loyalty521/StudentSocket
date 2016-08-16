/*************************************************************************
    > File Name: socket_select.c
    > Author: lizhu
    > Mail: 1489306911@qq.com 
    > Created Time: 2016年08月15日 星期一 07时27分57秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE 256
#define MYPORT  1234
#define BACKLOG 5

int conn_amount = 0;
int fd_A[BACKLOG]; 

void showclient()
{
	int i;
	printf("client amount: %d\n", conn_amount);
	for (i = 0; i < BACKLOG; i++) {
		printf("[%d]:%d  ", i, fd_A[i]);
	}
	printf("\n\n");
}

void main()
{
	signal(SIGPIPE, SIG_IGN);
	
	int opt = 1;
	int sock_fd, new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t sin_size;
	int ret = 1;
	char buf[BUF_SIZE];
	int i;

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return;
	}

	if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(int)) == -1){ //解决服务器端口占用问题 ret=1表示可以重用  
		perror("setsockopt");
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(MYPORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

	if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
		perror("bind");
		return;
	}

	if(listen(sock_fd, BACKLOG) == -1){
		perror("listen");
		return;
	}

	printf("listen port %d\n", MYPORT);

	fd_set fdsr;
	int maxsock;
	struct timeval tv;
	
	conn_amount = 0;
	sin_size = sizeof(client_addr);
	maxsock = sock_fd;
	
	while(1){
        /*将指定的文件描述符集清空，在对文件描述符集合进行设置前，
         * 必须对其进行初始化，如果不清空，由于在系统分配内存空间后，
         * 通常并不作清空处理，所以结果是不可知的。
         * */
		FD_ZERO(&fdsr);
        /*
         *用于在文件描述符集合中增加一个新的文件描述符。
         * */
		FD_SET(sock_fd, &fdsr);

		tv.tv_sec = 30;
		tv.tv_usec = 0;

		for(i = 0; i< BACKLOG; i++){
			if(fd_A[i] != 0){
				FD_SET(fd_A[i], &fdsr);
			}
		}

		ret = select(maxsock+1, &fdsr, NULL, NULL, &tv);
		if(ret < 0){
			perror("select");
			break;
		}else if( ret == 0){
			printf("timeout\n");
			continue;
		}
        /*
         * FD_ISSET(int fd,fd_set *fdset) 用于测试指定的文件描述符是否在该集合中。
         * */
		for(i = 0; i< conn_amount; i++){
			if(FD_ISSET(fd_A[i], &fdsr)){
				ret = recv(fd_A[i], buf, sizeof(buf), 0);
				if(ret <= 0){
					printf("client[%d] close\n",i);
					close(fd_A[i]);
                    /*
                     *FD_CLR(fd_set *fdset) 用于在文件描述符集合中删除一个文件描述符。
                     * */
					FD_CLR(fd_A[i], &fdsr);
					fd_A[i] = 0;
				}else{
					if(ret < BUF_SIZE)
						memset(&buf[ret], '\0', 1);
					printf("client[%d] send:%s\n",i,buf);
				}
			}
		}

		if(FD_ISSET(sock_fd, &fdsr)){
			new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
			if(new_fd<=0){
				perror("accept");
				continue;
			}

			if(conn_amount < BACKLOG){
				fd_A[conn_amount++] = new_fd;
				printf("new connection client[%d] %s:%d\n", conn_amount,
						inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
				if(new_fd > maxsock)
					maxsock = new_fd;
			}else{
				printf("max connections arrive, exit\n");
				send(new_fd,"bye",4,0);
				close(new_fd);
				break;
			}
		}
		showclient();

	}

	for(i = 0; i< BACKLOG; i++){
		if(fd_A[i] != 0){
			close(fd_A[i]);
		}
	}
}
