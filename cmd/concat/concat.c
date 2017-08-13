#include <liblocust.h>

void concat(uint64 f, byte *s) {
    byte buf[4096];
    int64 n;

    while ((n = read(f, buf, sizeof(buf))) > 0) {
        if (n != write(1, buf, n)) {
            die("write error copying %s: %r", s);
        }
    }
    if (n < 0) {
        die("error reading %s: %r", s);
    }
}

void main(uint64 arg_c, byte *arg_v[]) {
    uint64 f, i;

    arg_v_0 = "cat";
    if (arg_c == 1) {
        concat(0, "<stdin>");
    } else for (i=1; i<arg_c; i++) {
        if ((f = open(arg_v[i], OREAD)) < 0) {
            die("can't open %s: %r", argv[i]);
        } else {
            concat(f, arg_v[i]);
            close(f);
        }
    }
    exit(0);
}
