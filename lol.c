#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define NCHILDREN 3
pid_t child [NCHILDREN];

struct sigaction sa, old;

static void
handler (int ignore)
{
  int i;

  /* Kill the children.  */
  for (i = 0; i < NCHILDREN; ++i)
    {
      if (child [i] > 0)
        {
          kill (child [i], SIGUSR1);
          waitpid (child [i], 0, 0);
        }
    }

  /* Restore the default handler.  */
  sigaction (SIGUSR1, &old, 0);

  /* Kill self.  */
  kill (getpid (), SIGUSR1);
}

int
main ()
{
  int i;

  /* Install the signal handler.  */
  sa.sa_handler = handler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction (SIGUSR1, &sa, &old);

  /* Spawn the children.  */
  for (i = 0; i < NCHILDREN; ++i)
    {
      if ((child [i] = fork ()) == 0)
        {
          /* Each of the children: clear the array, wait for a signal
             and exit.  */
          while (i >= 0)
            child [i--] = -1;
          pause ();
          return 0;
        }
    }

  /* Wait to be interrupted by a signal.  */
  pause ();
  return 0;
}