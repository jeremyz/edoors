/* EDOORS
 * Copyright (C) 2012 Jérémy Zurcher
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __EDOORS_PRIVATE_H__
#define __EDOORS_PRIVATE_H__

#ifdef HAVE_CONFIG_H
# include "edoors_config.h"
#endif
#include "edoors_main.h"
#include "edoors_iota.h"

#include <eina_log.h>
#undef EINA_LOG_DOMAIN_DEFAULT
#define EINA_LOG_DOMAIN_DEFAULT edoors_log_dom
#define EIOTA_LOG_DOMAIN "edoors"

#define EDOORS_MAX_VALUE_LENGTH 1024
#define EDOORS_MAX_PATH_LENGTH 256
#define EDOORS_MAX_ACTION_LENGTH 16

#define EDOORS_PATH_SEP '/'
#define EDOORS_FIELDS_SEP ','
#define EDOORS_ACTION_SEP '?'
#define EDOORS_PARTICLE_ARRAY_STEP 3

void edoors_iota_desinit(Edoors_Iota *iota);

int edoors_iota_init(Edoors_Iota *iota, const char *name, Edoors_Iota *parent, Edoors_Type type);

#undef PRINTPTR
#ifdef __clang__
# define PRINTPTR(_p) (unsigned int)_p
#else
# define PRINTPTR(_p) (_p)
#endif

#define CHECK_PARENT()                      \
    if(parent==NULL) {                      \
        ERR("NULL parent not allowed");     \
        return NULL;                        \
    }

#define STRINGSHARE_FREE(_st)           \
    if(_st) {                           \
        eina_stringshare_del(_st);      \
        _st = NULL;                     \
    }

#define BUILD_INSTANCE(_type,_x)                \
    _type *_x = (_type*)malloc(sizeof(_type));  \
    if(_x==NULL) {                              \
        ERR("malloc error");                    \
        return NULL;                            \
    }

#define INIT_IOTA(_iota,_name,_parent,_type)                            \
    if(edoors_iota_init(_iota,_name,(Edoors_Iota*)_parent,_type)) {     \
        return NULL;                                                    \
    }

#define ADD_TO_PARENT(_parent,_iota,_st_name)                                       \
    if(eina_hash_find(_parent->children,_iota->name)) {                             \
        ERR("%s %s already exists in %s",_st_name,_iota->name,parent->iota.path);   \
        edoors_iota_desinit(_iota);                                                 \
        return NULL;                                                                \
    }                                                                               \
    eina_hash_direct_add(_parent->children,_iota->name,_iota);

#define CHECK_USERBITS(_user_bits)                      \
    if(_user_bits->data==NULL) {                        \
        ERR("user_bits->data NULL is not allowed");     \
        return  NULL;                                   \
    }                                                   \
    if(_user_bits->free_fct==NULL) {                    \
        ERR("user_bits->free_fct NULL is not allowed"); \
        return  NULL;                                   \
    }                                                   \
    if(_user_bits->recv_fct==NULL) {                    \
        ERR("user_bits->recv_fct NULL is not allowed"); \
        return  NULL;                                   \
    }                                                   \

/* TODO  user_bits->start_fct; user_bits->stop_fct; user_bits->suspend_fct; user_bits->resume_fct; */

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_edoors_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_edoors_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_edoors_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_edoors_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_edoors_log_dom, __VA_ARGS__)

#endif // __EDOORS_PRIVATE_H__
