/*
Date: 06/12/2014
Author: Cooler_
Contact: coolerlair@gmail.com
License: GPL3 read file LICENSE.txt

*/
#include <stdio.h> 
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include "file_ops.h"


void init_banner_mosca()
{
 puts(
 CYAN
"           _      \n"
"       (^\\'='/^)  \n"
"        \\ \\=/ /    .  .  __   ___  ___  __  \n"
"      '--\\_Y_/--'  |\\/| |  | [__  |    |__| \n" 
"       .'(_I_)`.   |  | |__| ___] |___ |  |   coded by Cooler_\n"
"           \"       \n"
 YELLOW
"    Tool to find bugs like a grep unix command  v0.07 \n"
 LAST
"+-----------------------------------------------------------------+\n"
"Options: \n"
"--egg = Load module to make analysis '--egg eggs/php_top_fails.php' don't use '../path' \n"
"--path = Path to open and make recursive search, use full path don't use ../path \n"
"--ext = File extension to search example; get only C files '\\.c$' \n"
"--log = File to save results \n"
YELLOW
"Example: \n"
LAST
"$ ./mosca --egg eggs/php_common_fail.egg --path /home/user/blog_php --ext \"\\\\.php$\" --log reports.txt \n"
 );
 puts(LAST);
}

static struct option long_options[] =
{
	{"egg", required_argument, NULL, 'e'},
	{"path", required_argument, NULL, 'p'},
	{"ext", required_argument, NULL, 'x'},
	{"log", required_argument, NULL, 'o'},
	{NULL, 0, NULL, 0}
};


int main(int argc, char ** argv)
{
 char c;
 char *pack[5]; 
 short y=4;

	if(argc < 8) 
	{
		init_banner_mosca();
		DEBUG(" Need more arguments.\n");
		exit(0);
	}

 	while(y>-1)
 	{
  		pack[y]=NULL;
  		y--;
 	}


	opterr = 0;

 	while((c = getopt_long(argc, argv, "e:p:x:o",long_options,NULL)) != -1)
  		switch(c) 
  		{
   			case 'e':
    				
				if ( strnlen(optarg,256)<= 255 )
				{
    					pack[0] = optarg;
    					printf("Egg: %s \n",pack[0]);
    					
				} else {
					DEBUG("Error \nArgument egg is very large \n");
					exit(1);
				}
				break;

			case 'p':
				if ( strnlen(optarg,256)<= 255 )
				{
    					pack[1] = optarg;
    					printf("Path: %s \n",optarg);
    					
				} else {
					DEBUG("Error \nArgument Path very large  \n");
					exit(1);
				}
				break;

   			case 'x':    				
				if ( strnlen(optarg,8)<= 7 )
				{
    					pack[2] = optarg;
    					printf("Extension: %s \n",optarg);
    				} else {
			
					DEBUG("Error \nArgument extension is very large  \n");
					exit(1);
				}
				break;

   			case 'o':    				
				if ( strnlen(optarg,256)<= 255 )
				{
    					pack[3] = optarg;
    					printf("Log file: %s \n",optarg);
    				} else {
			
					DEBUG("Error \nArgument Log is very large  \n");
					exit(1);
				}
				break;

   			case '?':
    				if(optopt == 'e' || optopt == 'p' || optopt == 'x' || optopt == 'o' ) 
    				{
     					init_banner_mosca();
     					puts(RED);
     					DEBUG("Option -%c requires an argument.\n", optopt); 
     					puts(LAST);
     					exit(1);
    				}
				break;

			default:	
				init_banner_mosca();
				DEBUG("Need more arguments.\n");
				exit(1);

  		}


		if(pack[0]==NULL)
		{
			DEBUG("error at egg file");
			exit(0);
		}


		if(pack[1]==NULL)
		{
			DEBUG("error at path file");
			exit(0);
		}


		if(pack[3]==NULL)
		{
			DEBUG("error at log file");
			exit(0);
		}

		if(pack[2]==NULL)
		{
			DEBUG("error at extension file");
			exit(0);
		}
		
		burn_mem(log_file,0,255);	
		strncpy(log_file,pack[3],255);

		mosca_start(pack[1],pack[2],pack[0]);

    exit(0);
}
