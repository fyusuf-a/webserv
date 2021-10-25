#include "includes/IPAddress.hpp"
#include "includes/webserv.hpp"
#include "includes/webserv.hpp"
#include "includes/NIOSelector.hpp"
#define DEFAULT_PATH "conf/nginx.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int main(int ac, char **av)
{
	std::string path = ac == 2 ? av[1] : DEFAULT_PATH;

 	WebServ webserv(path);

	while (1) {
		NIOSelector::getInstance()->poll();
	}

 	//std::cout << webserv;
 	return (0);
}

// char *test(const unsigned char *input, size_t len)
// {
//   char *result;
//   char hexits[] = "0123456789ABCDEF";
//   if (input == NULL || len <= 0)
//     return NULL;

//     int resultlength = (len*3)+1;
//     result = (char*)malloc(sizeof(char) * resultlength); 
//     bzero(result, resultlength);

//     for (int i = 0; i < len ; i++)
//     {
//       result[i*3] = hexits[input[i] >> 4];
//       result[(i*3)+1] = hexits[input[i] & 0x0F];
//       result[(i*3)+2] = ' ';
//     }
//     return (result);

// }

//  int main (int ac, char *av[])
//  {
//      int                         sock, conff, n;
//      struct sockaddr_in  sin;
//      uint8_t buff[MAXLINE + 1];
//      uint8_t recvline[MAXLINE + 1];


//      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
//        printf("error\n");

//       bzero(&sin, sizeof(sin));
//      sin.sin_addr.s_addr = htonl(INADDR_ANY);
//      sin.sin_family = AF_INET;
//      sin.sin_port = htons(SERVER_PORT);

//      if (bind(sock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
//        printf("error\n");

//      if (listen(sock, 100 ) == SOCKET_ERROR)
//        printf("error\n");

//      for (int i = 0 ; ; i++)
//      {
//        struct sockaddr_in addr;
//        socklen_t addr_len;

//        std::cout << "Waiting for connection..." << std::endl;
//        fflush(stdout);
//        conff = accept(sock, (sockaddr*) NULL, NULL);
      
//        memset(recvline, 0, MAXLINE);

//        while ( (n = read(conff, recvline, MAXLINE - 1) ) > 0)
//        {
//          fprintf(stdout, "\n\n%s", recvline);

//          if (recvline[n-1] == '\n')
//            break;
//         }
//         memset(recvline, 0, MAXLINE);

//         snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHEllo -> %d", i);

//         write(conff, (char*) buff, strlen((char*)buff));
//         close(conff);
//      }

//  }
