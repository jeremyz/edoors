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

#include "edoors_board.h"
#include "edoors_private.h"

EAPI Edoors_Board* edoors_board_add(const char* name, const Edoors_Room *parent, Edoors_User_Bits *user_bits)
{
    // TODO
    return NULL;
}

void edoors_board_free(Edoors_Board *board)
{
    DBG("Door free 0x%X",PRINTPTR(board));
    // TODO
}

