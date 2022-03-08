#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PORT 2024
extern int errno;
int nr=0;
char msg[100],msg2[100];	
int main ()
{
    struct sockaddr_in server;	
    struct sockaddr_in from;	
    int sd;			
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
    	perror ("[server]Eroare la socket().\n");
    	return errno;
    }
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (PORT);
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
    	perror ("[server]Eroare la bind().\n");
    	return errno;
    }
    if (listen (sd, 1) == -1)
    {
    	perror ("[server]Eroare la listen().\n");
    	return errno;
    }
    while (1)
    {
    	int client;
    	int length = sizeof (from);
    	printf ("[server]Asteptam la portul %d...\n",PORT);
    	fflush (stdout);
    	
    	client = accept (sd, (struct sockaddr *) &from, &length);
        nr++;
    	if (client < 0)
    	{
    		perror ("[server]Eroare la accept().\n");
    		continue;
    	}
    	int pid;
    	if ((pid = fork()) == -1) {
    		close(client);
    		continue;
    	} else if (pid > 0) {
    		close(client);
    		while(waitpid(-1,NULL,WNOHANG));
    		continue;
    	} else if (pid == 0) {
    		close(sd);
    		while(strncmp(msg,"S-a inchis clientul",19)!=0)
    		{
    		bzero (msg, 100);
    		printf ("[server]Asteptam mesajul...\n");
    		fflush (stdout);
    		if (read (client, msg, 100) <= 0)
    		{
    			perror ("[server]Eroare la read() de la client.\n");
    			close (client);	
    			continue;		
    		}
    		if(strncmp(msg,"S-a inchis clientul",19)!=0)
    		{sprintf(msg2,"%d",nr);
    		strcat(msg," de la clientul ");
    		strcat(msg,msg2);
    		}
    		else
    		{
    		sprintf(msg2,"%d",nr);
    		strcat(msg,msg2);
    		}
    		printf ("[server]Mesajul a fost receptionat...%s\n", msg);
    		int i=strlen(msg);
    		msg[i]='\0';
    		}
    		
    		close (client);
    		exit(0);
    	}

    }				
}				
