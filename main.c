/***************************************************************************//**
  @file         main.c
  @author       Dipro Chowdhury
  @date         Tuesday, 5 April 2016
*******************************************************************************/

int main(int argc, char **argv)
{
  // Load config files Here

  // call the loop function here
  shell_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

//Implementation of the loop