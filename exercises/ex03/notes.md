
`tee [ -a ] [ -i ] [ File ... ]`

General plan for basics:
- open file in write mode, else error
- read (an amount?) from stdin, write to file, write to stdout
- append: open file in append mode vs write
- ignore interrupt signals: which ones? in python you can catch the error.

cmdline interface options:
- [getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html): recursive, bash-ish method, standard POSIX if only short-options
- [argp](https://www.gnu.org/software/libc/manual/html_node/Argp.html): python `argparse`-ish, more features (automatic help/version)
- ISO C: `int main (int argc, char *argv[])`
- UNIX (non-POSIX): `int main (int argc, char *argv[], char *envp[])`

- interrupt signal catching: `signal` and `sighandler`
  - https://stackoverflow.com/questions/19618579/catching-all-signals-in-linux
- real tee with `-i` ignores `^C` (signal), but not `^D` (EOF) or `^Z` (bash/shell level?)
