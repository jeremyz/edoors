#ifndef _HELPER_H_
#define _HELPER_H_

#include "Eiotas.h"

#include <stdio.h>

#include <eina_log.h>
#include <eina_array.h>
#include <eina_stringshare.h>

#undef PRINTPTR
#ifdef __clang__
# define PRINTPTR(_p) (unsigned int)_p
#else
# define PRINTPTR(_p) (_p)
#endif

void check_cond(Eina_Bool cond, char *msg);
void check_str(char *s0, char *s1, char *msg);

void test_spin();
void test_particle();
void test_user_door();

#endif // _HELPER_H_
