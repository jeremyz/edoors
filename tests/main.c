#include "Eiotas.h"

#include <eina_log.h>
#include <stdio.h>

#undef PRINTPTR
#ifdef __clang__
# define PRINTPTR(_p) (unsigned int)_p
#else
# define PRINTPTR(_p) (_p)
#endif

typedef struct {
    char txt[32];
    int idx;
} Input;

static Input* input_create(char *txt)
{
    Input *input = (Input*)malloc(sizeof(Input));
    strncpy(input->txt,txt,32);
    input->txt[31] = '\0';
    input->idx = 0;
    return input;
}

static void input_free(Input *input)
{
    EINA_LOG_DOM_DBG(_eiotas_log_dom,"free Input\n");
    free(input);
}

static void input_show(Input *input)
{
    EINA_LOG_DOM_DBG(_eiotas_log_dom,"Input [%d] %s\n",input->idx,input->txt);
}

static void input_receive(const Eiotas_Door *door, Eiotas_Particle *particle, Eiotas_User_Data *data)
{
    EINA_LOG_DOM_DBG(_eiotas_log_dom,"input_receive 0x%X\n",PRINTPTR(data));
}

int main(int argc, char **argv)
{
    int i;
    Eiotas_Particle *p0, *p1, *p2, *p3, *p4;

    if(eiotas_init()>0) {
        return EXIT_FAILURE;
    }
    eina_log_domain_level_set("eiotas",EINA_LOG_LEVEL_DBG);
    EINA_LOG_DOM_DBG(_eiotas_log_dom,"Eiotas version %d.%d.%d",eiotas_version->major,eiotas_version->minor,eiotas_version->micro);

    Eiotas_Spin *dom0 = eiotas_spin_add("dom0",10);
    eiotas_iota_show((Eiotas_Iota*)dom0);

    Eiotas_Room *room = &dom0->room;
    char name[8];
    for(i=0; i<5; i++) {
        sprintf(name,"room%d",i);
        Eiotas_Room *tmp = eiotas_room_add(name,room);
        if(tmp!=NULL) {
            room = tmp;
            eiotas_iota_show((Eiotas_Iota*)room);   // MACROS
        }
    }
    room = eiotas_room_add("room0",&dom0->room);

    Input *input = input_create("hello world");
    input_show(input);

    Eiotas_User_Bits user_bits;

    user_bits.data = input;
    user_bits.free_fct = (Eiotas_User_Data_Free)&input_free;
    user_bits.recv_fct = (Eiotas_Receive_Particle)&input_receive;
    Eiotas_Door *din0 = eiotas_door_add("input0",&dom0->room,&user_bits);
    eiotas_iota_show(&din0->iota); // eiotas_iota_show((Eiotas_Iota*)din0);

    p0 = eiotas_require_particle(din0);
    p1 = eiotas_require_particle(din0);
    p2 = eiotas_require_particle(din0);
    p3 = eiotas_require_particle(din0);

    eiotas_release_particle(din0,p0);
    eiotas_release_particle(din0,p1);
    p4 = eiotas_require_particle(din0);
    if(p4!=p1) {
        fprintf(stderr,"Particle require fail\n");
    }
    eiotas_release_particle(din0,p4);

    /* eiotas_send_particle(din0,p2,EINA_FALSE); */
    /* eiotas_send_particle(din0,p3,EINA_TRUE); */

    eiotas_spin_free(dom0);

    return eiotas_shutdown();
}
