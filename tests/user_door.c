
#include "helper.h"

typedef struct {
    char txt[32];
    int idx;
} Input;

static int free_called = 0;

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
    EINA_LOG_DOM_DBG(_edoors_log_dom,"free Input\n");
    free(input);
    free_called = 1;
}

static void input_show(Input *input)
{
    EINA_LOG_DOM_DBG(_edoors_log_dom,"Input [%d] %s\n",input->idx,input->txt);
}

static void input_receive(const Edoors_Door *door, Edoors_Particle *particle, Edoors_User_Data *data)
{
    EINA_LOG_DOM_DBG(_edoors_log_dom,"input_receive 0x%X\n",PRINTPTR(data));
}

void test_user_door()
{
    Edoors_Spin *dom0 = edoors_spin_add("dom0",10);

    Input *input = input_create("hello world");
    input_show(input);

    Edoors_User_Bits user_bits;

    user_bits.data = input;
    user_bits.free_fct = (Edoors_User_Data_Free)&input_free;
    user_bits.recv_fct = (Edoors_Receive_Particle)&input_receive;
    Edoors_Door *din0 = edoors_door_add("input0",&dom0->room,&user_bits);
    edoors_iota_show(&din0->iota); // edoors_iota_show((Edoors_Iota*)din0);

    edoors_spin_free(dom0);
    check_cond((free_called==1),"input_free not called");
}

