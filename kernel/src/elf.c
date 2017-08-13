#ifndef ELF_H
#include <elf.h>
#endif

#include <string.h>

elf32 elf_parse_kernel(multiboot_info *mbt, elf32 *elf) {
    elf32_Shdr *shdr = (elf32_Shdr*)mbt->u.elf_sec.addr;
    uint32_t shstrtab = shdr[mbt->u.elf_sec.shndx].sh_addr;
    for (uint32_t i = 0; i < mbt->u.elf_sec.num; i++) {
        const char *name = &((const char *)shdr[i].sh_name)[shstrtab];
        if (!strcmp(name, ".strtab")) {
            elf->strtab   = (const char *)shdr[i].sh_addr;
            elf->strtabsz = shdr[i].sh_size;
        }
        if (!strcmp(name, ".symtab")) {
            elf->symtab   = (elf32_Sym*)shdr[i].sh_addr;
            elf->symtabsz = shdr[i].sh_size;
        }
    }
    return *elf;
}
