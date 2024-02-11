//
// Created by maylis on 04.02.24.
//
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <memory.h>

int main(void){
    const char *hostname = "www.google.de";
    const char *port = "80";

    struct addrinfo hints, *result, *p;

    // Initialize hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // AF_UNSPEC allows for both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;

    // Get address information
    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // Now 'result' points to a linked list of struct addrinfo containing address information

    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        // Get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // Convert the IP to a string and print it
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("IP Address: %s\n", ipstr);
    }
    // Free the memory allocated by getaddrinfo
    freeaddrinfo(result);

    return 0;
}



