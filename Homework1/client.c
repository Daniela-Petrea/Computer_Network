#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
 
int main() { 
   int fd1; 
   int lungime; 
   int read_bytes; 
   char str[200]; 
   char user[30]=" "; 
   char *myfifo="myfifo"; 
   mkfifo(myfifo,0666); 
   while (1) { 
      printf("Enter your command: "); 
      fd1 = open(myfifo, O_WRONLY); 
      fgets(str, sizeof(str), stdin); // ia comanda de la tastatura 
      lungime = strlen(str); 
      str[lungime - 1] = '\0'; 
      write(fd1, str, strlen(str)); 
      if (strcmp(str,"quit") != 0) { 
      if((strcmp(str,"login : username") !=0) && (strcmp(str,"logout") !=0) && (strcmp(str,"get-logged-users") !=0) && (strcmp(str, "get-proc-info : pid")!=0)) {  
         close(fd1); 
         fd1=open(myfifo,O_RDONLY); 
         read_bytes=read(fd1,str,sizeof(str)); 
         str[read_bytes]='\0'; 
         printf("%s\n",str);  
         close(fd1); 
      } 
      else 
      if((strcmp(str,"login : username") == 0)&&(strcmp(user," ")!=0)) {  
           close(fd1); 
           fd1=open(myfifo,O_RDONLY); 
           read_bytes=read(fd1,str,sizeof(str)); 
           str[read_bytes]='\0'; 
           printf("%s\n",str);  
           close(fd1); 
      } 
      else 
      if((strcmp(str,"logout") == 0)&&(strcmp(user," ")==0)) { 
           close(fd1); 
           fd1=open(myfifo,O_RDONLY); 
           read_bytes=read(fd1,str,sizeof(str)); 
           str[read_bytes]='\0'; 
           printf("%s\n",str);  
           close(fd1); 
      } 
      else 
      if((strcmp(str,"logout") == 0)&&(strcmp(user," ")!=0)) { 
        strcpy(user," "); 
        close(fd1); 
        fd1=open(myfifo,O_RDONLY); 
        read_bytes=read(fd1,str,sizeof(str)); 
        str[read_bytes]='\0'; 
        printf("%s\n",str);  
        close(fd1); 
      } 
      else 
      if((strcmp(str,"get-logged-users")==0)&& (strcmp(user," ")==0)) {  
        close(fd1); 
        fd1=open(myfifo,O_RDONLY); 
        read_bytes=read(fd1,str,sizeof(str)); 
        str[read_bytes]='\0'; 
        printf("%s\n",str);  
        close(fd1); 
      } 
      else 
      if((strcmp(str,"get-logged-users")==0)&& (strcmp(user," ")!=0)) { 
      close(fd1); 
      fd1=open(myfifo,O_RDONLY); 
      read_bytes=read(fd1,str,sizeof(str)); 
      str[read_bytes]='\0'; 
      printf("%s\n",str);
      close(fd1); 
      } 
      else 
      if((strcmp(str,"get-proc-info : pid")==0)&& (strcmp(user," ")==0)) { 
        close(fd1); 
        fd1=open(myfifo,O_RDONLY); 
        read_bytes=read(fd1,str,sizeof(str)); 
        str[read_bytes]='\0'; 
        printf("%s\n",str);  
        close(fd1); 
      } 
      else 
      if((strcmp(str,"get-proc-info : pid")==0)&& (strcmp(user," ")!=0)) { 
       printf("Enter pid:"); 
       fgets(str,sizeof(str),stdin); 
       lungime = strlen(str); 
       str[lungime - 1] = '\0'; 
       write(fd1,str,strlen(str)+1); 
       close(fd1); 
       //sleep(2); 
       fd1=open(myfifo,O_RDONLY); 
       read_bytes=read(fd1,str,sizeof(str)); 
       str[read_bytes]='\0'; 
       printf("%s\n",str);  
       close(fd1); 
      } 
      else 
      if((strcmp(str,"login : username") ==0)&&(strcmp(user," ")==0)) 
      { 
       printf("Enter username:"); 
       fgets(str,sizeof(str),stdin); 
       lungime = strlen(str); 
       str[lungime - 1] = '\0'; 
       strcpy(user,str); 
       write(fd1,str,strlen(str)+1); 
       close(fd1); 
       //sleep(2); 
       fd1=open(myfifo,O_RDONLY); 
       read_bytes=read(fd1,str,sizeof(str)); 
       str[read_bytes]='\0'; 
       printf("%s\n",str);
       if(strcmp(str,"8NOT FIND")==0) 
       strcpy(user," "); 
       close(fd1); 
      } 
      } 
       else { 
         close(fd1); 
         fd1=open(myfifo,O_RDONLY); 
         read_bytes=read(fd1,str,sizeof(str)); 
         str[read_bytes]='\0'; 
         printf("%s\n",str);  
         close(fd1); 
         exit(0); 
         break; 
      } 
   } 
    
   return 0; 
} 
 



