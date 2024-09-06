#include <common.h>
#include <command.h>
#include <env.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int do_getfile(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    char cmd[256];
    const char *filename;
    const char *device;
    const char *part;
    const char *kernel_addr_r;

    if (argc != 4) {
        printf("Usage: getfile <filename> <device> <part>\n");
        return CMD_RET_USAGE;
    }

    filename = argv[1];
    device = argv[2];
    part = argv[3];

    kernel_addr_r = env_get("kernel_addr_r");
    if (!kernel_addr_r) {
        printf("Error: kernel_addr_r environment variable not set.\n");
        return CMD_RET_FAILURE;
    }

    snprintf(cmd, sizeof(cmd), "tftp %s %s && fatwrite %s %s %s %s ${filesize}",
             kernel_addr_r, filename, device, part, kernel_addr_r, filename);

    printf("Executing command: %s\n", cmd);

    if (run_command(cmd, 0) != 0) {
        printf("Error executing command.\n");
        return CMD_RET_FAILURE;
    }

    return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
    getfile,
    4,
    0,
    do_getfile,
    "Download file via TFTP and write to MMC",
    "<filename> <device> <part>"
);
