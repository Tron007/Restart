#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>


std::string PID_name,temp_S;
std::string Full_text_search="";
std::string Name_to_search="java";
std::fstream fs;
std::ifstream myfile;
struct dirent **namelist;
int n;

void Report( ){
	 time_t t = time(0);   // get time now
	    struct tm * now = localtime( & t );

 fs.open ("Report.txt", std::fstream::in | std::fstream::out | std::fstream::app);

	  fs << " Restart ->";
	  fs  << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << "  " << now->tm_hour << "H " <<now->tm_min <<"m "
         << std::endl;

    fs.close();

}
std::string processdir(const struct dirent *dir)
{

    return  dir->d_name;

}

int filter(const struct dirent *dir)
{
     uid_t user;
     struct stat dirinfo;
     int len = strlen(dir->d_name) + 7;
     char path[len];

     strcpy(path, "/proc/");
     strcat(path, dir->d_name);
     user = getuid();
     if (stat(path, &dirinfo) < 0) {
	  perror("processdir() ==> stat()");
	  exit(EXIT_FAILURE);
     }
     return !fnmatch("[1-9]*", dir->d_name, 0) && user == dirinfo.st_uid;
}

int main()
{
     /* Based on example in "man scandir" */



     while (true) {
     	usleep(1000000);
     n = scandir("/proc", &namelist, filter, 0);
     if (n < 0)
	  perror("Not enough memory.");
     else {
	  while(n--) {

		  PID_name = processdir(namelist[n]);
		  PID_name = "/proc/"+PID_name+"/cmdline";
         //std::cout<<PID_name<<std::endl;
		  myfile.open(PID_name.c_str());
		 if (myfile.is_open())
		  {   std::getline (myfile,temp_S);

			  Full_text_search.append(temp_S.c_str());

           ///std::cout<<temp_S<<std::endl;
			  	     myfile.close();
		  }
		 free(namelist[n]);
		  }
	  free(namelist);
	  }

if (Full_text_search.find("wt_accounts")==std::string::npos){
std::cout<<system("/home/server/Desktop/wt_accounts_test/./wt_accounts --docroot . --http-address 0.0.0.0 --http-port 8000");

//std::cout<<std::endl<<"restart ";
Report();

}
     }
     return 0;
}
