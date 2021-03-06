/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*								*
*    	MODULE:							*
*	    P_GRAPHIC2.C					*
*								*
*	SYNOPSIS:						*
*	    This module contains the write control commands	*
*	for graphic output using the ReGis mode in a VT240	*
*	color terminal.						*
*								*
*	DESCRIPTION:						*
*	    The module contains the following functions		*
*		SetPVFactor()					*
*		SelStdPattern()					*
*		SelBinPattern()					*
*		SelPatternFactor()				*
*		EnableRevPattern()				*
*		EnableBitMap()					*
*		SelFgIntensity()				*
*		SelMapHLS()					*
*		SelFgHLS()					*
*		SelWriteMode()					*
*		EnableShading()					*
*		SelShadeYRef()					*
*		SelShadeXRef()					*
*		SelChShade()					*
*		EraseScreen()					*
*							       	*
*	CAVEATS:						*
*	    Not tested.						*
*								*
*	NOTES:							*
*								*
*	FILES:							*
*								*
*	SEE ALSO:						*
*	    VT240 series. Programmer Pocket Guide		*
*								*
*	DESIGNED BY:						*
*	    Jos� Ram�n Valverde Carrillo.			*
*								*
*  	HISTORY:						*
*	    23 - jul - 1989 J.R.Valverde (implementation)	*
*								*
*	COPYRIGHT:						*
*								*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

#include <stdio.h>

#include "P_graphic.h"

/*--------------------------------------------------------------------
	SetPVFactor
	    Select Pixel Vector multiplication. Defines multipli-
	cation factor for PV values. Can be used as a temporary write
	control for other types of commands.

	INPUT:	FACTOR	Multiplication factor.

	J. R. Valverde
--------------------------------------------------------------------*/

void SetPVFactor(factor)
int factor;
{
    printf("W(M%d)", factor);
}

/*--------------------------------------------------------------------
	SelStdPattern
	    Select standard pattern. Selects 1 of 10 stored
	write patterns for write tasks.

	INPUT:	PATTERN	The pattern to use

	J. R. Valverde
--------------------------------------------------------------------*/

void SelStdPattern(pattern)
int pattern;
{
    if ((pattern > 9) || (pattern < 0))
	return;
    printf("W(P%d)", pattern);
}       

/*--------------------------------------------------------------------
	SelBinPattern
	    Specify a binary pattern. Allows specification of unique
	writing patterns for write tasks. The specified pattern can be
	up to 8 bits in length.

	INPUT:	PATTERN	The desired binary pattern.

	J. R. Valverde
--------------------------------------------------------------------*/

void SelBinPattern(pattern)
char *pattern;
{
    /* Be sure of pattern length */
    pattern[8] = '\0';

    printf("W(P%s)", pattern);
}

/*--------------------------------------------------------------------
	SelPatternFactor
	    Pattern multiplication. Defines the number of times
	each bit of the pattern memory is processed. You can use pattern
	multiplication with either select standard pattern or the
   	specify binary pattern, or by itself, to define a multiplication
	factor for the las specified pattern.

	INPUT:	FACTOR The multiplication factor. Must be between 1
		and 6

	J. R. Valverde
--------------------------------------------------------------------*/
                   
void SelPatternFactor(factor)
int factor;
{
    if ( (factor < 1) || (factor > 6) )
	return;
    printf("WP(M%d)", factor);
}

/*--------------------------------------------------------------------
	EnableRevPattern
	    Negative pattern control. When 1, lets you reverse
	currently selected write pattern.

	INPUT:	NP_ALLOW || NP_AVOID

	J. R. Valverde
--------------------------------------------------------------------*/

void EnableRevPattern(on_off)
int on_off;
{
    printf("W(N%d)", on_off);
}

/*--------------------------------------------------------------------
	EnableBitMap
	    Foreground plane control. Provides a mask that
	determines which planes of the bit map can be written
	to during write tasks.

	INPUT:	MASK	0 -- 3

	J. R. Valverde
--------------------------------------------------------------------*/
                        
void EnableBitMap(mask)
int mask;
{
    if ( (mask < 0) || (mask > 3) )
	return;
    printf("W(F%d)", mask);
}

/*--------------------------------------------------------------------
	SelFgIntensity
	    Foreground intensity select. Defines an output map
	address to use for write tasks. Writing puts address of that
	location into bitmap.

	INPUT:	MAP 0 -- 3

	J. R. Valverde
--------------------------------------------------------------------*/
                        
void SelFgIntensity(map)
int map;
{
    if ( (map < 0) || (map > 3) )
	return;
    printf("W(I%d)", map);
}

/*--------------------------------------------------------------------
	SelFgHLS
	    Foreground intensity select. Defines writing to occur
	using output map address containing the color closest to the
	HLS value specified.

	INPUT:	Hue, Lightness and Saturation values

    J. R. Valverde
--------------------------------------------------------------------*/

void SelFgHLS(h, l, s)
int h, l, s;
{
    printf("W(I(H%dL%dS%d))", h, l, s);
}

/*--------------------------------------------------------------------
	SelMapHLS
	    Select HLS value to store in the specified map location

	INPUT:	MAP - map location
		Hue, Lightness and Saturation to store.

	J. R. Valverde
--------------------------------------------------------------------*/

SelMapHLS(map, h, l, s)
int map, h, l, s;
{
    map = map % 4;
    printf("S(M%c(H%dL%dS%d))", map, h, l, s);
}

/*--------------------------------------------------------------------
	SelWriteMode
	    Four option letters available to define type of
	writing to occur.

	INPUT: MODE C for complement writing
		    E for erase writing
	       	    R for replace writing
		    V for overlay writing

	J. R. Valverde
--------------------------------------------------------------------*/

void SelWriteMode(mode)
char mode;
{
    printf("W(%c)", mode);
}                       

/*--------------------------------------------------------------------
	EnableShading
	    Shading On/Off control. When On, enables shading at
	currently selected pattern. The shading reference line is defined
	by the Y-axis value of the active position when On is invoked.

	INPUT:	ONOFF	The desired status.

	J. R. Valverde
--------------------------------------------------------------------*/

void EnableShading(on_off)
int on_off;
{
    if (on_off)
	printf("W(S1)");
    else
	printf("W(S0)");
}

/*--------------------------------------------------------------------
	SelShadeYRef
	    Shading reference line select. Selects a horizontal
	shading reference line defined by a Y value, which can be
	either an absolute or relative value.

	INPUT:	Y   The y reference line.

	J. R. Valverde
--------------------------------------------------------------------*/

void SelShadeYRef(y)
int y;
{
    printf("W(S[,%d])", y);
}

/*--------------------------------------------------------------------
	SelShadeXRef
	    Shading reference line select. Selects a vertical
	shading reference line defined by X, which can be either
	an absolute or relative value.

	INPUT:	X   The x line reference

	J. R. Valverde
--------------------------------------------------------------------*/

void SelShadeXRef(x)
int x;
{
    printf("W(S(x)[%d])", x);
}

/*--------------------------------------------------------------------
	SelChShade
	    Shading character select. Lets you fill graphics
	objects with the character specified.

	INPUT:	CH  The desired character.

	J. R. Valverde
--------------------------------------------------------------------*/

void SelChShade(ch)
char ch;
{
    printf("W(S'%c')", ch);
}

/*--------------------------------------------------------------------
	EraseScreen
	    Erases the whole screen.

	J. R. Valverde
--------------------------------------------------------------------*/

void EraseScreen()
{
    printf("S(E)");
}

