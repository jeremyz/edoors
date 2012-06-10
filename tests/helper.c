
#include "helper.h"

void check_cond(Eina_Bool cond, char *msg) {
    if(!cond) {
        EINA_LOG_DOM_ERR(_edoors_log_dom,"%s",msg);
    }
}

void check_str(char *s0, char *s1, char *msg) {
    if(strcmp(s0,s1)!=0) {
        EINA_LOG_DOM_ERR(_edoors_log_dom,"%s => %s != %s\n",msg,s0,s1);
    }
}


