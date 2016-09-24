#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<event2/event.h>   // 必须包含   libevent的核心头文件
#include<event2/evhttp.h> // libevent 提供的http 服务的头文件
#include<event2/buffer.h> 
void http_req(struct evhttp_request *req,void *arg)
{
char output[2048]="\0";
char tmp[1024];
    //获取 访问的请求链接 (使用 evhttp_request_uri  or  req->uri)
    const char *uri;
    uri = evhttp_request_get_uri(req);
    sprintf(tmp,"uri=%s\n",uri);
    strcat(output,tmp);
 
 
//  把请求的链接参数 解码
    char *decoded_uri;
    decoded_uri = evhttp_decode_uri(uri);
     
 
    //解析url的参数
    struct evkeyvalq params;
    evhttp_parse_query(decoded_uri,?ms);
    sprintf(tmp,"q=%s\n",evhttp_find_header(¶ms,"usrname"));
    strcat(output,tmp);
    sprintf(tmp,"s=%s\n",evhttp_find_header(¶ms,"password"));  // evhttp_find_header 是获取请求链接里特定的字段值
    strcat(output,tmp);
    free(decoded_uri);
 
    /*
    这里可以做很多操作 比如  数据库存储操作  比如memcatch 缓存操作等等
    */
 
    // http 协议头
    evhttp_add_header(req->output_headers,"Content-Type","text/plain;charset=UTF-8");
    evhttp_add_header(req->output_headers,"Connection","hello world");
 
     
    struct evbuffer *buf;  // 字符缓冲区
    buf = evbuffer_new();
    evbuffer_add_printf(buf,"It works !\n%s\n",output);  // 把结果返回给客户端
    evhttp_send_reply(req,HTTP_OK,"OK",buf);
    evbuffer_free(buf);
 
}
int main(int argc, char *argv[])
{
    char *http_addr= "127.0.0.1";
    char *http_port = 8080;
    int http_daemon = 0;
  int http_timeout = 120;
    if (httpd_daemon)
  {
      pid_t pid;
      pid = fork();
      if (pid<0)
        {
        perror("fork failed");
        exit(EXIT_FAILURE);
      }
     if (pid>0)
       {
      exit(EXIT_SUCCESS);
     }
  }
    event_init();  // 初始化 event_init 环境  也可以用 struct event_base *base;
    struct evhttp *http;  // 也可以用 http = evhttp_new(base);   如果调用了 evhttp_new函数 则调用 evhttp_bind_socket 配套使用  我还没试过其他的方式 
    // 这里直接 调用启动 http 函数
    http= evhttp_start(http_addr,http_port);
    evhttp_set_timeout(http,http_timeout);
    evhttp_set_gencb(http,http_req,NULL); // 加载回调
    event_dispatch();
    evhttp_free(http);
    return 0;
}
