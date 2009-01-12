/*
 *  Copyright � 2006-2009 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

/* --------------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "bgdcore.h"
#include "bgdrtm.h"

#include "dcb.h"

#include "libgrbase.h"

/* --------------------------------------------------------------------------- */

#define CHARWIDTH 6

/* --------------------------------------------------------------------------- */

static char sysfont[][8][16] =
{
    {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXXX " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "      " }
    }, {
        { "XXXXX " },
        { "X     " },
        { "X     " },
        { "XXXX  " },
        { "X     " },
        { "X     " },
        { "XXXXX " },
        { "      " }
    }, {
        { "XXXXX " },
        { "X     " },
        { "X     " },
        { "XXXX  " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X     " },
        { "X  XX " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "XXXXX " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "XXXXX " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "XXXXX " },
        { "      " }
    }, {
        { "    X " },
        { "    X " },
        { "    X " },
        { "    X " },
        { "    X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "X   X " },
        { "X  X  " },
        { "X X   " },
        { "XX    " },
        { "X X   " },
        { "X  X  " },
        { "X   X " },
        { "      " }
    }, {
        { "X     " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "XXXXX " },
        { "      " }
    }, {
        { "X   X " },
        { "XX XX " },
        { "X X X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "XX  X " },
        { "XX  X " },
        { "X X X " },
        { "X X X " },
        { "X X X " },
        { "X  XX " },
        { "X  XX " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X X X " },
        { "XX  X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "X X   " },
        { "X  X  " },
        { "X   X " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X     " },
        { " XXX  " },
        { "    X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXXX " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " X X  " },
        { " X X  " },
        { "  X   " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X X X " },
        { "X X X " },
        { " X X  " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { " X X  " },
        { "  X   " },
        { " X X  " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "X   X " },
        { "X   X " },
        { " X X  " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "      " }
    }, {
        { "XXXXX " },
        { "    X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "X     " },
        { "XXXXX " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "  X   " },
        { " XX   " },
        { "X X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "XXXXX " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "    X " },
        { "  XX  " },
        { " X    " },
        { "X     " },
        { "XXXXX " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "    X " },
        { " XXX  " },
        { "    X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "    X " },
        { "X   X " },
        { "X   X " },
        { "XXXXX " },
        { "    X " },
        { "    X " },
        { "    X " },
        { "      " }
    }, {
        { "XXXXX " },
        { "X     " },
        { "XXXX  " },
        { "    X " },
        { "    X " },
        { "    X " },
        { "XXXX  " },
        { "      " }
    }, {
        { " XXX  " },
        { "X     " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXXX " },
        { "    X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "X     " },
        { "X     " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXXX " },
        { "    X " },
        { " XXX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "  XX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "  XX  " },
        { "      " },
        { "      " },
        { "  XX  " },
        { "      " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "  XX  " },
        { "      " },
        { "  XX  " },
        { " XX   " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { " XXXX " },
        { "      " },
        { " XXXX " },
        { "      " },
        { "      " }
    }, {
        { "XX    " },
        { "X   X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "X   X " },
        { "   XX " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXX  " },
        { "    X " },
        { " XXXX " },
        { "X   X " },
        { " XXXX " },
        { "      " }
    }, {
        { "X     " },
        { "X     " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXX  " },
        { "X   X " },
        { "X     " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "    X " },
        { "    X " },
        { " XXXX " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXXX " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXX  " },
        { "X   X " },
        { "XXXX  " },
        { "X     " },
        { " XXXX " },
        { "      " }
    }, {
        { " XXX  " },
        { "X   X " },
        { "X     " },
        { "XXX   " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXXX " },
        { "X   X " },
        { "X   X " },
        { " XXXX " },
        { "    X " },
        { " XXX  " }
    }, {
        { "X     " },
        { "X     " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "      " },
        { "  X   " },
        { "      " },
        { " XX   " },
        { "  X   " },
        { "  X   " },
        { " XXX  " },
        { "      " }
    }, {
        { "      " },
        { "    X " },
        { "      " },
        { "  XXX " },
        { "    X " },
        { "    X " },
        { "X   X " },
        { " XXX  " }
    }, {
        { "X     " },
        { "X     " },
        { "X     " },
        { "X  X  " },
        { "XXX   " },
        { "X  X  " },
        { "X   X " },
        { "      " }
    }, {
        { " XX   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "XXXXX " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "XX X  " },
        { "X X X " },
        { "X X X " },
        { "X X X " },
        { "X X X " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "XXXX  " },
        { "X     " },
        { "X     " }
    }, {
        { "      " },
        { "      " },
        { " XXXX " },
        { "X   X " },
        { "X   X " },
        { " XXXX " },
        { "    X " },
        { "    X " }
    }, {
        { "      " },
        { "      " },
        { "X XX  " },
        { "XX  X " },
        { "X     " },
        { "X     " },
        { "X     " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { " XXX  " },
        { "X     " },
        { " XXX  " },
        { "    X " },
        { "XXXX  " },
        { "      " }
    }, {
        { " X    " },
        { " X    " },
        { "XXXX  " },
        { " X    " },
        { " X    " },
        { " X  X " },
        { "  XX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " X X  " },
        { "  X   " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "X   X " },
        { "X   X " },
        { "X X X " },
        { "X X X " },
        { " X X  " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "X   X " },
        { " X X  " },
        { "  X   " },
        { " X X  " },
        { "X   X " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXXX " },
        { "    X " },
        { "XXXX  " }
    }, {
        { "      " },
        { "      " },
        { "XXXXX " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "XXXXX " },
        { "      " }
    }, {
        { " XXX  " },
        { " X    " },
        { " X    " },
        { " X    " },
        { " X    " },
        { " X    " },
        { " XXX  " },
        { "      " }
    }, {
        { " XXX  " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { " XXX  " },
        { "      " }
    }, {
        { "  XX  " },
        { " X    " },
        { " X    " },
        { " X    " },
        { " X    " },
        { " X    " },
        { "  XX  " },
        { "      " }
    }, {
        { " XX   " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { "   X  " },
        { " XX   " },
        { "      " }
    }, {
        { "  XX  " },
        { " X    " },
        { " X    " },
        { "X     " },
        { " X    " },
        { " X    " },
        { "  XX  " },
        { "      " }
    }, {
        { " XX   " },
        { "   X  " },
        { "   X  " },
        { "    X " },
        { "   X  " },
        { "   X  " },
        { " XX   " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "XXXXX " },
        { "      " },
        { "      " },
        { "      " }
    }, {
        { " X    " },
        { "  X   " },
        { "   X  " },
        { "    X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "      " }
    }, {
        { "    X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "  X   " },
        { "   X  " },
        { "    X " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "XXXXX " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "   X  " },
        { " XX   " }
    }, {
        { "      " },
        { "X     " },
        { " X    " },
        { "  X   " },
        { "   X  " },
        { "    X " },
        { "     X" },
        { "      " }
    }, {
        { "      " },
        { "     X" },
        { "    X " },
        { "   X  " },
        { "  X   " },
        { " X    " },
        { "X     " },
        { "      " }
    }, {
        { "      " },
        { "      " },
        { "  X   " },
        { "  X   " },
        { "XXXXX " },
        { "  X   " },
        { "  X   " },
        { "      " }
    }, {
        { "      " },
        { " X X  " },
        { "  X   " },
        { "XXXXX " },
        { "  X   " },
        { " X X  " },
        { "      " },
        { "      " }
    }, {
        { "      " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "      " },
        { "  X   " },
        { "      " }
    }, {
        { "      " },
        { "  X   " },
        { "      " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "      " }
    }, {
        { "      " },
        { " XXX  " },
        { "X   X " },
        { "   X  " },
        { "  X   " },
        { "      " },
        { "  X   " },
        { "      " }
    }, {
        { "      " },
        { "  X   " },
        { "      " },
        { "  X   " },
        { " X    " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { " X X  " },
        { " X X  " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "      " }
    }, {
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  XXXX" },
        { "  X   " },
        { "  X   " },
        { "  X   " }
    }, {
        { "      " },
        { "      " },
        { "      " },
        { "      " },
        { "XXXXXX" },
        { "      " },
        { "      " },
        { "      " }
    }, {
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "  X   " }
    }, {
        { "   X  " },
        { "  X   " },
        { " XXX  " },
        { "X   X " },
        { "XXXXX " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "XXXXX " },
        { "X     " },
        { "XXXX  " },
        { "X     " },
        { "XXXXX " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "XXXXX " },
        { "  X   " },
        { "  X   " },
        { "  X   " },
        { "XXXXX " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { " XXX  " },
        { "      " },
        { "XX  X " },
        { "XX  X " },
        { "X X X " },
        { "X  XX " },
        { "X  XX " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { " XXX  " },
        { "    X " },
        { " XXXX " },
        { "X   X " },
        { " XXXX " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { " XXX  " },
        { "X   X " },
        { "XXXX  " },
        { "X     " },
        { " XXXX " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "      " },
        { " XX   " },
        { "  X   " },
        { "  X   " },
        { " XXX  " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { " XXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "   X  " },
        { "  X   " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { " XXX  " },
        { "      " }
    }, {
        { "XXXX  " },
        { "      " },
        { "XXXX  " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "X   X " },
        { "      " }
    }
};

/* --------------------------------------------------------------------------- */

void systext_color( int cfg, int cbg );
void systext_puts( GRAPH * map, int x, int y, uint8_t * str, int len );

/* --------------------------------------------------------------------------- */

static uint8_t * letters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:;=%abcdefghijklmnopqrstuvwxyz[](){}-><_,\\/+*!�?�\"'\x01\x02\x03������������" ;

static int fg = 0, bg = 0;

/* --------------------------------------------------------------------------- */

void systext_putchar( GRAPH * map, int ox, int oy, uint8_t c )
{
    int x, y ;
    static int corr[256] ;
    static int corr_init = 0 ;

    if ( !corr_init )
    {
        uint8_t * ptr ;

        for ( ptr = letters; *ptr; ptr++ )
            corr[*ptr] = corr_init++ ;
    }

#define PUTSYS(TYPE)                                            \
    for (y = oy ; y < oy+8 ; y++)                               \
    {                                                           \
        TYPE * ptr; uint8_t * cptr ;                            \
        if (y < 0 || y >= (int)map->height) continue ;          \
        ptr = (TYPE *)((uint8_t*)map->data + map->pitch*y) ;    \
        ptr += ox;                                              \
        cptr = (uint8_t*)sysfont[c][y-oy];                      \
        for (x = ox ; x < ox+6 ; x++, cptr++)                   \
        {                                                       \
            if (x < 0 || x >= (int)map->width)                  \
            {                                                   \
                ptr++ ;                                         \
                continue ;                                      \
            }                                                   \
            if (*cptr == 'X')                                   \
                *ptr++ = fg ;                                   \
            else                                                \
                if (bg)                                         \
                    *ptr++ = bg ;                               \
                else                                            \
                    ptr++ ;                                     \
        }                                                       \
    }

    switch ( map->format->depth )
    {
        case 8 :
        {
            c = corr[c] ;
            PUTSYS( uint8_t )
        }
        break;
        case 16 :
        {
            c = corr[c] ;
            PUTSYS( uint16_t )
        }
        break;
        case 32 :
        {
            c = corr[c] ;
            PUTSYS( uint32_t )
        }
    }

#undef PUTSYS
}

/* --------------------------------------------------------------------------- */

static int text_colors[] =
{
    0x000000, 0x0000C0, 0xC00000, 0xC000C0, 0x00C000, 0x00C0C0, 0xC0C000, 0xC0C0C0,
    0x808080, 0x0000FF, 0xFF0000, 0xFF00FF, 0x00FF00, 0x00FFFF, 0xFFFF00, 0xFFFFFF
} ;

/* --------------------------------------------------------------------------- */

void systext_puts( GRAPH * map, int x, int y, uint8_t * str, int len )
{
    while ( *str && len )
    {
        if ( *str == ( uint8_t )'�' )
        {
            uint8_t color = 0 ;
            str++ ;
            if ( isdigit( *str ) ) color = *str++ - '0' ;
            if ( isdigit( *str ) ) color = color * 10 + *str++ - '0' ;

            if ( color < 32 )
            {
                if ( color > 15 )
                    systext_color( -1, text_colors[color - 16] ) ;
                else
                    systext_color( text_colors[color], -1 ) ;
            }
            if ( !*str ) break ;
            continue;
        }
        systext_putchar( map, x, y, *str++ ) ;
        x += CHARWIDTH ;
        len--;
    }

    while ( len-- > 0 )
    {
        systext_putchar( map, x, y, ' ' ) ;
        x += CHARWIDTH ;
    }
}

/* --------------------------------------------------------------------------- */

void systext_color( int cfg, int cbg )
{
    if ( !cbg ) bg = 0;
    if ( sys_pixel_format->depth == 8 )
    {
        if ( !trans_table_updated ) gr_make_trans_table() ;

        fg = gr_find_nearest_color((( cfg & 0xFF0000 ) >> 16 ), (( cfg & 0x00FF00 ) >>  8 ), ( cfg & 0x0000FF ) ) ;
        if ( cbg > 0 ) bg = gr_find_nearest_color((( cbg & 0xFF0000 ) >> 16 ), (( cbg & 0x00FF00 ) >>  8 ), ( cbg & 0x0000FF ) ) ;
    }
    else
    {
        fg = gr_rgb((( cfg & 0xFF0000 ) >> 16 ), (( cfg & 0x00FF00 ) >>  8 ), ( cfg & 0x0000FF ) ) ;
        if ( cbg > 0 ) bg = gr_rgb((( cbg & 0xFF0000 ) >> 16 ), (( cbg & 0x00FF00 ) >>  8 ), ( cbg & 0x0000FF ) ) ;
    }
}

/* --------------------------------------------------------------------------- */
