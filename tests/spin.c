
#include "helper.h"

void test_spin()
{
    int i;
    Edoors_Particle *p0, *p1, *p2;

    /* add spin */
    Edoors_Spin *dom0 = edoors_spin_add("dom0",10);
    edoors_iota_show((Edoors_Iota*)dom0);

    /* particle require/release */
    p0 = edoors_spin_require_particle(dom0);
    p1 = edoors_spin_require_particle(dom0);

    edoors_spin_release_particle(dom0,p0);
    edoors_spin_release_particle(dom0,p1);
    p2 = edoors_spin_require_particle(dom0);
    check_cond((p2==p1),"Particle require fail\n");

    edoors_release_particle(dom0,p2);

    /* particle send(sys) */
    p0 = edoors_spin_require_particle(dom0);
    p1 = edoors_spin_require_particle(dom0);
    edoors_spin_send_particle(dom0,p0,EINA_FALSE);
    edoors_spin_send_particle(dom0,p1,EINA_TRUE);

    /* add rooms */
    Edoors_Room *room = &dom0->room;
    char name[8];
    for(i=0; i<5; i++) {
        sprintf(name,"room%d",i);
        Edoors_Room *tmp = edoors_room_add(name,room);
        if(tmp!=NULL) {
            room = tmp;
            edoors_iota_show((Edoors_Iota*)room);   // MACROS
        }
    }
    room = edoors_room_add("room0",&dom0->room);
    check_cond(room==NULL,"room0 should already exists");

    edoors_spin_free(dom0);
}

