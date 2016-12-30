#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>


/* 
 * 获取当前系统时间的字符串表示，精确到纳秒
 * 参数 buffer: 保存时间字符串的缓冲区
 * 参数 size: 时间字符串缓冲区的长度
 * 返回值: 传入的缓冲区的地址 
 */

char *get_current_time_string(char *buffer, size_t size) {

    //保证输入缓冲区足够大 
    if(size < 32){
        printf("[%s][line %d]: time buffer size is too small.\n", __FILE__, __LINE__);
        exit(-1);
    }

    struct timespec cur_time;
    struct tm cur_tm;
    size_t offset;

    clock_gettime(CLOCK_REALTIME, &cur_time);
    localtime_r(&cur_time.tv_sec, &cur_tm);
    offset = strftime(buffer, size, "%Y-%m-%d-%H-%M-%S-", &cur_tm);
    sprintf(buffer+offset, "%ld", cur_time.tv_nsec);
    return buffer;
}

int main(){
    char buffer[256];
    get_current_time_string(buffer, sizeof(buffer));
    printf("%s %ld\n", buffer, strlen(buffer));
    return 0;
}

