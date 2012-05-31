
#include "helper.h"

int main(int argc, char **argv)
{
    if(eiotas_init()==0) {
        return EXIT_FAILURE;
    }
    eina_log_domain_level_set("eiotas",EINA_LOG_LEVEL_ERR);
    EINA_LOG_DOM_INFO(_eiotas_log_dom,"Eiotas version %d.%d.%d",eiotas_version->major,eiotas_version->minor,eiotas_version->micro);

    test_spin();
    test_particle();

    return eiotas_shutdown();
}

