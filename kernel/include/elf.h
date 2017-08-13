#define ELF_H
#include <freestanding.h>

#ifndef MULTIBOOT_H
#include <multiboot.h>
#endif

#define EI_NIDENT 16

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry_addr;
    uint32_t e_ph_offset;
    uint32_t e_sh_offset;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} elf32_Ehdr;

typedef struct {
    uint32_t sh_name;
    uint32_t sh_type;
    uint32_t sh_flags;
    uint32_t sh_addr;
    uint32_t sh_offset;
    uint32_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint32_t sh_addralign;
    uint32_t sh_entsize;
} elf32_Shdr;

typedef struct {
    uint32_t st_name;
    uint32_t st_value_addr;
    uint32_t st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t st_shndx;
} elf32_Sym;

typedef struct {
    uint32_t r_offset_addr;
    uint32_t r_info;
} elf32_Rel;

typedef struct {
    uint32_t r_offset_addr;
    uint32_t r_info;
    int32_t r_addend;
} elf32_Rela;

typedef struct {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_v_addr;
    uint32_t p_p_addr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} elf32_Phdr;

typedef struct {
    elf32_Sym *symtab;
    uint32_t symtabsz;
    const char *strtab;
    uint32_t strtabsz;
} elf32;

elf32 elf_parse_kernel(multiboot_info *mbt, elf32 *elf);
