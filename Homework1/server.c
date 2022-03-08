#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <utmp.h>
#include <time.h>

int main() {
   int fd;
   int i;
   char readbuf[200];
   char raspuns[100];
   char user[30]=" ";
   int read_bytes;
   char *myfifo="myfifo";
   mkfifo(myfifo,0666);
   while(1) 
   {
      fd = open(myfifo, O_RDONLY);
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      if (strcmp(readbuf,"quit") == 0) {
         sleep(2);
         close(fd);
         i=strlen("quit");
         sprintf(raspuns,"%d",i);
         strcat(raspuns,"quit");
         fd=open(myfifo,O_WRONLY); 
         write(fd,raspuns,strlen(raspuns)+1);  
         close(fd);
         exit(0);
         break;
      } 
      else
     if((strcmp(readbuf,"login : username") !=0) && (strcmp(readbuf,"logout") !=0) && (strcmp(readbuf,"get-logged-users") !=0) && (strcmp(readbuf,"get-proc-info : pid") !=0))
      {
      sleep(2);
      close(fd);
      i=strlen("wrong command");
      sprintf(raspuns,"%d",i);
      strcat(raspuns,"wrong command");
      fd=open(myfifo,O_WRONLY); 
      write(fd,raspuns,strlen(raspuns)+1);   
      close(fd);
  }
      else
      if((strcmp(readbuf,"login : username") == 0)&&(strcmp(user," ")!=0)) {
      sleep(2);
      close(fd);
      i=strlen("connection impossible, we already have a connected user");
      sprintf(raspuns,"%d",i);
      strcat(raspuns,"connection impossible, we already have a connected user");
      fd=open(myfifo,O_WRONLY); 
      write(fd,raspuns,strlen(raspuns)+1);   
      close(fd);
      }
      else
      if((strcmp(readbuf,"logout") == 0)&&(strcmp(user," ")==0)) {
        sleep(2);
        close(fd);
        i=strlen("logout is impossible because we don't have a connected user");
        sprintf(raspuns,"%d",i);
        strcat(raspuns,"logout is impossible because we don't have a connected user");
        fd=open(myfifo,O_WRONLY); 
        write(fd,raspuns,strlen(raspuns)+1); 
        close(fd);
      }
      else
      if((strcmp(readbuf,"logout") == 0)&&(strcmp(user," ")!=0)) {
        strcpy(user," ");
        sleep(2);
        close(fd);
        i=strlen("Succesful logout");
        sprintf(raspuns,"%d",i);
        strcat(raspuns,"Succesful logout");
        fd=open(myfifo,O_WRONLY);
        write(fd,raspuns,strlen(raspuns)+1);
        close(fd);
      }
      else
      if((strcmp(readbuf,"get-logged-users")==0)&& (strcmp(user," ")==0)) {
        sleep(2);
        close(fd);
        i=strlen("Error, because we don't have a connected user");
        sprintf(raspuns,"%d",i);
        strcat(raspuns,"Error, because we don't have a connected user");
        fd=open(myfifo,O_WRONLY);
        write(fd,raspuns,strlen(raspuns)+1);
        close(fd);
      }
      else
      if((strcmp(readbuf,"get-logged-users")==0)&& (strcmp(user," ")!=0)) {
      sleep(2);
      close(fd);
      int sockp[2], proces2; 
      char msg[1024];
      socketpair(AF_UNIX, SOCK_STREAM, 0, sockp);
      proces2 = fork();
      if (proces2>0)   //parinte 
        {  
            close(sockp[0]); 
            read(sockp[1], msg, 1024);
            //printf("[parinte] %s\n", msg);
            
            fd=open(myfifo,O_WRONLY);
            i=strlen(msg);
            sprintf(raspuns,"%d",i);
            strcat(raspuns,msg);
            write(fd,raspuns,strlen(raspuns)+1);
            sleep(2); 
            close(fd);
            write(sockp[1], "mesaj random", sizeof("mesaj random"));
            close(sockp[1]);  
          } 
        else if(proces2 ==0)    //copil
          { 
            close(sockp[1]); 
            struct utmp *p_utent;
            char sirsocket[256]=" ";
            char conversie[256]=" ";
            while((p_utent = getutent()) != NULL){
                sprintf(conversie, "%s",p_utent->ut_user); 
                strcat(sirsocket,conversie);
                strcat(sirsocket," ");
                sprintf(conversie, "%s",p_utent->ut_host); 
                strcat(sirsocket,conversie);
                strcat(sirsocket," ");
                sprintf(conversie, "%d",p_utent->ut_time); 
                strcat(sirsocket,conversie);
                strcat(sirsocket, "\n");
        }   
           write(sockp[0], sirsocket, sizeof(sirsocket));
           read(sockp[0], msg, 1024); 
           close(sockp[0]);
           exit(0);
           }
          
          
           } 
      else
      if((strcmp(readbuf,"get-proc-info : pid")==0)&& (strcmp(user," ")==0)) {
        sleep(2);
        close(fd);
        i=strlen("Error, because we don't have a connected user");
        sprintf(raspuns,"%d",i);
        strcat(raspuns,"Error, because we don't have a connected user");
        fd=open(myfifo,O_WRONLY);
        write(fd,raspuns,strlen(raspuns)+1);
        close(fd);
      }
      else
      if((strcmp(readbuf,"get-proc-info : pid")==0)&& (strcmp(user," ")!=0)) {
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      sleep(2);
      close(fd);
      int fdpipe3[2], fdpipe4[2];  
      int proces3; 
      pipe(fdpipe3);
      pipe(fdpipe4);
      proces3 = fork(); 
      if(proces3>0) {  //parinte
        char sir2[1000]; 
        close(fdpipe3[0]);  
        write(fdpipe3[1], readbuf, strlen(readbuf)+1); 
        close(fdpipe3[1]); 
        wait(NULL); 
        close(fdpipe4[1]); 
        read(fdpipe4[0], sir2, sizeof(sir2)); 
        fd=open(myfifo,O_WRONLY);
        i=strlen(sir2);
        sprintf(raspuns,"%d",i);
        strcat(raspuns,sir2);
        write(fd,raspuns,strlen(raspuns)+1); 
        close(fdpipe4[0]);   
        close(fd); 
    } 
   else
   if(proces3==0)  //copil
     { 
        close(fdpipe3[1]);  
        read(fdpipe3[0], readbuf, sizeof(readbuf));
        char stocare[1000],altsir[1000];
        char loc[1000];
        strcpy(loc,"/proc/");
        strcat(loc,readbuf);
        strcat(loc,"/status");
        int citire=open(loc, O_RDONLY);
        int size=read(citire,stocare,sizeof(stocare));
        stocare[size]='\0';
        //printf("%s",stocare);
        int k=0,i=0;
        while(stocare[i]!='\0'){ 
        if(stocare[i]=='P' && stocare[i+1]=='P' && stocare[i+2]=='i' && stocare[i+3]=='d')
        {
        while(stocare[i]!='\n' && stocare[i]!='\0') {
        altsir[k]=stocare[i];
        k++;i++;}
        altsir[k]='\n';
        k++;i++;}
        else
        if(stocare[i]=='S' && stocare[i+1]=='t' && stocare[i+2]=='a' && stocare[i+3]=='t' && stocare[i+4]=='e')
        {
        while(stocare[i]!='\n' && stocare[i]!='\0') {
        altsir[k]=stocare[i];
        k++;
        i++;}
        altsir[k]='\n';
        k++;i++;}
        else
        if(stocare[i]=='U' && stocare[i+1]=='i' && stocare[i+2]=='d')
        {
        while(stocare[i]!='\n' && stocare[i]!='\0'){
        altsir[k]=stocare[i];
        k++; i++;}
        altsir[k]='\n';
        k++; i++;}
        else
        if(stocare[i]=='N' && stocare[i+1]=='a' && stocare[i+2]=='m' && stocare[i+3]=='e')
        {
        while(stocare[i]!='\n' && stocare[i]!='\0'){
        altsir[k]=stocare[i];
        k++;i++;}
        altsir[k]='\n';
        k++;i++;}
        else
        if(stocare[i]=='V' && stocare[i+1]=='M' && stocare[i+2]=='S' && stocare[i+3]=='i' && stocare[i+4]=='z' && stocare[i+5]=='e')
        {
        while(stocare[i]!='\n' && stocare[i]!='\0') {
        altsir[k]=stocare[i];
        k++; i++;}
        altsir[k]='\n';
        k++;i++;}
        else
        i++;
        }
        altsir[k]='\0';
        close(fdpipe3[0]); 
        close(fdpipe4[0]); 
        write(fdpipe4[1], altsir, strlen(altsir)+1); 
        close(fdpipe4[1]); 
        exit(0);  }
    }
      else
      if((strcmp(readbuf,"login : username") == 0)&&(strcmp(user," ")==0)) {
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      sleep(2);
      close(fd);
      int fdpipe1[2], fdpipe2[2];  
      int proces1; 
      pipe(fdpipe1);
      pipe(fdpipe2);
      proces1 = fork(); 
   if(proces1>0)   //parinte
  { 
        char sir2[100]; 
        close(fdpipe1[0]); 
        write(fdpipe1[1], readbuf, strlen(readbuf)+1); 
        strcpy(user,readbuf);
        close(fdpipe1[1]); 
        wait(NULL); 
        close(fdpipe2[1]); 
        read(fdpipe2[0], sir2, sizeof(sir2)); 
        fd=open(myfifo,O_WRONLY); 
        write(fd,sir2,strlen(sir2)+1); 
        if(strcmp(sir2,"8NOT FIND")==0)
        strcpy(user," ");
        close(fdpipe2[0]);  
        close(fd); 
    } 
   else
   if(proces1==0)  //copil
     { char sir[100];char sir2[100]; 
     char corect[6]="4FIND";
     char gresit[10]="8NOT FIND";
     int lungime;
     FILE *fcitire= fopen("logininfo.txt", "r");
        close(fdpipe1[1]);  
        read(fdpipe1[0], readbuf, sizeof(readbuf)); 
       while(fgets(sir,sizeof(sir),fcitire)!=0)	 
       { 
       lungime = strlen(sir);
       sir[lungime - 1] = '\0';
       if(strcmp(sir,readbuf)==0) 
       { 
       strcpy(sir2,corect); 
       fclose(fcitire);
       break; 
       } 
       else 
       {
       strcpy(sir2,gresit); 
       fclose(fcitire);
      } 
      }
        close(fdpipe1[0]); 
        close(fdpipe2[0]); 
        write(fdpipe2[1], sir2, strlen(sir2)+1); 
        close(fdpipe2[1]); 
        exit(0); 
    }
      }
}
   return 0;
}



