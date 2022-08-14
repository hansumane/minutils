#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/default.h"

#define BUFFER (8 * sizeof(unsigned long long int) + 1)

static unsigned long long int number;
static int flg, arg, way;

static char buffer[BUFFER] = { '0' };
static char result[BUFFER] = { };
static char *endptr = NULL;

int
main (int argc, char **argv)
{
  flg = getarg (argc, argv, 1, 0);
  arg = getarg (argc, argv, 1, 1);

  if (arg < 0)
    die (1, NULL);

  if (flg < 0)
    way = 0;
  else if (!strcmp (argv[flg], "-f") || !strcmp (argv[flg], "--full"))
    way = 1;
  else
    die (1, NULL);

  number = strtoull (argv[arg], &endptr, 10);

  for (size_t i = 0; number > 0; ++i)
    {
      buffer[i] = '0' + number % 2;
      number /= 2;
    }

  for (ssize_t i = 0, j = strlen (buffer) - 1; j >= 0;)
    result[i++] = buffer[j--];

  if (way)
    {
      setcol ("cyan", stdout);
      fputs ("0b", stdout);
      setcol (NULL, stdout);
    }
  puts (result);
  if (way)
    {
      setcol ("cyan", stdout);
      printf ("  ^%zu\n", strlen (result) - 1);
      setcol (NULL, stdout);
    }

  return 0;
}
