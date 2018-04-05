/* File:  
 *    testDaemon
 *
 * Compile:  gcc -g -Wall -o bin/daemon src/daemon.c -lm
 * Usage:    ./bin/daemon
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_BUF 1024
#define KILL_DAEMON 1
#define START_TONE 2

void createStream(double hertz, int sampleRate, int offset[8]);


int main(int argc, char *argv[]){

  /* Set up variables for demon pipe address relative to current dir */
  int command = 0;
  int fd;
  char * daemonPipe = "/pipes/daemonControlPipe";
  char cwd[1024];
  char addr[1024];
  char buf[1024];
  getcwd(cwd, sizeof(cwd));
  strcpy(addr,cwd);
  strcat(addr,daemonPipe);

  /* Turn process into a daemon with relative path and control (1,1)*/
  daemon(1,1);

  /* The Big Loop */
  while (command != KILL_DAEMON) {
    /* open, read, and display the message from the FIFO */
    fd = open(addr, O_RDONLY);
    read(fd, buf, MAX_BUF);
    close(fd);

    if(strcmp(buf,"-kill") == 0)
      {
        command=KILL_DAEMON;
      }
    if(strcmp(buf,"-start") == 0)
      {
        command=START_TONE;
	
	int myOffset[8] = {0,0,0,0,0,0,0,0};
        createStream(20000.0,256000,myOffset);
      }
  }

  printf("\nDaemon has exited\n");

  return 0;	
}

void createStream(double hertz, int sampleRate, int offset[8])
{
  //calculate time increment
  double timeIncrement = 1.0/sampleRate;

  //allocate offsets (in seconds)
  double time[] = {0.0+timeIncrement*offset[0],
                   0.0+timeIncrement*offset[1],
                   0.0+timeIncrement*offset[2],
                   0.0+timeIncrement*offset[3],
                   0.0+timeIncrement*offset[4],
                   0.0+timeIncrement*offset[5],
                   0.0+timeIncrement*offset[6],
                   0.0+timeIncrement*offset[7]};

  uint8_t out;

  for(int i = 0; i <= 10; i++)
    {
      for(int j = 0; j < 8; j++)
        {
          out = (uint8_t) (256 * sin(M_PI*time[j]*hertz));
          printf("%d - %d - %f - %d \n",i,j,time[j],out);
          time[j] = time[j] + timeIncrement;
        }
    }
}
