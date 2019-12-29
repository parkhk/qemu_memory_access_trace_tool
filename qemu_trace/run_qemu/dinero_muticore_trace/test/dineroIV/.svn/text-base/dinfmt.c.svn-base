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
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"

/*
 * Read in ASCII from standard input
 * Expect ONE label and addr in hex per line.
 * Rest of data input line is ignored so it may
 * be used for comments.
 *
 * This version is a bit more forgiving than the
 * FAST_BUT_DANGEROUS_INPUT version in Dinero III.
 *
 * WARNING: If more than one tuple is put on a line,
 * all but the first tuple will be ignored.
 */

d4memref
tracein_din()
{
	int i;
	char c, instrData;
	char cpuNumber[8], processID[8], size[8];
	
	d4memref r;
	r.isOK = 1; /* Set to 1, if we encounter a problem it'll be set to 0
				 * We'll skip bad lines (rather than aborting completely)
				 * since some (very small percentage) lines aren't perfect
				 */
    
	/* skip initial whitespace */
	do {
		instrData = getchar();
	} while (instrData == ' ' || instrData == '\t' || instrData == '\n');

	if (instrData == EOF) {
		r.isOK = 1;	/* causes an infinite loop if set to zero */
		r.cpuID = 0;
		r.address = 0;
		r.processID = 0;
		r.accesstype = D4TRACE_END;
		r.size = 0;
        return r;	/* this will trigger normal termination */
	}

	/*======================== INSRUCTION/DATA ======================*/
	if(instrData == 'I') {
		r.accesstype = D4XINSTRN;
		r.size = 8;
	}
	else if(instrData != 'D')
		goto panic;
	getchar();
	
	/*=========================== CPUNUMBER =========================*/
   	i = 0;
	while((c = getchar())) {
		if(i > 6) {
			cpuNumber[i] = '\0';
			goto panic;
		}
		else
			cpuNumber[i] = c;

		if(!isdigit(cpuNumber[i]) && !isspace(cpuNumber[i]))
			goto panic;
		else if(isspace(cpuNumber[i])) {
			cpuNumber[i] = '\0';
			break;
		}
		i++;
	}
	r.cpuID = atoi(cpuNumber);

	/*============================= ADDRESS =========================*/
	r.address = 0;
	c = getchar();
    while (isxdigit(c)) {
		//printf("%c", c);
    	r.address *= 16;
    	r.address += c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
    	c = getchar();
    }

	/*============================= PROCESS ID  =====================*/
	i = 0;
	while((c = getchar())) {
		if(i > 6) {
			processID[i] = '\0';
			goto panic;
		}
		else
			processID[i] = c;

		if(!isdigit(processID[i]) && !isspace(processID[i]) && processID[i] != '-')
			goto panic;
		else if(isspace(processID[i])) {
			processID[i] = '\0';
			break;
		}
		i++;
	}
	r.processID = atoi(processID);

	i = 0;
	while((c = getchar())) {
		if(i > 6) {
			size[i] = '\0';
			goto panic;
		}
		else
			size[i] = c;

		if(!isdigit(size[i]) && !isspace(size[i]) && size[i] != '-')
			goto panic;
		else if(isspace(size[i]) || size[i] == EOF) {
			size[i] = '\0';
			break;
		}
		i++;
	}
	r.size = atoi(size);

	if(instrData == 'D') {
		c = getchar();
		if(c == '0')
			r.accesstype = D4XREAD;
		else if(c == '1')
	        r.accesstype = D4XWRITE;
		else
			goto panic;
		getchar();
	}

	return r;

	panic:
		printf("DINERO PANIC: INVALID TRACE LINE!\n");
		r.cpuID = 0;
		r.address = 0;
		r.processID = 0;
		r.accesstype = D4TRACE_END;
		r.size = 0;
		r.isOK=0;

		/* skip rest of line */
		do
			c = getchar();
		while (c != '\n' && c != EOF);

		return r;
}
