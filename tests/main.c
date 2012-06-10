
#include "helper.h"

int main(int argc, char **argv)
{
    if(edoors_init()==0) {
        return EXIT_FAILURE;
    }
    eina_log_domain_level_set("edoors",EINA_LOG_LEVEL_ERR);
    EINA_LOG_DOM_INFO(_edoors_log_dom,"Edoors version %d.%d.%d",edoors_version->major,edoors_version->minor,edoors_version->micro);

    test_spin();
    test_particle();

    return edoors_shutdown();
}

