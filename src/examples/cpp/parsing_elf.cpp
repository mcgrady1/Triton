/*
**  $ ./parsing_elf.bin /usr/bin/id
**  ----------------------------------------------------------------------
**  Program Header
**  ----------------------------------------------------------------------
**        Type     Flags    Offset     Vaddr     Paddr    Filesz     Memsz
**           6         5        40    400040    400040       230       230
**           3         4       270    400270    400270        1c        1c
**           1         5         0    400000    400000      8004      8004
**           1         6      8e10    608e10    608e10       4c4       6f0
**           2         6      8e28    608e28    608e28       1d0       1d0
**           4         4       28c    40028c    40028c        20        20
**    6474e550         4      6ffc    406ffc    406ffc       28c       28c
**    6474e551         6         0         0         0         0         0
**    6474e552         4      8e10    608e10    608e10       1f0       1f0
**    65041580      2800         0         0         0         0         0
**  ----------------------------------------------------------------------
**  ------------------------------------------------------------------------------------------
**  Section Header
**  ------------------------------------------------------------------------------------------
**        Type     Flags    Offset      Addr      Size      Link      Info                Name
**           0         0         0         0         0         0         0
**           1         2       270    400270        1c         0         0             .interp
**           7         2       28c    40028c        20         0         0       .note.ABI-tag
**    6ffffff6         2       2b0    4002b0        60         4         0           .gnu.hash
**           b         2       310    400310       6f0         5         1             .dynsym
**           3         2       a00    400a00       2f8         0         0             .dynstr
**    6fffffff         2       cf8    400cf8        94         4         0        .gnu.version
**    6ffffffe         2       d90    400d90        60         5         1      .gnu.version_r
**           4         2       df0    400df0        90         4         0           .rela.dyn
**           4        42       e80    400e80       630         4         b           .rela.plt
**           1         6      14b0    4014b0        1a         0         0               .init
**           1         6      14d0    4014d0       430         0         0                .plt
**           1         6      1900    401900      4289         0         0               .text
**           1         6      5b8c    405b8c         9         0         0               .fini
**           1         2      5bc0    405bc0      143c         0         0             .rodata
**           1         2      6ffc    406ffc       28c         0         0       .eh_frame_hdr
**           1         2      7288    407288       d7c         0         0           .eh_frame
**           e         3      8e10    608e10         8         0         0         .init_array
**           f         3      8e18    608e18         8         0         0         .fini_array
**           1         3      8e20    608e20         8         0         0                .jcr
**           6         3      8e28    608e28       1d0         5         0            .dynamic
**           1         3      8ff8    608ff8         8         0         0                .got
**           1         3      9000    609000       228         0         0            .got.plt
**           1         3      9240    609240        94         0         0               .data
**           8         3      92d4    609300       200         0         0                .bss
**           1         0      92d4         0        10         0         0      .gnu_debuglink
**           3         0      92e4         0        eb         0         0           .shstrtab
**  ------------------------------------------------------------------------------------------
**  --------------------
**  Dynamic Table
**  --------------------
**         Tag     Value
**           1         1
**           c    4014b0
**           d    405b8c
**          19    608e10
**          1b         8
**          1a    608e18
**          1c         8
**    6ffffef5    4002b0
**           5    400a00
**           6    400310
**           a       2f8
**           b        18
**          15         0
**           3    609000
**           2       630
**          14         7
**          17    400e80
**           7    400df0
**           8        90
**           9        18
**    6ffffffe    400d90
**    6fffffff         1
**    6ffffff0    400cf8
**           0         0
**           0         0
**           0         0
**           0         0
**           0         0
**           0         0
**  --------------------
**  --------------------------------------------------------------------------------
**  Symbols Table
**  --------------------------------------------------------------------------------
**        Info     Other     Shndx     Value      Size                          Name
**          12         0         0         0         0                 __assert_fail
**          12         0         0         0         0                 __ctype_b_loc
**          12         0         0         0         0        __ctype_get_mb_cur_max
**          12         0         0         0         0                  __cxa_atexit
**          12         0         0         0         0              __errno_location
**          12         0         0         0         0                    __fpending
**          12         0         0         0         0                 __fprintf_chk
**          12         0         0         0         0                    __freading
**          20         0         0         0         0                __gmon_start__
**          12         0         0         0         0             __libc_start_main
**          12         0         0         0         0                    __overflow
**          12         0         0         0         0                  __printf_chk
**          11         0        18    609300         8                    __progname
**          11         0        18    609318         8               __progname_full
**          12         0         0         0         0              __stack_chk_fail
**          12         0         0         0         0                       __uflow
**          12         0         0         0         0                         _exit
**          12         0         0         0         0                         abort
**          12         0         0         0         0                bindtextdomain
**          12         0         0         0         0                        calloc
**          12         0         0         0         0                         close
**          12         0         0         0         0                     dcgettext
**          12         0         0         0         0                      endgrent
**          12         0         0         0         0                      endpwent
**          12         0         0         0         0                         error
**          12         0         0         0         0                          exit
**          12         0         0         0         0                        fclose
**          12         0         0         0         0                        fdopen
**          12         0         0         0         0                        fflush
**          12         0         0         0         0                        fileno
**          12         0         0         0         0                fputs_unlocked
**          12         0         0         0         0                          free
**          12         0         0         0         0                        fscanf
**          12         0         0         0         0                        fseeko
**          12         0         0         0         0                        fwrite
**          12         0         0         0         0                       getegid
**          12         0         0         0         0                        getenv
**          12         0         0         0         0                       geteuid
**          12         0         0         0         0                        getgid
**          12         0         0         0         0                      getgrgid
**          12         0         0         0         0                      getgrnam
**          12         0         0         0         0                  getgrouplist
**          12         0         0         0         0                     getgroups
**          12         0         0         0         0                   getopt_long
**          12         0         0         0         0                      getpwnam
**          12         0         0         0         0                      getpwuid
**          12         0         0         0         0                        getuid
**          12         0         0         0         0                      iswprint
**          12         0         0         0         0                         lseek
**          12         0         0         0         0                        malloc
**          12         0         0         0         0                       mbrtowc
**          12         0         0         0         0                       mbsinit
**          12         0         0         0         0                        memcmp
**          12         0         0         0         0                        memcpy
**          12         0         0         0         0                        memset
**          12         0         0         0         0                   nl_langinfo
**          12         0         0         0         0                          open
**          11         0        18    609310         4                        optind
**          21         0        18    609318         8       program_invocation_name
**          21         0        18    609300         8 program_invocation_short_name
**          12         0         0         0         0                       realloc
**          12         0         0         0         0                     setlocale
**          11         0        18    609320         8                        stderr
**          11         0        18    609308         8                        stdout
**          12         0         0         0         0                        strchr
**          12         0         0         0         0                        strcmp
**          12         0         0         0         0                        strcpy
**          12         0         0         0         0                        strlen
**          12         0         0         0         0                       strncmp
**          12         0         0         0         0                       strrchr
**          12         0         0         0         0                       strtoul
**          12         0         0         0         0                    textdomain
**          12         0         0         0         0                        ungetc
**  --------------------------------------------------------------------------------
*/

#include <iostream>
#include <triton/api.hpp>
#include <triton/abstractBinary.hpp>



int main(int ac, const char *av[]) {
  triton::format::AbstractBinary binary;

  if (ac != 2)
    return -1;

  binary.loadBinary(av[1]);

  auto elf = binary.getElf();

  std::cout << "----------------------------------------------------------------------" << std::endl;
  std::cout << "Program Header" << std::endl;
  std::cout << "----------------------------------------------------------------------" << std::endl;
  std::cout << std::hex;
  std::cout << std::setw(10) << "Type";
  std::cout << std::setw(10) << "Flags";
  std::cout << std::setw(10) << "Offset";
  std::cout << std::setw(10) << "Vaddr";
  std::cout << std::setw(10) << "Paddr";
  std::cout << std::setw(10) << "Filesz";
  std::cout << std::setw(10) << "Memsz";
  std::cout << std::endl;
  for (auto it = elf->getProgramHeaders().begin(); it != elf->getProgramHeaders().end(); it++) {
    std::cout << std::setw(10) << it->getType();
    std::cout << std::setw(10) << it->getFlags();
    std::cout << std::setw(10) << it->getOffset();
    std::cout << std::setw(10) << it->getVaddr();
    std::cout << std::setw(10) << it->getPaddr();
    std::cout << std::setw(10) << it->getFilesz();
    std::cout << std::setw(10) << it->getMemsz();
    std::cout << std::endl;
  }
  std::cout << "----------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;

  std::cout << "------------------------------------------------------------------------------------------" << std::endl;
  std::cout << "Section Header" << std::endl;
  std::cout << "------------------------------------------------------------------------------------------" << std::endl;
  std::cout << std::hex;
  std::cout << std::setw(10) << "Type";
  std::cout << std::setw(10) << "Flags";
  std::cout << std::setw(10) << "Offset";
  std::cout << std::setw(10) << "Addr";
  std::cout << std::setw(10) << "Size";
  std::cout << std::setw(10) << "Link";
  std::cout << std::setw(10) << "Info";
  std::cout << std::setw(20) << "Name";
  std::cout << std::endl;
  for (auto it = elf->getSectionHeaders().begin(); it != elf->getSectionHeaders().end(); it++) {
    std::cout << std::setw(10) << it->getType();
    std::cout << std::setw(10) << it->getFlags();
    std::cout << std::setw(10) << it->getOffset();
    std::cout << std::setw(10) << it->getAddr();
    std::cout << std::setw(10) << it->getSize();
    std::cout << std::setw(10) << it->getLink();
    std::cout << std::setw(10) << it->getInfo();
    std::cout << std::setw(20) << it->getName();
    std::cout << std::endl;
  }
  if (elf->getSectionHeaders().size() == 0)
    std::cout << std::endl << std::setw(55) << "<section header empty!>" << std::endl << std::endl;
  std::cout << "------------------------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;

  std::cout << "--------------------" << std::endl;
  std::cout << "Dynamic Table" << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << std::hex;
  std::cout << std::setw(10) << "Tag";
  std::cout << std::setw(10) << "Value";
  std::cout << std::endl;
  for (auto it = elf->getDynamicTable().begin(); it != elf->getDynamicTable().end(); it++) {
    std::cout << std::setw(10) << it->getTag();
    std::cout << std::setw(10) << it->getValue();
    std::cout << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  std::cout << std::endl;

  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << "Symbols Table" << std::endl;
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << std::hex;
  std::cout << std::setw(10) << "Info";
  std::cout << std::setw(10) << "Other";
  std::cout << std::setw(10) << "Shndx";
  std::cout << std::setw(10) << "Value";
  std::cout << std::setw(10) << "Size";
  std::cout << std::setw(30) << "Name";
  std::cout << std::endl;
  for (auto it = elf->getSymbolsTable().begin(); it != elf->getSymbolsTable().end(); it++) {
    std::cout << std::setw(10) << static_cast<unsigned int>(it->second.getInfo());
    std::cout << std::setw(10) << static_cast<unsigned int>(it->second.getOther());
    std::cout << std::setw(10) << it->second.getShndx();
    std::cout << std::setw(10) << it->second.getValue();
    std::cout << std::setw(10) << it->second.getSize();
    std::cout << std::setw(30) << it->second.getName();
    std::cout << std::endl;
  }
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;

  return 0;
}

