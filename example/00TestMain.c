#include "../include/func.h"
#include <stdarg.h>

//static char sprint_buf[1024];
int printf1(char *,...);

int main(int argc, char *argv[])
{
	if(isDebugger())
		errors("You Are Running In Debugger!");
    success("Today IS %d-%d",11,7);
    logs("Time IS %d:%d",13,12);
    message("%s Comming Soon","Wubin");
    warning("Process Stoped %.2f%%",91.76);
    errors("System Is Shutting Down%c",'!');
}



int printf1(char *fmt, ...)
{
	va_list args;
	int n;
	va_start(args, fmt);
	n = vsprintf(sprint_buf, fmt, args);
	va_end(args);
	write(1, sprint_buf, n);
	return n;
}