#include <common.h>
#include <command.h>

typedef struct {
    char *name;
    int maxargs;
    int repeatable;
    int (*cmd)(struct cmd_tbl_s *cmdtp, int flag, int argc, char *const argv[]);
    char *usage;
} cmd_tbl_t;

static int do_clear(struct cmd_tbl_s *cmdtp, int flag, int argc, char *const argv[])
{
    
    printf("\033[2J\033[H"); 

    return 0;
}

U_BOOT_CMD(
    clear, 1, 0, do_clear,
    "Clear screen",
    ""
);
