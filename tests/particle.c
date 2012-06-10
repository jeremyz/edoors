
#include "helper.h"

void test_particle()
{
    void *p;
    Eina_Accessor       *acc;
    Edoors_Particle     *p0, *p1, *p2, *p3, *p4;

    Edoors_Spin *dom0 = edoors_spin_add("dom0",10);

    p0 = edoors_require_particle(dom0);

    check_cond(!edoors_particle_has_dst(p0),"should be no destination");

    edoors_particle_destinations_add(p0,"dom0/room0/door0?get");
    check_cond(edoors_particle_has_dst(p0),"should be a destination");
    edoors_particle_destinations_add(p0," dom0/room0/door0?get ");
    edoors_particle_destinations_add(p0,"    dom0/room0/door0?get   ");
    edoors_particle_destinations_add(p0,"dom0/room0/room1/doorx?get,door?get,dom0/room0/door0?get");
    edoors_particle_destinations_add(p0,"  dom0/room0/room1/doorx?get,door?get  ,  dom0/room0/door0?get ");
    edoors_particle_destinations_add(p0," dom0/room0/room1/doorx?get,door?get, dom0/room0/door0?get ");
    edoors_particle_destinations_add(p0," /suffix, ?suffix, prefix/ , prefix? , ,,  very/?wrong , very?wrong?too");

    acc = eina_array_accessor_new(p0->dsts);
    eina_accessor_data_get(acc,0,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,1,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,2,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,3,&p);
    check_str("dom0/room0/room1/doorx?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,4,&p);
    check_str("door?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,5,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,6,&p);
    check_str("dom0/room0/room1/doorx?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,7,&p);
    check_str("door?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,8,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,9,&p);
    check_str("dom0/room0/room1/doorx?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,10,&p);
    check_str("door?get",(char*)p,"edoors_particle_destinations_add");
    eina_accessor_data_get(acc,11,&p);
    check_str("dom0/room0/door0?get",(char*)p,"edoors_particle_destinations_add");
    check_cond((eina_accessor_data_get(acc,12,&p)==EINA_FALSE),"eina_accessor_data_get should fail");;

    edoors_particle_link_fields_set(p0," key2,key9  ,  key1,key10  ");
    acc = eina_array_accessor_new(p0->link_fields);
    eina_accessor_data_get(acc,0,&p);
    check_str("key2",(char*)p,"edoors_particle_link_fields_set");
    eina_accessor_data_get(acc,1,&p);
    check_str("key9",(char*)p,"edoors_particle_link_fields_set");
    eina_accessor_data_get(acc,2,&p);
    check_str("key1",(char*)p,"edoors_particle_link_fields_set");
    eina_accessor_data_get(acc,3,&p);
    check_str("key10",(char*)p,"edoors_particle_link_fields_set");
    check_cond((eina_accessor_data_get(acc,4,&p)==EINA_FALSE),"eina_accessor_data_get should fail");;


    check_cond((p0->link_value==NULL),"link_value should be NULL");

    edoors_particle_data_set(p0,"key0","val0");
    check_cond((p0->link_value==NULL),"link_value should be NULL");
    edoors_particle_data_set(p0,"key1","val1");
    check_str((char*)p0->link_value,"val1","link_value is wrong");
    edoors_particle_data_set(p0,"key2","val2");
    check_str((char*)p0->link_value,"val2val1","link_value is wrong");
    edoors_particle_data_set(p0,"key3","val3");
    check_str((char*)p0->link_value,"val2val1","link_value is wrong");

    if(strcmp(edoors_particle_data_get(p0,"key0"),"val0")!=0) fprintf(stderr,"ERROR\n");
    if(strcmp(edoors_particle_data_get(p0,"key1"),"val1")!=0) fprintf(stderr,"ERROR\n");
    if(strcmp(edoors_particle_data_get(p0,"key2"),"val2")!=0) fprintf(stderr,"ERROR\n");
    if(strcmp(edoors_particle_data_get(p0,"key3"),"val3")!=0) fprintf(stderr,"ERROR\n");

    edoors_particle_data_del(p0,"key0");
    if(edoors_particle_data_get(p0,"key0")!=NULL) fprintf(stderr,"ERROR\n");
    check_str((char*)p0->link_value,"val2val1","link_value is wrong");

    p1 = edoors_require_particle(dom0);
    check_cond(!edoors_particle_match(p0,p1),"link_value is not the same");
    edoors_particle_link_fields_set(p1," k0,k1");
    edoors_particle_data_set(p1,"k0","val2");
    edoors_particle_data_set(p1,"k1","val1");
    check_str((char*)p1->link_value,"val2val1","link_value is wrong");
    check_cond(edoors_particle_match(p0,p1),"link_value is the same");

    edoors_particle_data_del(p0,"key2");
    if(edoors_particle_data_get(p0,"key2")!=NULL) fprintf(stderr,"ERROR\n");
    check_str((char*)p0->link_value,"val1","link_value is wrong");
    edoors_particle_data_del(p0,"key1");
    if(edoors_particle_data_get(p0,"key1")!=NULL) fprintf(stderr,"ERROR\n");
    check_cond((p0->link_value==NULL),"link_value should be NULL");

    p2 = edoors_require_particle(dom0);

    edoors_particle_destinations_add(p2,"door");
    edoors_particle_split_dst(p2);
    check_cond((p2->cur_room==NULL),"room must be NULL");
    check_str((char*)p2->cur_door,"door","door is wrong");
    check_cond((p2->cur_action==NULL),"action must be NULL");

    edoors_particle_next_dst(p2);
    edoors_particle_destinations_add(p2,"doora?get");
    edoors_particle_split_dst(p2);
    check_str((char*)p2->cur_action,"get","action is wrong");
    check_str((char*)p2->cur_door,"doora","door is wrong");
    check_cond((p2->cur_room==NULL),"room must be NULL");

    edoors_particle_next_dst(p2);
    edoors_particle_destinations_add(p2,"room/room/door");
    edoors_particle_split_dst(p2);
    check_cond((p2->cur_action==NULL),"action must be NULL");
    check_str((char*)p2->cur_door,"door","door is wrong");
    check_str((char*)p2->cur_room,"room/room","room is wrong");

    edoors_particle_next_dst(p2);
    edoors_particle_destinations_add(p2,"room/room/door?get");
    edoors_particle_split_dst(p2);
    check_str((char*)p2->cur_action,"get","action is wrong");
    check_str((char*)p2->cur_door,"door","door is wrong");
    check_str((char*)p2->cur_room,"room/room","room is wrong");

    edoors_particle_next_dst(p2);
    edoors_particle_destinations_add(p2,"room/room/doorb?get");
    edoors_particle_split_dst(p2);
    check_str((char*)p2->cur_action,"get","action is wrong");
    check_str((char*)p2->cur_door,"doorb","door is wrong");
    check_str((char*)p2->cur_room,"room/room","room is wrong");

    p3 = edoors_require_particle(dom0);
    edoors_particle_destinations_add(p3,"dom0/room0/room1/doorx?get,door?get,dom0/room0/door0?get");
    edoors_particle_split_dst(p3);
    check_str((char*)p3->cur_action,"get","action is wrong");
    check_str((char*)p3->cur_door,"doorx","door is wrong");
    check_str((char*)p3->cur_room,"dom0/room0/room1","room is wrong");
    edoors_particle_destination_set(p3,"  room/door?got  nothing else matters ");
    edoors_particle_split_dst(p3);
    check_str((char*)p3->cur_action,"got","action is wrong");
    check_str((char*)p3->cur_door,"door","door is wrong");
    check_str((char*)p3->cur_room,"room","room is wrong");

    p4 = edoors_require_particle(dom0);
    edoors_particle_merge(p0,p1);
    edoors_particle_merge(p0,p2);
    edoors_particle_merge(p2,p3);
    edoors_particle_merge(p2,p4);

    edoors_particle_free(p0);

    edoors_spin_free(dom0);
}

