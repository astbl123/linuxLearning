/**
 * @file    sysfsRead.c
 * @author  BOLONG TAN
 * @version V1.0.0
 * @date    27-April-2018
 * @brief   This file is for sysfs file reading and handle the string
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>//错误返回值
            

int cmpStr(char *src,char *dest);

int main(int argc,char *argv[]){
	int fd = -1;
	char buf[100] = {0};
	int ret = -1;
	char dir[] = "/sys/power/state";
	extern int errno;
    //1.打开文件
	fd = open(dir,O_RDWR);
	if(-1 == fd){
		printf("文件打开错误:errno=%d\n", errno);
	}else{	
		printf("文件打开成功，fd = %d\n", fd);
	}
    //2.读取文件
	ret = read(fd, buf, 40);
	if(ret < 0){
		printf("read=%d, errno=%d 失败\n", ret, errno);
	}else{
		printf("实际读取%d个字节.\n", ret);
		printf("文件内容是: [%s].\n", buf);
	}
	//3.比较字符串是否是自己想要找的字符串	
	if(cmpStr(buf,"disk") == 0){
		printf("string found.\n");
	}else{
		printf("string not found.\n");
	}
	close(fd);
	return 0;
}


int cmpStr(char *src,char *dest){
	char *token;
    int len,i;
    //去掉字符串里面的回车字符
	printf("src is [%s], dest is [%s] \n", src, dest);
	len = strlen(src);
	for(i = 0; i < len; i++){
		if(src[i] == '\n')
			src[i] = '\0';
	}
    //利用strtok函数截取字符串，再逐个比较字符串
	token = strtok(src," ");
	while(token != NULL){
		printf("token string is %s \n", token);
		if(strcmp(token, dest) == 0){
			printf("found string %s \n", token);
			return 0;
		}
            		
		token = strtok(NULL, " ");
	}
	return -1;
}
