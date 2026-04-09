# Socket_Programming

implemented ftp system using tcp sockets.
tcp sockets use sock_stream which are more reliable and the data packets arrive in order (unlike udp). it also ensures that all the packets get delivered

it is a client server model -> server listens for incoming connections and client initiates communication.

filenames are sent before the file data so that server knows how to name the file while saving it locally
