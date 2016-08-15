#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WEB_ROOT "/var"
#define DEFAULT_PAGE "/index.html"

int read_line(int fd,char *buf,int size){
	int i;
	for(i = 0; i < size; ++i){
		int n = recv(fd,buf+i,1,0);
		if(1==n){
			if(buf[i]=='\n')break;
		}else{
			perror("read_line");
			return -1;
		}
	}
	buf[++i] = '\0';
	return i;
}

void do_get(int sockfd,char *filename){
	char path[128] = {'\0'};
	if(strcmp("/",filename)==0){//这个操作时默认首页的时候使用的
		filename = DEFAULT_PAGE;//这个时可以的
	}
	sprintf(path,"%s%s",WEB_ROOT,filename);
	int ret = open(path,O_RDONLY);
	if(ret<0){
		perror("open");
		char err_msg[129] = "<h1>404</h1>";
		send(sockfd,err_msg,strlen(err_msg),0);
		return;
	}

	while(1){
		char buf[1024] = {'\0'};
		int size = read (ret,buf,sizeof(buf));
		if(size <=0 )break;
		write(sockfd,buf,size);
	}
	close(ret);
}

void start(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);//PF_INET
		if (-1 == sockfd) {
			perror("socket");
			exit(1);
		}

		int opt = 1; //1代表可以重用      解决服务器端口占用
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, 4); //4代表opt的大小

		struct sockaddr_in ser_addr;
		ser_addr.sin_family = AF_INET;
		ser_addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");
		ser_addr.sin_port = htons(80);

		int ret = bind(sockfd, (struct sockaddr*) &ser_addr, 16);
		if (-1 == ret) {
			perror("bind");
			exit(1);
		}

		ret = listen(sockfd, 20);
		if (-1 == ret) {
			perror("listen");
			exit(1);
		}

		printf("lizhu server is ready\n");

		while(1){
			int newfd = accept(sockfd,NULL,NULL);
			if(-1 == newfd){
				perror("accept");
				continue;
			}
			printf("a client connected\n");

			while(1){
				char buf[1024] = {"\0"};
				int size = read_line(newfd,buf,sizeof(buf));
				if(size <=2 )break;

				//GET /a.html HTTP/1.1\r\n拆分字符串获得a.html
				if(strncasecmp("GET",buf,3)==0 || strncasecmp("POST")==0){
					char *p = strchr(buf,' ');//extern char *strchr(const char *s,char c);查找字符串s中首次出现字符c的位置
					if(p){
						++p;
						char *q = strchr(p,' ');
						if(q){
							*q = '\0';
							do_get(newfd,p);
						}
					}
				}
				printf("recv:%d,%s\n",size,buf);
			}
			close(newfd);
		}


		close(sockfd);
}

int main(int agc, char *agv[]) {
	start();
	return 0;
}
