/*	File:		BareBones.c	Contains:	The main routine	Written by: Chris White		Copyright:	Copyright � 1996-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/6/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/#pragma segment Core#define __MAIN__// System includes#ifndef __MEMORY__	#include <Memory.h>#endif// Application includes#ifndef __PROTOTYPES__	#include "Prototypes.h"#endif#if !defined(THINK_C) && !defined(__MWERKS__)		// These declares "qd" in their runtime	QDGlobals	qd;#endifvoid main ( void ){	MaxApplZone ( );		// Do we use handles?	MoreMasters ( );	MoreMasters ( );		InitToolbox ( );						// Init toolbox stuff	InitApplication ( );					// Init application specific stuff	EventLoop ( );		return;}