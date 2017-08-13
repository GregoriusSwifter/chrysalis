 vcxd#define SYSCALLS_H

#ifndef FS_H
#include "fs.h"
#endif

// FS
uinty __attribute__((overloadable)) fcreate(byte *category, uinty tagnum, byte **tags, byte *name);
uinty __attribute__((overloadable)) fcreate(byte *category, byte *name);
uinty __attribute__((overloadable)) fcreate(byte *name);
uinty __attribute__((overloadable)) fcreate(uinty fid);

void __attribute__((overloadable)) fdestroy(byte *category, uinty tagnum, byte **tags, byte *name);
void __attribute__((overloadable)) fdestroy(byte *category, byte *name);
void __attribute__((overloadable)) fdestroy(byte *name);
void __attribute__((overloadable)) fdestroy(uinty fid);

uinty fopen(byte *name, uint8 mode);
void fclose(uinty fid);
byte* fread(uinty fid);
uinty fwrite(uinty fid, byte* str);

