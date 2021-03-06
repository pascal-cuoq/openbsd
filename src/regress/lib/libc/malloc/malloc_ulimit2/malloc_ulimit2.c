/*	$OpenBSD: malloc_ulimit2.c,v 1.1 2006/04/18 19:04:03 otto Exp $	*/

/* Public Domain, 2006, Otto Moerbeek <otto@drijf.net> */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#define FACTOR 	1024

main()
{
	struct rlimit lim;
	size_t sz;
	int i;
	void *p;

	if (getrlimit(RLIMIT_DATA, &lim) == -1)
		err(1, "getrlimit");

	sz = lim.rlim_cur / FACTOR;

	for (i = 0; ; i++) {
		size_t len = (sz-i) * FACTOR;
		p = malloc(len);
		if (p != NULL) {
			free(p);
			break;
		}
	}
	i += 10;
	for (; i >= 0; i--) {
		size_t len = (sz-i) * FACTOR;
		p = malloc(len);
		free(p);
		free(malloc(4096));
	}
	return (0);
}
