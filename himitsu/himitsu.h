#include <openssl/md5.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>
#include "utils/safe_fgets.h"


void create_secrettext(void);
void set_passwd_tofile(char *file);
void decode_file(char *file);
char *hash_passwd(char *pwd, char *hashpwd);
int save_passwd(char *pwd, int pwd_len, int again);
int search_passwd(char *pwd, char *key);
void closing(void);
