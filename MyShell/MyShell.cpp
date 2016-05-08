// ---- Program Info Start----
//FileName:     MyShell.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-05-07 20:04:27
// ---- Program Info End  ----

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

void displayPrompt(){
    time_t t;
    struct tm * tmp;
    char buf[64];

    time(&t);
    tmp = localtime(&t);
    strftime(buf, 64, "%a %b %d, %Y, %r",tmp);
    printf("%s \n", buf);

    char * home = getenv("PWD");
    printf("%s $ ", home);

}

void readCommand( char * command, char * parameters [] ){
    char commandLine[2048];
    char * word;
    int count = 0;
    gets(commandLine);
    //printf("command line is %s \n", commandLine);

    parameters[count++] = strtok(commandLine, " ");
    strcpy(command, parameters[0]);
    //printf("command is : %s \n", parameters[count-1]);
    for(; parameters[count-1] != NULL;){
        parameters[count++] = strtok(NULL, " ");
        //printf("command is : %s \n", parameters[count-1]);
    }
    parameters[count-1] = getenv("PWD"); //设定运行子程序的envp
    parameters[count] = (char *)0;

}

int main(int argc, char *argv[])
{
    char command[1024],* parameters[1024];
    int status;

    while(1)
    {
        displayPrompt();
        readCommand(command, parameters);
        if( fork()!=0 ){
            waitpid(-1, &status, 0);
        }
        else{
            //int i=0;
            //while(parameters[i] != NULL)
            //printf("%s \n", parameters[i++]);
            if(execvp(command, parameters) < 0){
                printf("exec error\n");
                exit(-1);
            }
            exit(0);
        }
    }
    return 0;
}
