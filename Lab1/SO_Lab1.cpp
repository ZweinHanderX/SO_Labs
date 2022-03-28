#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main(){

    //Linea de comando 1
    char *args[6];
    //Linea de comando 2
    char *args2[3];

    //Strings para los comandos
    // youtube-dl -x --audio-format mp3
    string yt = "youtube-dl";
    string format = "-x";
    string audio = "--audio-format";
    string mp3 = "mp3";
    string url = "https://www.youtube.com/watch?v=Eyu3KZ64kO8";
    string play = "ffplay";
    string name = "Never Gonna Give You Up-Eyu3KZ64kO8.mp3";

    //Descargar en formato mp3 un video
    args[0] = (char*)yt.c_str();
    args[1] = (char*)format.c_str();
    args[2] = (char*)audio.c_str();
    args[3] = (char*)mp3.c_str();
    args[4] = (char*)url.c_str();
    args[5] = NULL;

    //Reproducir
    args2[0] = (char*)play.c_str();
    args2[1] = (char*)name.c_str();
    args2[2] = NULL;

    pid_t pid = fork();

    //Ejecución del hijo
    if(pid == 0){

        if(execvp (args[0],args) == -1){
        perror("exec");
        }
        
    }
    //Ejecución del padre
    else{
        
        if(wait(0) == -1){
            perror("wait");
        }
        if(execvp (args2[0],args2) == -1){
        perror("exec");
        }
    }
    return 0; 
}