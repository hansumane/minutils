#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/default.h"

static int flg, arg;
static const char *tdescfmt = "%-3u | 0x%02X | %-4s | %s\n";
static const char *tcharfmt = "%-3u | 0x%02X |  %c   |\n";
static const char *fdescfmt = "DEC: %u | HEX: 0x%02X\nChar: %s - %s\n";
static const char *fcharfmt = "DEC: %u | HEX: 0x%02X\nChar: '%c'\n";
static const char *table[33][2] = {
  {"NUL", "Null-terminator '\\0'"},
  {"SOH", "Start of heading"},
  {"STX", "Start of text"},
  {"ETX", "End of text"},
  {"EOT", "End of transmission"},
  {"ENQ", "Enquiry"},
  {"ACK", "Acknowledge"},
  {"BEL", "Bell '\\a'"},
  {"BS",  "Backspace '\\b'"},
  {"HT",  "Horizontal tab '\\t'"},
  {"LF",  "Line feed '\\n'"},
  {"VT",  "Vertical tab '\\v'"},
  {"FF",  "Form feed '\\f'"},
  {"CR",  "Carriage return '\\r'"},
  {"SO",  "Shift out"},
  {"SI",  "Shift in"},
  {"DLE", "Data link escape"},
  {"DC1", "Device control 1"},
  {"DC2", "Device control 2"},
  {"DC3", "Device control 3"},
  {"DC4", "Device control 4"},
  {"NAK", "Negative-acknowledge"},
  {"SYN", "Synchronous idle"},
  {"ETB", "End of transmission block"},
  {"CAN", "Cancel"},
  {"EM",  "End of medium"},
  {"SUB", "Substitute Win/EOF"},
  {"ESC", "Escape '\\e'"},
  {"FS",  "File separator"},
  {"GS",  "Group separator"},
  {"RS",  "Record separator"},
  {"US",  "Unit separator"},
  {" ",   "Space"},
};

void
ptable (void)
{
  puts ("DEC | HEX  | Char | Description");
  puts ("----+------+------+--------------------------");
  for (unsigned int i = 0; i <= 32; ++i)
    printf (tdescfmt, i, i, table[i][0], table[i][1]);
  for (unsigned int i = 33; i <= 126; ++i)
    printf (tcharfmt, i, i, i);
}

void
chinfo (const int argc, char **argv)
{
  unsigned int result = (unsigned int) argv[arg][0];
  printf (fcharfmt, result, result, result);
}

void
ninfo (const int argc, char **argv)
{
  unsigned int result = (unsigned int) atoi (argv[arg]);
  if (result <= 126)
    {
      if (result <= 32)
        printf (fdescfmt, result, result, table[result][0], table[result][1]);
      else
        printf (fcharfmt, result, result, result);
    }
  else
    die (1, NULL);
}

int
main (int argc, char **argv)
{
  flg = getarg (argc, argv, 1, 0);
  arg = getarg (argc, argv, 1, 1);

  if (arg < 0 && flg < 0)
    ptable ();
  else if (arg > 0 && flg < 0)
    chinfo (argc, argv);
  else if (arg > 0 && !strcmp (argv[flg], "-s"))
    chinfo (argc, argv);
  else if (arg > 0 && !strcmp (argv[flg], "-n"))
    ninfo (argc, argv);
  else
    die (1, NULL);

  return 0;
}
