# ft_traceroute

## Features

## Requirements

Unix-like operating system (tested on macOS and Ubuntu)
C compiler (tested with gcc)

## Options

| Option        | Description            |
| ------------- | ---------------------- |
| <destination> | dns name or ip address |

## Usefull definition

### ICMP

ICMP stands for Internet Control Message Protocol. It is a protocol that is used by network devices to send error messages and operational information about network conditions. ICMP packets are small packets of data that are sent over the Internet to communicate error messages, status information, or to test connectivity between two network devices.

## TTL (Time To Live)

The TTL (Time To Live) is a value in the IP (Internet Protocol) header of a packet that specifies the maximum number of hops (routers) that the packet can traverse before it is discarded. Each router that the packet passes through decrements the TTL value by 1, and if the TTL reaches 0, the packet is discarded and an ICMP error message is sent back to the sender.

The TTL value is used to prevent packets from circulating indefinitely in the network, and to ensure that packets are delivered efficiently and reliably to their destination. The typical TTL value for a packet is 64, but it can be adjusted based on the network topology and the characteristics of the traffic.

## Usefull function

### getaddrinfo

the getaddrinfo function resolves an FQDN (Fully Qualified Domain Name) and returns the corresponding IP address(es) for that domain name. It works with both IPv4 and IPv6 addresses, and the results are returned in a linked list of addrinfo structures.

### inet_ntop

The inet_ntop() function is used to convert a binary IP address representation in network byte order to a human-readable string representation in dotted-decimal notation.

### inet_pton

The inet_pton() function is used to convert a human-readable string representation of an IP address to its binary form in network byte order.

### recvmsg

The recvmsg() function is used to receive a message from a socket. It allows you to receive both the message data and ancillary data (such as control messages).

The struct msghdr structure is used to describe a message that is sent or received using the sendmsg() or recvmsg() functions. It contains several fields that provide information about the message, including the source and destination addresses, the message data, and any ancillary data.

The msg_iov field of the struct msghdr structure is a pointer to an array of struct iovec structures that describe the message data. Each struct iovec structure contains a pointer to a buffer and the length of the buffer.

The struct iovec structure contains two fields: iov_base and iov_len. The iov_base field is a pointer to the buffer containing the data to be read or written, and iov_len is the size of the buffer in bytes.

## Resources

[socket man](https://man7.org/linux/man-pages/man2/socket.2.html)

[checksum](https://datatracker.ietf.org/doc/html/rfc1071)

[ip_icmp.h.](https://sites.uclouvain.be/SystInfo/usr/include/netinet/ip_icmp.h.html)
