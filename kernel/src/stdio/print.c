#include <stdio.h>

#if defined(__SWARM_OS__)
#include <k/tty.h>
#endif

void print(char const * data, uint32_t length) {
    uint32_t i=0;
    while (length-->0) {
#if defined(__SWARM_OS__)
        terminal_write(data[i++]);
#else
        // TODO: Implement stdio and the write system call.
#endif
    }
    return;
}

typedef
struct IOchunk
{
    void    *addr;
    ulong   len;
} IOchunk;

static long write(int fd, array a) {
    int i;
    long tot;
    char *buf, *p;

    tot = 0;
    for(i=0; i<nio; i++)
        tot += io[i].len;
    buf = malloc(tot);
    if(buf == nil)
        return -1;

    p = buf;
    for(i=0; i<nio; i++){
        memmove(p, io->addr, io->len);
        p += io->len;
        io++;
    }

    tot = pwrite(fd, buf, tot, offset);

    free(buf);
    return tot;
}

long writev(int fd, IOchunk *io, int nio) {
    return iowritev(fd, io, nio, -1LL);
}

long pwritev(int fd, IOchunk *io, int nio, vlong off) {
    return iowritev(fd, io, nio, off);
}

