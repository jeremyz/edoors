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

#ifndef __EIOTAS_USERBITS_H__
#define __EIOTAS_USERBITS_H__

#include "eiotas_iota.h"
#include "eiotas_particle.h"

typedef struct _Eiotas_User_Bits Eiotas_User_Bits;

typedef void Eiotas_User_Data;
typedef void (*Eiotas_User_Data_Free)(Eiotas_User_Data*);
typedef void (*Eiotas_Receive_Particle)(Eiotas_Iota *iota, Eiotas_Particle *particle, Eiotas_User_Data *data);
typedef void (*Eiotas_Start)(Eiotas_Iota *iota, Eiotas_User_Data *data);
typedef void (*Eiotas_Suspend)(Eiotas_Iota *iota, Eiotas_User_Data *data);
typedef void (*Eiotas_Resume)(Eiotas_Iota *iota, Eiotas_User_Data *data);
typedef void (*Eiotas_Stop)(Eiotas_Iota *iota, Eiotas_User_Data *data);

struct _Eiotas_User_Bits {
    Eiotas_User_Data *data;
    Eiotas_User_Data_Free free_fct;
    Eiotas_Receive_Particle recv_fct;
    Eiotas_Start start_fct;
    Eiotas_Stop stop_fct;
    Eiotas_Suspend suspend_fct;
    Eiotas_Resume resume_fct;
};

#endif // __EIOTAS_USERBITS_H__
