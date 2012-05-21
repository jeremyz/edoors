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

#include "eiotas_board.h"
#include "eiotas_private.h"

EAPI Eiotas_Board*
eiotas_board_add(const char* name, Eiotas_Room *parent, Eiotas_User_Bits *user_bits)
{
    // TODO
    return NULL;
}

void eiotas_board_free(Eiotas_Board *board)
{
    DBG("Door free 0x%X",board);
    // TODO
}

