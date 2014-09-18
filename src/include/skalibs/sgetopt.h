/* ISC license. */

#ifndef SGETOPT_H
#define SGETOPT_H


 /* reentrant */

typedef struct subgetopt_s subgetopt_t, *subgetopt_t_ref ;
struct subgetopt_s
{
  int ind ;
  int err ;
  int problem ;
  char const *arg ;
  unsigned int pos ;
  char const *prog ;
} ;

#define SUBGETOPT_ZERO { .ind = 1, .err = 1, .problem = 0, .arg = 0, .pos = 0, .prog = 0 }

extern int subgetopt_r (int, char const *const *, char const *, subgetopt_t_ref) ;


 /* non-reentrant */

extern int sgetopt_r (int, char const *const *, char const *, subgetopt_t_ref) ;

extern subgetopt_t subgetopt_here ;

#define subgetopt(argc, argv, opts) subgetopt_r((argc), (argv), (opts), &subgetopt_here)
#define sgetopt(argc, argv, opts) sgetopt_r((argc), (argv), (opts), &subgetopt_here)
#define sgetopt_prog() (subgetopt_here.prog = PROG)

/* define SUBGETOPT_SHORT if you don't mind potential name conflicts */

#ifdef SUBGETOPT_SHORT
# define getopt sgetopt
# define optarg subgetopt_here.arg
# define optind subgetopt_here.ind
# define opterr subgetopt_here.err
# define optopt subgetopt_here.problem
# define opteof (-1)
#endif

#endif
