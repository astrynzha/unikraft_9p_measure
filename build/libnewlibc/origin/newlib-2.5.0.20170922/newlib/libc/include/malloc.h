/* malloc.h -- header file for memory routines.  */

#ifndef _INCLUDE_MALLOC_H_
#define _INCLUDE_MALLOC_H_

#include <_ansi.h>
#include <sys/reent.h>

#define __need_size_t
#include <stddef.h>

/* include any machine-specific extensions */
#include <machine/malloc.h>
#ifdef __Unikraft__
#include <uk/config.h>
#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#include <uk/alloc.h>
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* This version of struct mallinfo must match the one in
   libc/stdlib/mallocr.c.  */

struct mallinfo {
  size_t arena;    /* total space allocated from system */
  size_t ordblks;  /* number of non-inuse chunks */
  size_t smblks;   /* unused -- always zero */
  size_t hblks;    /* number of mmapped regions */
  size_t hblkhd;   /* total space in mmapped regions */
  size_t usmblks;  /* unused -- always zero */
  size_t fsmblks;  /* unused -- always zero */
  size_t uordblks; /* total allocated space */
  size_t fordblks; /* total non-inuse space */
  size_t keepcost; /* top-most, releasable (via malloc_trim) space */
};	

/* The routines.  */

#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#ifndef __UK_HAVE_MALLOC__
#define __UK_HAVE_MALLOC__
static inline void *malloc(size_t size)
{
	return uk_malloc(uk_alloc_get_default(), size);
}
#endif /* __UK_HAVE_MALLOC__ */
#else
extern _PTR malloc _PARAMS ((size_t));
#endif
#ifdef __CYGWIN__
#undef _malloc_r
#define _malloc_r(r, s) malloc (s)
#else
extern _PTR _malloc_r _PARAMS ((struct _reent *, size_t));
#endif

#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#ifndef __UK_HAVE_FREE__
#define __UK_HAVE_FREE__
static inline void free(void *ptr)
{
	return uk_free(uk_alloc_get_default(), ptr);
}
#endif /* __UK_HAVE_FREE__ */
#else
extern _VOID free _PARAMS ((_PTR));
#endif
#ifdef __CYGWIN__
#undef _free_r
#define _free_r(r, p) free (p)
#else
extern _VOID _free_r _PARAMS ((struct _reent *, _PTR));
#endif

#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#ifndef __UK_HAVE_REALLOC__
#define __UK_HAVE_REALLOC__
static inline void *realloc(void *ptr, size_t size)
{
	return uk_realloc(uk_alloc_get_default(), ptr, size);
}
#endif /* __UK_HAVE_REALLOC__ */
#else
extern _PTR realloc _PARAMS ((_PTR, size_t));
#endif
#ifdef __CYGWIN__
#undef _realloc_r
#define _realloc_r(r, p, s) realloc (p, s)
#else
extern _PTR _realloc_r _PARAMS ((struct _reent *, _PTR, size_t));
#endif

#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#ifndef __UK_HAVE_CALLOC__
#define __UK_HAVE_CALLOC__
static inline void *calloc(size_t nmemb, size_t size)
{
	return uk_calloc(uk_alloc_get_default(), nmemb, size);
}
#endif /* __UK_HAVE_CALLOC__ */
#else
extern _PTR calloc _PARAMS ((size_t, size_t));
#endif
#ifdef __CYGWIN__
#undef _calloc_r
#define _calloc_r(r, s1, s2) calloc (s1, s2);
#else
extern _PTR _calloc_r _PARAMS ((struct _reent *, size_t, size_t));
#endif

#if CONFIG_LIBUKALLOC_IFSTATS_PERLIB
#ifndef __UK_HAVE_MEMALIGN__
#define __UK_HAVE_MEMALIGN__
static inline void *memalign(size_t align, size_t size)
{
	return uk_memalign(uk_alloc_get_default(), align, size);
}
#endif /* __UK_HAVE_MEMALIGN__ */
#else
extern _PTR memalign _PARAMS ((size_t, size_t));
#endif
#ifdef __CYGWIN__
#undef _memalign_r
#define _memalign_r(r, s1, s2) memalign (s1, s2);
#else
extern _PTR _memalign_r _PARAMS ((struct _reent *, size_t, size_t));
#endif

extern struct mallinfo mallinfo _PARAMS ((void));
#ifdef __CYGWIN__
#undef _mallinfo_r
#define _mallinfo_r(r) mallinfo ()
#else
extern struct mallinfo _mallinfo_r _PARAMS ((struct _reent *));
#endif

extern void malloc_stats _PARAMS ((void));
#ifdef __CYGWIN__
#undef _malloc_stats_r
#define _malloc_stats_r(r) malloc_stats ()
#else
extern void _malloc_stats_r _PARAMS ((struct _reent *));
#endif

extern int mallopt _PARAMS ((int, int));
#ifdef __CYGWIN__
#undef _mallopt_r
#define _mallopt_r(i1, i2) mallopt (i1, i2)
#else
extern int _mallopt_r _PARAMS ((struct _reent *, int, int));
#endif

extern size_t malloc_usable_size _PARAMS ((_PTR));
#ifdef __CYGWIN__
#undef _malloc_usable_size_r
#define _malloc_usable_size_r(r, p) malloc_usable_size (p)
#else
extern size_t _malloc_usable_size_r _PARAMS ((struct _reent *, _PTR));
#endif

/* These aren't too useful on an embedded system, but we define them
   anyhow.  */

extern _PTR valloc _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _valloc_r
#define _valloc_r(r, s) valloc (s)
#else
extern _PTR _valloc_r _PARAMS ((struct _reent *, size_t));
#endif

extern _PTR pvalloc _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _pvalloc_r
#define _pvalloc_r(r, s) pvalloc (s)
#else
extern _PTR _pvalloc_r _PARAMS ((struct _reent *, size_t));
#endif

extern int malloc_trim _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _malloc_trim_r
#define _malloc_trim_r(r, s) malloc_trim (s)
#else
extern int _malloc_trim_r _PARAMS ((struct _reent *, size_t));
#endif

/* A compatibility routine for an earlier version of the allocator.  */

extern _VOID mstats _PARAMS ((char *));
#ifdef __CYGWIN__
#undef _mstats_r
#define _mstats_r(r, p) mstats (p)
#else
extern _VOID _mstats_r _PARAMS ((struct _reent *, char *));
#endif

/* SVID2/XPG mallopt options */

#define M_MXFAST  1    /* UNUSED in this malloc */
#define M_NLBLKS  2    /* UNUSED in this malloc */
#define M_GRAIN   3    /* UNUSED in this malloc */
#define M_KEEP    4    /* UNUSED in this malloc */

/* mallopt options that actually do something */
  
#define M_TRIM_THRESHOLD    -1
#define M_TOP_PAD           -2
#define M_MMAP_THRESHOLD    -3 
#define M_MMAP_MAX          -4

#ifndef __CYGWIN__
/* Some systems provide this, so do too for compatibility.  */
extern void cfree _PARAMS ((_PTR));
#endif /* __CYGWIN__ */

#ifdef __cplusplus
}
#endif

#else
#include_next <malloc.h>

#endif /* _INCLUDE_MALLOC_H_ */
