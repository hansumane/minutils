#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/default.h"

static int flg, arg1, arg2;
static long long iresult;
static double dresult;
static char *endptr;

int
main (int argc, char **argv)
{
  flg = getarg (argc, argv, 1, 0);
  arg1 = getarg (argc, argv, 1, 1);
  arg2 = getarg (argc, argv, 2, 1);

  if ((arg1 | arg2) < 0)
    die (1, NULL);

  if (flg < 0)
    goto INT;
  else if (strcmp (argv[flg], "-f") == 0)
    goto DBL;
  else if (strcmp (argv[flg], "-i") == 0)
    goto INT;
  else
    die (1, NULL);

INT:
  iresult = strtoll (argv[arg1], &endptr, 10) + strtoll (argv[arg2], &endptr, 10);
  printf ("%lld\n", iresult);
  goto END;
DBL:
  dresult = strtod (argv[arg1], &endptr) + strtod (argv[arg2], &endptr);
  printf ("%lf\n", dresult);
END:
  return 0;
}
