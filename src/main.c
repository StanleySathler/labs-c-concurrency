#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief: Calculates the factorial of a number.
 */
double factorial(double x)
{
  int total = 0;

  if (x == 0 || x == 1)
    return 1;

  for (int i = x; i > 0; i--)
    total *= i;

  return total;
}

/**
 * @brief: Calculates the sumatory of the square of
 *         a number.
 */
double sumatory(double x)
{
  double total = 0;

  for (int i = 1; i <= x; i++)
    total += pow(i, 2);

  return total;
}

/**
 * @brief: Simulates the `i(x)` function.
 */
double i(double x)
{
  return pow(x, 2) / sqrt(x);
}

/**
 * @brief: Simulates the `l(x)` function.
 */
double l(double x)
{
  return ( factorial(x) - factorial(pow(x, 2)) ) / sumatory(x);
}

/**
 * @brief: Simulates the `h(x)` function.
 */
double h(double x)
{
  double i_res, l_res;
  int p3p4_buffer[2];
  pid_t pid;

  /* Creates an inter-process communication buffer. */
  pipe(p3p4_buffer);

  /* Splits into process: (P3) & (P4). */
  pid = fork();

  /* Child process (P4). */
  if (pid == 0)
  {
    l_res = l(x);

    /* Closes reading and writes to the buffer. */
    close(p3p4_buffer[0]);
    write(p3p4_buffer[1], &l_res, sizeof(l_res));
  }

  /* Parent process (P3). */
  else
  {
    i_res = i(x);

    /* Pauses execution until P4 is finished. */
    wait(0);

    /* Closes writing and reads from the buffer. */
    close(p3p4_buffer[1]);
    write(p3p4_buffer[0], &l_res, sizeof(l_res));

    return (i_res + l_res);
  }
}

/**
 * @brief: Simulates the `g(x)` function.
 */
double g(double x)
{
  return factorial(x);
}

/**
 * @brief: Simulates the `f(x)` function.
 */
double f(double x)
{
  double h_res, g_res, total;
  int p1p2_buffer[2], p1p3_buffer[2];
  pid_t pid, pid2;

  /* Creates an inter-process communication stream. */
  pipe(p1p2_buffer);

  /* Split into two process: (P1) & (P2). */
  pid = fork();

  /* Child process (P2). */
  if (pid == 0)
  {
    g_res = g(x);
    close(p1p2_buffer[0]);
    write(p1p2_buffer[1], &g_res, sizeof(g_res));
  }

  /* Parent process (P1). */
  else
  {
    /* Split into two process: (P1) & (P3). */
    pid2 = fork();

    /* Child process (P3). */
    if (pid2 == 0)
    {
      h_res = h(x);
      close(p1p3_buffer[0]);
      write(p1p3_buffer[1], &h_res, sizeof(h_res));
    }

    /* Parent process (P1). */
    else
    {
      /* Wait twice, once for (P2) and once for (P3). */
      wait(0);
      wait(0);

      /* Close writing and read value from buffer. */
      close(p1p2_buffer[1]);
      close(p1p3_buffer[1]);
      read(p1p2_buffer[0], &g_res, sizeof(g_res));
      read(p1p3_buffer[0], &h_res, sizeof(h_res));

      return (g_res + h_res);
    }
  }
}

/**
 * @brief: The entry function.
 **/
int
main(void)
{
  f(5);
  return(0);
}
