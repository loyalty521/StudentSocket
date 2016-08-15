/*************************************************************************
    > File Name: socket_select.c
    > Author: lizhu
    > Mail: 1489306911@qq.com 
    > Created Time: 2016年08月15日 星期一 07时27分57秒
 ************************************************************************/

#include<stdio.h>

void start()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket");
		return;
	}

	int opt = 1;
	ssetsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	struct sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = INADDR_ANY;
	ser_addr.sin_port = htons(80);

	int ret = bind(sockfd, (struct sockaddr*) &ser_addr, 16);
	if(ret == -1)
	{
		perror("bind");
		return;
	}

	ret = listen(sockfd, 20);
	if(-1 == ret)
	{
		perror("listen");
		return;
	}

	printf("lizhu server is ready \n");

	while(1)
	{
		
	}
}
