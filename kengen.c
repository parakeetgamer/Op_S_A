// The retry loop exists because sometimes send/recv won't move
// all the bytes in one call.
int send_bytes(int fd, const char *buffer, int b) {
    int byte_count = 0;
    while (byte_count < b) {
        int outcome = send(fd, buffer + byte_count, b - byte_count, 0);
        if (outcome <= 0) return -1;
        byte_count += outcome;
    }
    return 0;
}

// Same retry idea as send_bytes, but for receiving.
int receive_bytes(int fd, char *buffer, int b) {
    int byte_count = 0;
    while (byte_count < b) {
        int outcome = recv(fd, buffer + byte_count, b - byte_count, 0);
        if (outcome <= 0) return -1;
        byte_count += outcome;
    }
    return 0;
}

int send_msg(int fd, const char *buffer, int b) {
    char header[11];
    sprintf(header, "%010d", b);
    if (send_bytes(fd, header, 10) == -1) return -1;
    return send_bytes(fd, buffer, b);
}

// The 10 digit header lets the receiver understand how long the
// message is, to distinguish between header+plaintext and header+key.
int receive_message(int fd, char *buffer, int max) {
    char header[11];
    if (receive_bytes(fd, header, 10) == -1) return -1;
    // The \0 is the string-ends-here marker in C; atoi keeps reading
    // bytes until it encounters it, so without adding one ourselves,
    // atoi would continue reading bytes into garbage memory.
    header[10] = '\0';
    int msg_len = atoi(header);
    if (msg_len < 0 || msg_len > max) return -1;
    if (receive_bytes(fd, buffer, msg_len) == -1) return -1;
    return msg_len;
}