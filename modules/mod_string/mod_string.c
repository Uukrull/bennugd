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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"

#include "files.h"
#include "xstrings.h"

/* STRINGS */

/** LEN (STRING SOURCE)
 *  Returns the size of a string
 */

static int modstring_strlen( INSTANCE * my, int * params )
{
    const char * str = string_get( params[0] ) ;
    int r = str ? strlen( str ) : 0 ;
    string_discard( params[0] ) ;
    return r ;
}

/** STRING UCASE (STRING SOURCE)
 *  Converts a string to upper-case
 */

static int modstring_strupper( INSTANCE * my, int * params )
{
    int r = string_ucase( params[0] ) ;
    string_discard( params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** STRING LCASE (STRING SOURCE)
 *  Converts a string to lower-case
 */

static int modstring_strlower( INSTANCE * my, int * params )
{
    int r = string_lcase( params[0] ) ;
    string_discard( params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** STRCASECMP (STRING S1, STRING S2)
 *  Compares two strings, case-insensitive
 */

static int modstring_strcasecmp( INSTANCE * my, int * params )
{
    int r = string_casecmp( params[0], params[1] ) ;
    string_discard( params[0] ) ;
    string_discard( params[1] ) ;
    return r ;
}

/** SUBSTR (STRING SOURCE, INT FIRST_CHARACTER, INT COUNT)
 *  Returns part of a given string, starting at the given character position
 *  and returning a string limited to COUNT characters
 */

static int modstring_substr( INSTANCE * my, int * params )
{
    int r = string_substr( params[0], params[1], ( params[2] < 0 ) ? ( params[2] - 1 ) : params[2] ) ;
    string_discard( params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** SUBSTR (STRING SOURCE, INT FIRST_CHARACTER)
 *  Returns a substring, from the character given to the end of the source string
 */

static int modstring_substr2( INSTANCE * my, int * params )
{
    int r = string_substr( params[0], params[1], -1 ) ;
    string_discard( params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** FIND (STRING SOURCE, STRING SUBSTRING)
 *  Searchs a substring in a string, and returns its position
 */

static int modstring_strfind( INSTANCE * my, int * params )
{
    int r = string_find( params[0], params[1], 0 ) ;
    string_discard( params[0] ) ;
    string_discard( params[1] ) ;
    return r ;
}

/** FIND (STRING SOURCE, STRING SUBSTRING, INT FIRST)
 *  Searchs a substring in a string, starting from the given position, and returns its position
 */

static int modstring_strfindSSI( INSTANCE * my, int * params )
{
    int r = string_find( params[0], params[1], params[2] ) ;
    string_discard( params[0] ) ;
    string_discard( params[1] ) ;
    return r ;
}

/** STRING LPAD (STRING SOURCE, LENGTH)
 *  Expands the string up to the given length, adding spaces at the left
 */

static int modstring_lpad( INSTANCE * my, int * params )
{
    int r = string_pad( params[0], params[1], 0 );
    string_discard( params[0] );
    string_use( r );
    return r;
}

/** STRING RPAD (STRING SOURCE, LENGTH)
 *  Expands the string up to the given length, adding spaces at the right
 */

static int modstring_rpad( INSTANCE * my, int * params )
{
    int r = string_pad( params[0], params[1], 1 );
    string_discard( params[0] );
    string_use( r );
    return r;
}

/** ITOA (INT VALUE)
 *  Converts an integer to string
 */

static int modstring_itos( INSTANCE * my, int * params )
{
    int r = string_itoa( params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** FTOA (FLOAT VALUE)
 *  Converts a floating-point number to string
 */

static int modstring_ftos( INSTANCE * my, int * params )
{
    int r = string_ftoa( *( float * ) & params[0] ) ;
    string_use( r ) ;
    return r ;
}

/** ATOI (STRING VALUE)
 *  Converts a string to integer
 */

static int modstring_stoi( INSTANCE * my, int * params )
{
    const char * str = string_get( params[0] ) ;
    int r = str ? atoi( str ) : 0 ;
    string_discard( params[0] ) ;
    return r ;
}

/** ATOF (STRING VALUE)
 *  Converts a string to floating-point number
 */

static int modstring_stof( INSTANCE * my, int * params )
{
    const char * str = string_get( params[0] ) ;
    float res = ( float )( str ? atof( str ) : 0 );
    string_discard( params[0] ) ;
    return *(( int * )&res ) ;
}

/** ASC(STRING C)
 *  Return the ASCII code of the first character at the string
 */

static int modstring_asc( INSTANCE * my, int * params )
{
    const char * str = string_get( params[0] ) ;
    int r = str ? *str : 0 ;
    string_discard( params[0] ) ;
    return r ;
}

/** CHR(ASCII)
 *  Returns a string of length 1, with the character of the given ASCII code
 */

static int modstring_chr( INSTANCE * my, int * params )
{
    char buffer[2] = " " ; int r ;
    buffer[0] = params[0] ;
    r = string_new( buffer ) ;
    string_use( r ) ;
    return r ;
}

/** STRING TRIM(STRING SOURCE)
 *  Returns the given string, stripping any space characters at the beginning or the end
 */

static int modstring_trim( INSTANCE * my, int * params )
{
    int r = string_strip( params[0] ) ;
    string_discard( params[0] ) ;
    string_use( r ) ;
    return r;
}

#ifndef WIN32
static char * strrev( char * str )
{
    char *start = str;
    char *left = str;
    char ch;

    while ( *str++ ); str -= 2;

    while ( left < str )
    {
        ch = *left;
        *left++ = *str;
        *str-- = ch;
    }

    return( start );
}
#endif

/** STRING STRREV (STRING SOURCE)
 *  Returns the reverse of the source string
 */

static int modstring_strrev( INSTANCE * my, int * params )
{
    int r = string_new( string_get( params[0] ) );
    string_discard( params[0] ) ;
    string_use( r ) ;
    strrev(( char * ) string_get( r ) );
    return r;
}

/** FORMAT (INT VALUE)
 *  Converts a given integer value to string form
 */

static int modstring_formatI( INSTANCE * my, int * params )
{
    int r = string_format( params[0], 0, '.', ',' );
    string_use( r ) ;
    return r;
}

/** FORMAT (FLOAT VALUE)
 *  Converts a given value to string form
 */

static int modstring_formatF( INSTANCE * my, int * params )
{
    int r = string_format( *( float * ) & params[0], -1, '.', ',' );
    string_use( r ) ;
    return r;
}

/** FORMAT (INT VALUE, INT DECIMALS)
 *  Converts a given integer value to string form. Uses a fixed number
 *  of decimals, as given with the second parameter.
 */

static int modstring_formatFI( INSTANCE * my, int * params )
{
    int r = string_format( *( float * ) & params[0], params[1], '.', ',' );
    string_use( r ) ;
    return r;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_string, functions_exports )[] =
{
    { "LEN"        , "S"   , TYPE_INT   , modstring_strlen     },
    { "UCASE"      , "S"   , TYPE_STRING, modstring_strupper   },
    { "LCASE"      , "S"   , TYPE_STRING, modstring_strlower   },
    { "STRCASECMP" , "SS"  , TYPE_INT   , modstring_strcasecmp },
    { "SUBSTR"     , "SII" , TYPE_STRING, modstring_substr     },
    { "SUBSTR"     , "SI"  , TYPE_STRING, modstring_substr2    },
    { "FIND"       , "SS"  , TYPE_INT   , modstring_strfind    },
    { "FIND"       , "SSI" , TYPE_INT   , modstring_strfindSSI },
    { "LPAD"       , "SI"  , TYPE_STRING, modstring_lpad       },
    { "RPAD"       , "SI"  , TYPE_STRING, modstring_rpad       },
    { "ITOA"       , "I"   , TYPE_STRING, modstring_itos       },
    { "FTOA"       , "F"   , TYPE_STRING, modstring_ftos       },
    { "ATOI"       , "S"   , TYPE_INT   , modstring_stoi       },
    { "ATOF"       , "S"   , TYPE_FLOAT , modstring_stof       },
    { "ASC"        , "S"   , TYPE_BYTE  , modstring_asc        },
    { "CHR"        , "I"   , TYPE_STRING, modstring_chr        },
    { "TRIM"       , "S"   , TYPE_STRING, modstring_trim       },
    { "STRREV"     , "S"   , TYPE_STRING, modstring_strrev     },
    { "FORMAT"     , "I"   , TYPE_STRING, modstring_formatI    },
    { "FORMAT"     , "F"   , TYPE_STRING, modstring_formatF    },
    { "FORMAT"     , "FI"  , TYPE_STRING, modstring_formatFI   },
    { 0            , 0     , 0          , 0                    }
};
