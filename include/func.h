// This File Was Created By Wubin In 2021
// Copyright (C) 2021s Free Software Foundation
// Version 1.7.6
// Coding: UTF-8

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <error.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <sys/ptrace.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#define BUF_SIZE 1024
#define TRUE 1
#define FALSE 0
#define ERROR -1

static char sprint_buf[BUF_SIZE + BUF_SIZE]={'\0'};

void errors(const char * message,...)
{
    memset(sprint_buf,'\0',BUF_SIZE + BUF_SIZE);
    va_list args;
    va_start(args,message);
    /*int size =*/ vsprintf(sprint_buf,message,args);
    va_end(args);
    fputs("\a[\033[0;31m  ERROR  \033[0m] ",stderr);
    fputs(sprint_buf,stderr);
    fputc('\n',stderr);
    exit(ERROR);
}

void warning(const char * message,...)
{
    memset(sprint_buf,'\0',BUF_SIZE + BUF_SIZE);
    va_list args;
    va_start(args,message);
    /*int size =*/ vsprintf(sprint_buf,message,args);
    va_end(args);
    fputs("\a[\033[0;33m WARNING \033[0m] ",stderr);
    fputs(sprint_buf,stderr);
    fputc('\n',stderr);
    usleep(1800000);
}

void message(const char * message,...)
{
    memset(sprint_buf,'\0',BUF_SIZE + BUF_SIZE);
    va_list args;
    va_start(args,message);
    /*int size =*/ vsprintf(sprint_buf,message,args);
    va_end(args);
    fputs("[\033[0;34m  INFOR  \033[0m] ",stdout);
    fputs(sprint_buf,stdout);
    fputc('\n',stdout);
}

void success(const char * message,...)
{
    memset(sprint_buf,'\0',BUF_SIZE + BUF_SIZE);
    va_list args;
    va_start(args,message);
    /*int size =*/ vsprintf(sprint_buf,message,args);
    va_end(args);
    fputs("[\033[0;32m SUCCESS \033[0m] ",stdout);
    fputs(sprint_buf,stdout);
    fputc('\n',stdout);
}

void logs(const char * message,...)
{
    memset(sprint_buf,'\0',BUF_SIZE + BUF_SIZE);
    va_list args;
    va_start(args,message);
    /*int size =*/vsprintf(sprint_buf,message,args);
    va_end(args);
    fputs("            ",stdout);
    fputs(sprint_buf,stdout);
    fputc('\n',stdout);
}

void read_childproc(int sig)
{
    //pid_t pid;
    int status;
    /*pid =*/ waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        //printf("PID: %d Exit With: %d\n\n",pid,WEXITSTATUS(status));
    }
    else exit(ERROR);
}

void ( * SIGREG(int sig,void ( * func)(int))) (int)
{
    struct sigaction act;
    act.sa_handler = func;
    sigemptyset (&act.sa_mask);
    act.sa_flags = 0;
    
    sigaction(sig,&act,0);
    return func;
}

long int file_size1(char * filename)
{
    struct stat statbuf;
    long int state = stat (filename,&statbuf);
    if(state != 0) return -1;
    else return statbuf.st_size;
}

long int file_size2(char * filename)
{
    FILE * fp = fopen (filename,"rb");
    if(fp == NULL) return -1;
    fseek (fp,0,SEEK_END);
    long int size = ftell(fp);
    fclose (fp);
    return size;
}

void procbar(int m)
{
    if(m >= 0 && m <= 100)
    {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        char bar[50] = {0};
        char * lab = "-\\|/";
        for(int i = 0;i < m/2;i++)
            bar[i] = '#';
        bar[m/2+1] = '\0';
        printf ("[ %-50s ][ %.3d%% ][ %c ]\r",bar,m,lab[tv.tv_sec%4]);
        fflush(stdout);
    }
    //else exit(-1);
}

void procbar_f(float m,bool state)
{
    if(m >= 0 && m <= 100.01)
    {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        char bar[51] = {0};
        char * lab = "-\\|/";
        char text[150];
        memset(text,0,150);;
        for(int i = 0;i < (m/2);i++)
            bar[i] = '=';
        if((int)m % 2)
        {
            bar[(int)(m/2)] = '-';
            bar[(int)(m/2) + 1] = '\0';
        }
        else
            bar[(int)(m/2)] = '\0';
        if(state == FALSE)
        {
            if((int)m == 100)
                state = TRUE;
            else
                sprintf(text,"\a[\033[0;33m%-50s\033[0m][ %.3d.%.2d%% ][ \033[0;31m\033[5m%s\033[0m ]        \r\033[?25h",bar,(int)m,(int)((m - (int)m) * 100),"Terminated");
        }
        if(state)
        {
            if((int)m == 100)
                sprintf(text,"[%-50s][ %.3d.%.2d%% ][ \033[0;32m%s\033[0m ]\033[0m        \r\033[?25h",bar,(int)m,(int)((m - (int)m) * 100),"OK");
            else
                sprintf(text,"\033[?25l[\033[0;32m%-50s\033[0m][ %.3d.%.2d%% ][ %c ]            \r",bar,(int)m,(int)((m - (int)m) * 100),lab[(tv.tv_sec)%4]);
        }
        //fflush(stdout);
        printf("%s",text);
        fflush(stdout);
    }
}

bool isNotes(char msg[])
{
    if(msg[0] == '#')
        return true;
    else return false;
}

bool isEmptyL(char msg[])
{
    if(msg[0] == '\n')
        return true;
    else return false;
}

bool isContainC(char * msg,char c)
{
    char * master = msg;
    bool flag = false;
    while(*master != '\0')
        if(*master++ == c)
            flag = true;
    return flag;
}

void rmNextL(char * msg)
{
    char * master = msg;
    while (*master != '\0')
    {
        if(*master == '\n')
        {
            *master = '\0';
            break;
        }
        master++;
    }
}

void rmCharacter(char * msg,char c)
{
    char * master = msg;
    char * i, * j;
    while (*master != '\0')
    {
        i = master;
        j = i + 1;
        if(*i == c)
        {
            while(*i != '\0')
            {
                *i = *j;
                i++;j++;
            }
        }
        if(*master != c)
            master++;
    }
}

void subString(char * msg,char c,char * s1,char * s2)
{
    char * master = msg;
    char * i = s1;
    char * j = s2;
    while(*master != c)
    {
        *i = *master;
        i++;
        master ++;
    }
    *i = '\0';master++;
    while(*master != '\0')
    {
        *j = *master;
        j++;
        master++;
    }
    if(*(j-1) == '\n')
        *(j-1)='\0';
    else *j = '\0';
}

void upperConvertion(char * msg)
{
    char * master = msg;

    while(*master != '\0')
    {
        if((*master >= 97) && (*master <= 122))
            *master -= 32;
        master++;
    }
}

void lowerConvertion(char * msg)
{
    char * master = msg;

    while(*master != '\0')
    {
        if((*master >= 65) && (*master <= 90))
            *master += 32;
        master++;
    }
}

bool isDebugger()
{
    if(ptrace(PTRACE_TRACEME,0,0,0) == ERROR)
        return true;
    else return false;
}