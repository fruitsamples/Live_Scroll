/*	File:		Events.c	Contains:	Main event loop and basic keyboard/mouse processing	Written by: Chris White		Copyright:	Copyright � 1996-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/6/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/#pragma segment Core// System Includes#ifndef __MEMORY__	#include <Memory.h>#endif#ifndef __APPLEEVENTS__	#include <AppleEvents.h>#endif#ifndef __DIALOGS__	#include <Dialogs.h>#endif#ifndef __DESK__	#include <Desk.h>#endif#ifndef __WINDOWS__	#include <Windows.h>#endif// Application includes#ifndef __BAREBONES__	#include "BareBones.h"#endif#ifndef __PROTOTYPES__	#include "Prototypes.h"#endif// static includesstatic void DoMouseDown ( EventRecord* theEvent );static void DoKey ( EventRecord*theEvent );void EventLoop ( void ){	OSErr			theErr;	EventRecord		theEvent;			while ( !gQuit )	{		WaitNextEvent ( everyEvent, &theEvent, gSleepTime, nil );					switch ( theEvent.what )		{			case mouseDown: 				DoMouseDown ( &theEvent );			break;						case keyDown:			case autoKey: 				DoKey ( &theEvent );			break;						case activateEvt: 				DoActivate ( &theEvent );			break;						case updateEvt:				DoUpdate ( (WindowRef) theEvent.message );			break;						case osEvt:				if ( (theEvent.message >> 24) & suspendResumeMessage )	// suspend or resume				{					if ( (theEvent.message >> 24) & resumeFlag )						SetCursor ( &qd.arrow );										// Modify the event record to look like an activate/deactivate event					theEvent.modifiers = theEvent.message;		// Copy suspend/resume flag					theEvent.message = (long) FrontWindow ( );						DoActivate ( &theEvent );				}			break;						case kHighLevelEvent:				theErr = AEProcessAppleEvent ( &theEvent );			break;		}	}		return;	} // EventLoopstatic void DoMouseDown ( EventRecord* theEvent ){	Point			globalPt = theEvent->where;	SInt16			windowPart;	WindowRef		theWindow;	long			theMenu;			windowPart = FindWindow ( globalPt, &theWindow );	switch ( windowPart )	{		case inMenuBar: 			theMenu = MenuSelect ( globalPt );			MenuDispatch ( theMenu );		break;				case inSysWindow:			// The SystemClick toolbox routine handles system events			SystemClick ( theEvent, theWindow );		break;				case inGoAway:			// We'll quit when the user closes the window			if ( TrackGoAway ( theWindow, theEvent->where ) )				gQuit = true;		break;				// TO DO: Check order of this switch		case inGrow:			DoGrowWindow ( theWindow, theEvent );		break;				case inDrag:			DoDragWindow ( theWindow, theEvent );		break;		case inContent:			DoContentClick ( theWindow, theEvent );		break;	}		return;	} // DoMouseDownstatic void DoKey ( EventRecord* theEvent ){	char keyPressed = (theEvent->message & charCodeMask);			// Command keys get handled by the menu handling routines	if ( theEvent->modifiers & cmdKey )		MenuDispatch ( MenuKey ( keyPressed ) );		return;	} // DoKey