/* File:  
 *    deusVult.c
 *
 * Purpose:
 *    Command Line client to feed commands to the Daemon.
 *    Additionally is capable of creating and removing the pipe
 *    by itself.
 *
 * Input:
 *    Execution taks several command line argument
 * Output: 
 *    message from each process
 *
 * Compile:  gcc -g -Wall -o bin/deusVult src/deusVult.c -lm
 * Usage:    ./bin/deusVult <command>
 *
 *           - make sure to create the pipe first (-mkpipe) before trying
 *             to pass commands to the daemon
 *
 *           - removing the pipe (by unlink) will cause daemon to hang if
 *             still running
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

  //check that there is a command to extract
  if(argc!=2)
    {
      printf("Usage: bin/servitor <command>\n");
      exit(0);
    }
  
  char *command = (char*)argv[1];

  /* Set up variables for demon pipe address relative to current dir */
  int fd;
  char * daemonPipe = "/pipes/daemonControlPipe";
  char cwd[1024];
  char addr[1024];

  /* figure out pipe address */
  getcwd(cwd, sizeof(cwd));
  strcpy(addr,cwd);
  strcat(addr,daemonPipe);
  
  if(strcmp(command,"-mkpipe") == 0)
    {
       /* create the FIFO daemon */
        mkfifo(addr, 0666);
    }
  else if(strcmp(command,"-rmpipe") == 0)
    {
       /* remove the FIFO daemon (unwanted or multiple commands not allowed) */
       unlink(addr);
    }
  else
    {
      /* send (write) command to the daemon */
      fd = open(addr, O_WRONLY);
      write(fd, command, sizeof(command));
      close(fd);
    }
  
  return 0;	
}
