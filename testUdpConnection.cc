#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <cstring>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <unistd.h>

#define DELPHI_UDP_PKT_MAX_SIZE 9000 // max size sent over CAN gateway
static const int maxLog = 10000;

using namespace std;

bool configUDP(int *udpFdPtr, int udpPort)
{
    if((*udpFdPtr = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 )
    {
        printf("socket create fail\n");
        return false;
    }
    int val = 1;
    if(setsockopt(*udpFdPtr, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))<0)
    {
        printf("setsockopt error");
        return false;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(udpPort);

    if(bind(*udpFdPtr, (struct sockaddr *) &serverAddr, 
                sizeof(serverAddr)) < 0)
    {
        printf("socket bind  fail\n");
        return false;
    }
    return true;
}

int main()
{
    vector<int> udpFds;
    vector<int> udpPorts;

    udpPorts.push_back(50101);
    udpPorts.push_back(50102);
    for (unsigned int i = 0; i < udpPorts.size(); i++)
    {
        int udpFd;
        if (!configUDP(&udpFd, udpPorts[i]))
        {
            printf("error cofig UDP\n");
            return -1;
        }
        udpFds.push_back(udpFd);
        printf("fd: %d - port: %d is added to udp vector\n",
                udpFd, udpPorts[i]);
    }


    fd_set read_set;
    FD_ZERO(&read_set);
    int maxfd1 = -1;
    for (unsigned int i = 0; i < udpFds.size(); i++)
    {
        FD_SET(udpFds[i], &read_set);
        maxfd1 = max(maxfd1, udpFds[i]);
    }
    printf("maxfd: %d\n", maxfd1);
    unsigned char databuf[DELPHI_UDP_PKT_MAX_SIZE];

    for(;;)
    {    
        struct timeval tv;
        tv.tv_sec = 1;
        int ret = select(maxfd1 + 1, &read_set, NULL, NULL, &tv);       
        if(ret == 0) 
        {
            printf("Select timeout\n");
            continue;
        }

        if(ret < 0) 
        {
            printf("select error\n");
            return -1;
        }

        for (unsigned int i = 0; i < udpFds.size(); i++)
        {
            int udpFd = udpFds[i];
            if(FD_ISSET(udpFd, &read_set))
            {
                memset(databuf, 0, sizeof(databuf));
                int numbytes = recvfrom(udpFd, databuf, DELPHI_UDP_PKT_MAX_SIZE,
                        0, NULL, NULL);
                if (numbytes < 0)
                {
                    printf("recvfrom UDP failure.");
                    return -1;
                }
                else 
                {
                    printf("recv %d bytes' UDP data from fd: %d - port: %d\n", 
                            numbytes, udpFd, udpPorts[i]);
                }
            }
        }
        usleep(1000);
    }
    return 0;
}

