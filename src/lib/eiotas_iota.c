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

#ifdef HAVE_CONFIG_H
# include "eina_config.h"
#endif

#include "eiotas_iota.h"
#include "eiotas_private.h"

void eiotas_iota_init(Eiotas_Iota *iota, const char *name, Eiotas_Iota *parent, Eiotas_Type type)
{
    // TODO
}

void eiotas_iota_desinit(Eiotas_Iota *iota)
{
    // TODO
}

void eiotas_iota_free(Eiotas_Iota *iota)
{
    // TODO
}

EAPI void
eiotas_iota_show(Eiotas_Iota *iota)
{
    DBG("Iota(%d) 0x%X : %s (%s) [0x%X])",iota->type,iota,iota->name,iota->path,iota->parent);
}

