
#include "helper.h"

void test_spin()
{
    int i;
    Eiotas_Particle *p0, *p1, *p2;

    /* add spin */
    Eiotas_Spin *dom0 = eiotas_spin_add("dom0",10);
    eiotas_iota_show((Eiotas_Iota*)dom0);

    /* particle require/release */
    p0 = eiotas_spin_require_particle(dom0);
    p1 = eiotas_spin_require_particle(dom0);

    eiotas_spin_release_particle(dom0,p0);
    eiotas_spin_release_particle(dom0,p1);
    p2 = eiotas_spin_require_particle(dom0);
    check_cond((p2==p1),"Particle require fail\n");

    eiotas_release_particle(dom0,p2);

    /* particle send(sys) */
    p0 = eiotas_spin_require_particle(dom0);
    p1 = eiotas_spin_require_particle(dom0);
    eiotas_spin_send_particle(dom0,p0,EINA_FALSE);
    eiotas_spin_send_particle(dom0,p1,EINA_TRUE);

    /* add rooms */
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
    check_cond(room==NULL,"room0 should already exists");

    eiotas_spin_free(dom0);
}

