#include "../tests/test_wc_upload.h"
#include <dlfcn.h>

int main(int argc, char** argv)
{    
    void *wc_lib = dlopen(WCLIBNAME, RTLD_LAZY);
    if (!wc_lib)
    {
        fprintf(stderr, "failed to open lib %s\n", WCLIBNAME);
        return -1;
    }

    wc_t wc = dlsym(wc_lib, "wc");
    if (!wc)
    {
        fprintf(stderr, "failed to find symbols\n");
        return -1;
    }

    if (wc(argc, argv) == 0)
        printf("\nOk\n");
    else
        printf("\nFail\n");

    dlclose(wc_lib);
}