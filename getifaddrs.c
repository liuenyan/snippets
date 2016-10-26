/*
 * 获得网卡的信息，根据 getifaddrs(3) 的手册页编写
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/if_link.h>

int main()
{
    struct ifaddrs *ifap;
    int family, s;
    char host[NI_MAXHOST];
    char netmask[NI_MAXHOST];

    if(getifaddrs(&ifap) == -1)
    {
        perror("getifaddrs");
        return -1; 
    }

    for(struct ifaddrs *i = ifap; i != NULL; i=i->ifa_next)
    {
        if(!i->ifa_addr)
            continue;

        family = i->ifa_addr->sa_family; 
        printf("%s\t\t%s (%d)\n", i->ifa_name, \
                (family == AF_PACKET) ? "AF_PACKET" :\
                (family == AF_INET) ? "AF_INET" : \
                (family == AF_INET6) ? "AF_INET6": "???", \
                family);
        if (family == AF_INET || family == AF_INET6)
        {
            s = getnameinfo(i->ifa_addr, \
                    (family == AF_INET) ? sizeof(struct sockaddr_in) :\
                    sizeof(struct sockaddr_in6), \
                    host, NI_MAXHOST,
                    NULL, 0, NI_NUMERICHOST); 
            if(s != 0)
            {
                printf("getnameinfo() error: %s\n", gai_strerror(s));
                return -1;
            }

            s = getnameinfo(i->ifa_netmask, \
                    (family == AF_INET) ? sizeof(struct sockaddr_in) :\
                    sizeof(struct sockaddr_in6), \
                    netmask, NI_MAXHOST,
                    NULL, 0, NI_NUMERICHOST); 
            if(s != 0)
            {
                printf("getnameinfo() error: %s\n", gai_strerror(s));
                return -1;
            }
            printf("\t\thost <%s>\n", host);
            printf("\t\tnetmask <%s>\n", netmask);
        }
        else if (family == AF_PACKET && i->ifa_data != NULL)
        {
            struct rtnl_link_stats *stats \
                = (struct rtnl_link_stats *)i->ifa_data;
            printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                    "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                    stats->tx_packets, stats->rx_packets,
                    stats->tx_bytes, stats->rx_bytes);
        }
    }

    freeifaddrs(ifap);
    return 0; 
}
