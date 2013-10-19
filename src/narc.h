// -*- mode: c; tab-width: 8; indent-tabs-mode: 1; st-rulers: [70] -*-
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2013 Pagoda Box, Inc.  All rights reserved.
 */

#ifndef NARC_H
#define NARC_H 

// #include "fmacros.h"
// #include "config.h"

#if defined(__sun)
#include "solarisfixes.h"
#endif

// #include <string.h>	/* string operations */
// #include <time.h>	/* time types */
// #include <limits.h>	/* implementation-defined constants */
// #include <errno.h>	/* system error numbers */
// #include <inttypes.h>	/* fixed size integer types */
// #include <pthread.h>	/* threads */
// #include <netinet/in.h>	/* Internet Protocol family */
// #include <signal.h>	/* signals */

#include <uv.h>		/* Event driven programming library */

#include "sds.h"	/* Dynamic safe strings */
#include "dict.h"	/* Hash tables */
#include "adlist.h"	/* Linked lists */
#include "zmalloc.h"	/* total memory usage aware version of malloc/free */
#include "intset.h"	/* Compact integer set structure */
#include "version.h"	/* Version macro */
#include "util.h"	/* Misc functions useful in many places */

/* Error codes */
#define NARC_OK		0
#define NARC_ERR	-1

/* Static narc configuration */
#define NARC_DAEMONIZE   	0
#define NARC_PIDFILE     	"/var/run/narc.pid"
#define NARC_REMOTE_HOST 	"127.0.0.1"
#define NARC_REMOTE_PORT 	514
#define NARC_REMOTE_PROTO	"tcp"
#define NARC_MAX_LOGMSG_LEN	1024	/* Default maximum length of syslog messages */

/* Log levels */
#define NARC_DEBUG		0
#define NARC_VERBOSE		1
#define NARC_NOTICE		2
#define NARC_WARNING		3
#define NARC_LOG_RAW		(1<<10)	/* Modifier to log without timestamp */
#define NARC_DEFAULT_VERBOSITY	NARC_NOTICE

/* Anti-warning macro... */
#define NARC_NOTUSED(V)	((void) V)

/* We can print the stacktrace, so our assert is defined this way: */
#define narcAssertWithInfo(_c,_o,_e)	((_e)?(void)0 : (_narcAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
#define narcAssert(_e)			((_e)?(void)0 : (_narcAssert(#_e,__FILE__,__LINE__),_exit(1)))
#define narcPanic(_e)			_narcPanic(#_e,__FILE__,__LINE__),_exit(1)

/*-----------------------------------------------------------------------------
 * Data types
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Global state
 *----------------------------------------------------------------------------*/

struct narcServer {
	/* General */
	char		*configfile;			/* Absolute config file path, or NULL */
	char		*pidfile;			/* PID file path */
	dict		*streams;			/* Stream table */
	uv_loop_t	*loop;				/* Event loop */
	/* Networking */
	char		*host; 				/* Remote syslog host */
	int 		port; 				/* Remote syslog port */
	char 		*protocol; 			/* Protocol to use when communicating with remote host */
	/* Configuration */
	int		verbosity;			/* Loglevel in narc.conf */
	int		daemonize;			/* True if running as a daemon */
	/* Logging */
	char		*logfile;			/* Path of log file */
	int		syslog_enabled;			/* Is syslog enabled? */
	char		*syslog_ident;			/* Syslog ident */
	int		syslog_facility;		/* Syslog facility */
	/* Limits */
	unsigned long long	maxmemory;		/* Max number of memory bytes to use */
};

/*-----------------------------------------------------------------------------
 * Extern declarations
 *----------------------------------------------------------------------------*/

extern struct narcServer	server;

/*-----------------------------------------------------------------------------
 * Functions prototypes
 *----------------------------------------------------------------------------*/

/* Core functions */
#ifdef __GNUC__
void	narcLog(int level, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
#else
void	narcLog(int level, const char *fmt, ...);
#endif
void	narcLogRaw(int level, const char *msg);

#endif