/* Code to read Gleipnir ascii format.
 * Author: Tomislav Janjusic
 * Institution: CSRL University of North Texas, Denton Texas
 * 2012
 * Provided as is, no warranty is implied or expressed. *
 */
/*** old copy right below ***/

/*
 * Code to read the traditional ascii "din" format for Dinero IV.
 * Written by Jan Edler and Mark D. Hill
 * 
 * Copyright (C) 1997 NEC Research Institute, Inc. and Mark D. Hill.
 * All rights reserved.
 * Copyright (C) 1985, 1989 Mark D. Hill.  All rights reserved.
 * 
 * Permission to use, copy, modify, and distribute this software and
 * its associated documentation for non-commercial purposes is hereby
 * granted (for commercial purposes see below), provided that the above
 * copyright notice appears in all copies, derivative works or modified
 * versions of the software and any portions thereof, and that both the
 * copyright notice and this permission notice appear in the documentation.
 * NEC Research Institute Inc. and Mark D. Hill shall be given a copy of
 * any such derivative work or modified version of the software and NEC
 * Research Institute Inc.  and any of its affiliated companies (collectively
 * referred to as NECI) and Mark D. Hill shall be granted permission to use,
 * copy, modify, and distribute the software for internal use and research.
 * The name of NEC Research Institute Inc. and its affiliated companies
 * shall not be used in advertising or publicity related to the distribution
 * of the software, without the prior written consent of NECI.  All copies,
 * derivative works, or modified versions of the software shall be exported
 * or reexported in accordance with applicable laws and regulations relating
 * to export control.  This software is experimental.  NECI and Mark D. Hill
 * make no representations regarding the suitability of this software for
 * any purpose and neither NECI nor Mark D. Hill will support the software.
 * 
 * Use of this software for commercial purposes is also possible, but only
 * if, in addition to the above requirements for non-commercial use, written
 * permission for such use is obtained by the commercial user from NECI or
 * Mark D. Hill prior to the fabrication and distribution of the software.
 * 
 * THE SOFTWARE IS PROVIDED AS IS.  NECI AND MARK D. HILL DO NOT MAKE
 * ANY WARRANTEES EITHER EXPRESS OR IMPLIED WITH REGARD TO THE SOFTWARE.
 * NECI AND MARK D. HILL ALSO DISCLAIM ANY WARRANTY THAT THE SOFTWARE IS
 * FREE OF INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHTS OF OTHERS.
 * NO OTHER LICENSE EXPRESS OR IMPLIED IS HEREBY GRANTED.  NECI AND MARK
 * D. HILL SHALL NOT BE LIABLE FOR ANY DAMAGES, INCLUDING GENERAL, SPECIAL,
 * INCIDENTAL, OR CONSEQUENTIAL DAMAGES, ARISING OUT OF THE USE OR INABILITY
 * TO USE THE SOFTWARE.
 *
 * $Header: /home/edler/dinero/d4/RCS/dinfmt.c,v 1.2 1997/12/08 19:35:24 edler Exp $
 */

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"

/* Gleipnir format.
 * Format:
 * L/S/M | ADDRESS | SIZE | TID | SEG | FUNCTION | SCOPE | ELEMENT
 * X | ADDRESS | MALLOC | SIZE | NAME
 * L/S/M | ADDRESS | SIZE | TID | FUNCTION | H-enum | ELEMENT 
 */

/* NOTE
 * Each structure will be stripped (will not track individual elements)
 * Same is true for arrays.
 * 
 * Will not track Global vs Local variable type at this point
 */

static d4memref
get_keyword(int atype, d4addr addr, unsigned int tid, char c)
{
	d4memref r;
	int i=0;

	/*Set prelims*/
	r.accesstype = atype;
	r.address = addr;
	r.tid = tid;
	r.seg = '\0';
  r.size = 0;


	/* get malloc type CALLOC/MALLOC/REALLOC*/
	r.function[i] = c;
	i++;
	do{
		c = getchar();
		r.function[i] = c;
		i++;
	}while(c != ' ' && c != '\t');
	r.function[i] = '\0';

	//printf("%s ", r.function);

	/* skip initial space */
	do {
		c = getchar();
	} while (c == ' ' || c == '\t');
		
	/* get size */
	r.size = (int)c - 48;
	c = getchar();
	while(isdigit(c)){
		r.size *= 10;
		r.size += (int)c - 48;
		c = getchar();
	}

	/*skip whitespace*/
	do{
    c = getchar();
  }while(c == ' ' || c == '\n');

  /*get struct name*/
  i=0;
  r.variable[i] = c;
  do{
    c = getchar();
    i++;
    r.variable[i] = c;
  }while(c != '\n' && c != ' ' && c != '\t');
  r.variable[i] = '\0';

	r.scope[0] = '\0';
	r.h_enum = 0;

	//printf("\n");

	return r;
}

d4memref
tracein_glin()
{
	static double tcount = 1;	/* double to increase range */
	int atype = 0;
	d4addr addr = 0;
	unsigned int size = 0;
	unsigned int tid = 1;
	char segment = '\0';
	char function[128];
	char scope[3];
	unsigned long int h_enum = 0;
	char variable[128];	
	
	int i = 0;
	int c;
	
	d4memref r;
	r.isOK = 1; /* Set to 1, if we encounter a problem it'll be set to 0
				 			 * We'll skip bad lines (rather than aborting completely) */

	/* skip initial space */
	do {
		c = getchar();
	} while (c == ' ' || c == '\t');
	
	/* check conditions */
	if (c == EOF) {
		r.accesstype = D4TRACE_END;
		r.address = 0;
		r.size = 0;
    return r;		/* this will trigger normal termination */
	}
	if (c == '\n'){ 	/* something is messed up, just skip this line*/
		r.isOK = 0;		
		return r;
	}

/* 
 * L/S/M/
 */
	if(c == 'L')
		atype = 0;
	else if(c == 'S')
    atype = 1;
	else if(c == 'M')
		atype = 1;
	else if(c == 'X')
		atype = 3;
	else{
		r.isOK=0;
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}
        
	c = getchar(); 	/* next char must be space, we only accept single character atypes! */
	if (c != ' ' && c != '\t') {	
		r.isOK=0;
		
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}

	/* skip whitespace between label and address */
	do {
		c = getchar();
	} while (c == ' ' || c == '\t');
	
	if (c == '\n' || c == EOF){
		r.isOK=0;
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}
	//printf("%d ", atype);

/*
 * ADDRESS
 */
	/* Check if it's not a digit */
	/* This happens for X accesstypes */
	if (!isxdigit(c)){
		r.isOK = 0;
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}

	/* Convert the address */
	addr = c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
	c = getchar();
	if ((c == 'x' || c == 'X') && addr == 0){
		c = getchar();	/* ignore leading 0x or 0X */
	}
	while (isxdigit(c)) {
		addr *= 16;
		addr += c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
		c = getchar();
	}
	/* We have the full address */

	/* Check if space */
	if(c != ' ' && c != '\t'){
		r.isOK=0;
		while(c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}
	/* skip whitespace */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');

	//printf("%lx ", addr);

/*
 * SIZE
 */
	if(isdigit(c)){
		size = (int)c - 48;
		c = getchar();
		while(isdigit(c)){
			size *= 10;
			size += (int)c - 48;
			c = getchar();
		}
	}

	/* Check if space */
	if(c != ' ' && c != '\t'){
		r.isOK=0;
		while(c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}
	/* skip whitespace */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');
	
	//printf("%d ", size);

	/* Check for keyword */
	if(atype == 3){
		r = get_keyword(atype, addr, /*actually tid*/ size, /*curr char*/c);
		return r;
	}

/*
 * TID
 */
	if(isdigit(c)){
		tid = (int)c - 48;
		c = getchar();
		while(isdigit(c)){
			tid *= 10;
			tid += (int)c - 48;
			c = getchar();
		}
	}

	/* Check for space */
	if(c != ' ' && c != '\t'){
		r.isOK=0;
		while(c != '\n' && c != EOF){
			c = getchar();
		}
		return r;
	}
	/* skip whitespace */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');
	
	//printf("%d ", tid);

/*
 * SEGMENT
 */	
	segment = c;

	/* skip whitespace */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');

	//printf("%c ", segment);
	/* Format: TYPE ADDR SIZE TID SEG;
	 * Check if there is a function
	 */
	if (c == '\n' || c == EOF){
		r.accesstype = atype;
		r.address = addr;
		r.size = size;
		r.tid = tid;
		r.seg = segment;
		strcpy(r.function, "_unknown_");
		r.scope[0] = '\0';
		r.h_enum = 0;
		strcpy(r.variable, "_unknown_");
		
		tcount +=1;
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		//printf("\n");
		return r;
	}
	
/*
 * FUNCTION
 */
	i = 0;
	do{
		function[i] = c;
		c = getchar();
		i++;
	}while(c != '\n' && c != EOF && c != ' ' && c != '\t');
	function[i] = '\0';
	//printf("%s ", function);
	
	/* Format: TYPE ADDR SIZE TID SEG FUNCTION
	 * Check if there is a scope*/
	if(c == '\n' || c == EOF){
		r.accesstype = atype;
		r.address = addr; 
		r.size = size;
		r.tid = tid;
		r.seg = segment;
		strcpy(r.function,function);
		r.scope[0] = '\0';
		r.h_enum = 0;
		strcpy(r.variable,"_unknown_");

		tcount +=1;	
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		//printf("\n");
		
		return r;
	}
	
	/* Skip remaining space */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');
		
/*
 * SCOPE
 */
	i = 0;
	do{
		scope[i] = c;
		c = getchar();
		i++;
	}while(c != ' ' && c != '\t' && c != '-' && c != '\n' && c != EOF);
	scope[i] = '\0';
	//printf("%s ", scope);

	/*If scope is H(Heap) then c=='-', get h_enum*/
	if(c == '-'){
		c = getchar();
		h_enum = (int)c - 48;
		c = getchar();
		while(isdigit(c)){
			h_enum *= 10;
			h_enum += (int)c - 48;
			c = getchar();
		}
		//printf("-%ld ", h_enum);
	}

	/* Skip remaining space */
	do{
		c = getchar();
	}while(c == ' ' || c == '\t');
		
	if(c == '\n' || c == EOF){
		/*
		 * Set everything but the variable.
		 * This is the rare case; not sure if this still holds.
		 */
		r.accesstype = atype;
		r.address = addr; 
		r.size = size;
		r.tid = tid;
		r.seg = segment;
		strcpy(r.function,function);
		strcpy(r.scope,scope);
		r.h_enum = h_enum;
		r.variable[0] = '\0';
		
		tcount +=1;
		/* skip rest of line */
		while (c != '\n' && c != EOF){
			c = getchar();
		}
		//printf("\n");
		return r;
	}
	
/*
 * VARIABLE
 * Note: for now will skip structures and offsets
 * a variable name may be a dynamic structure name, which may
 * include spaces, so be sure to ignore any spaces
 */	
	i = 0;
	do{
		variable[i] = c;
		c = getchar();
		i++;
	}while(c != '\n' && c != EOF && c != '[' && c != '.');
	variable[i] = '\0';
	
	//printf("%s\n", variable);
	/* skip rest of line */
	while (c != '\n' && c != EOF){
		c = getchar();
	}
	
	r.accesstype = atype;
	r.address = addr; 
	r.size = size;
	r.tid = tid;
	r.seg = segment;
	strcpy(r.function,function);
	strcpy(r.scope, scope);
	r.h_enum = h_enum;
	strcpy(r.variable, variable);

	tcount += 1;
	
	return r;
}
