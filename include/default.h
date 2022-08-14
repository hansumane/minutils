int getarg (const int, char **, const int, const int);
void setvol (char *, FILE *);
void die (const int, const char *);

int
getarg (const int argc, char **argv, const int order, const int way)
{

  /* way == 0 => flag (starting with '-')
     way == 1 => argument not including argv[0], so
     order becomes order + way or order + 1
     if you pass no program name argument to argv,
     then the program will not properly work! */

  int inner_order = 0;

  for (int i = 0; i < argc; ++i)
    if (((argv[i][0] == '-' && (argv[i][1] < '0' || argv[i][1] > '9')) != way)
        && ++inner_order == (order + way))
      return i;

  return -1;
}

void
setcol (char *cn, FILE *stream)
{
  char bold = 0;
  if (!stream)
    stream = stdout;

  if (cn)
    {
      if (cn[0] == 'b')
        {
          ++bold;
          ++cn;
        }
      if (!strcmp (cn, "black"))
        fprintf (stream, "\033[%hhu;30m", bold);
      else if (!strcmp (cn, "red"))
        fprintf (stream, "\033[%hhu;31m", bold);
      else if (!strcmp (cn, "green"))
        fprintf (stream, "\033[%hhu;32m", bold);
      else if (!strcmp (cn, "yellow"))
        fprintf (stream, "\033[%hhu;33m", bold);
      else if (!strcmp (cn, "blue"))
        fprintf (stream, "\033[%hhu;34m", bold);
      else if (!strcmp (cn, "magenta") || !strcmp (cn, "purple"))
        fprintf (stream, "\033[%hhu;35m", bold);
      else if (!strcmp (cn, "cyan"))
        fprintf (stream, "\033[%hhu;36m", bold);
      else if (!strcmp (cn, "white"))
        fprintf (stream, "\033[%hhu;37m", bold);
      else
        fputs ("\033[0m", stream);
    }
  else
    fputs ("\033[0m", stream);
}

void
die (const int code, const char *expr)
{
  setcol ("bred", stderr);
  switch (code)
    {
    case 1:
      fputs ("Wrong input!\n", stderr);
      break;
    case 2:
      if (expr)
        {
          fputs ("No such file: ", stderr);
          setcol ("byellow", stderr);
          fprintf (stderr, "%s\n", expr);
        }
      else
        fputs ("No such filename!\n", stderr);
      break;
    case -1:
      fputs ("Unexpected error!\n", stderr);
      break;
    default:
      fputs ("Undefined error...\n", stderr);
    }
  setcol (NULL, stderr);
  exit (code);
}
