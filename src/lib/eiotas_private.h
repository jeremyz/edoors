/* EIOTAS
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

#ifndef __EIOTAS_PRIVATE_H__
#define __EIOTAS_PRIVATE_H__

#include "eiotas_config.h"
#include "eiotas_main.h"

#include <eina_log.h>
#undef EINA_LOG_DOMAIN_DEFAULT
#define EINA_LOG_DOMAIN_DEFAULT eiotas_log_dom
#define EIOTA_LOG_DOMAIN "eiotas"

#define MAX_PATH_LENGTH 256
#define PATH_SEP '/'

#define CHECK_PARENT()                              \
    if(parent==NULL) {                              \
        EINA_LOG_ERR("NULL parent not allowed");    \
        return NULL;                                \
    }

#define BUILD_INSTANCE(_type,_x)                    \
    _type *_x = (_type*)malloc(sizeof(_type));      \
    if(_x==NULL) {                                  \
        EINA_LOG_ERR("malloc error");               \
        return NULL;                                \
    }

#ifdef CRITICAL
#undef CRITICAL
#endif
#define CRITICAL(...) EINA_LOG_DOM_CRIT(_eiotas_log_dom, __VA_ARGS__)

#ifdef ERR
#undef ERR
#endif
#define ERR(...) EINA_LOG_DOM_ERR(_eiotas_log_dom, __VA_ARGS__)

#ifdef WRN
#undef WRN
#endif
#define WRN(...) EINA_LOG_DOM_WARN(_eiotas_log_dom, __VA_ARGS__)

#ifdef INF
#undef INF
#endif
#define INF(...) EINA_LOG_DOM_INFO(_eiotas_log_dom, __VA_ARGS__)

#ifdef DBG
#undef DBG
#endif
#define DBG(...) EINA_LOG_DOM_DBG(_eiotas_log_dom, __VA_ARGS__)

#endif // __EIOTAS_PRIVATE_H__
