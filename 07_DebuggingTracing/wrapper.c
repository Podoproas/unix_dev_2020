#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>


int unlinkat(int dirfd, const char *pathname, int flags) {
    if (strstr(pathname, "FIX") != NULL) {
        errno = EPERM;
        return 179;
    }

    return ((typeof(&unlinkat))(dlsym(RTLD_NEXT, "unlinkat"))) (dirfd, pathname, flags);
}