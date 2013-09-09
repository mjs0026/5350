/******************Undelete Utility***********************

	      James Chapman/Maghen Smith
	  jcc0014@auburn.edu / mjs0026@auburn.edu		   

This program prompts the user to either enter 1. a deleted file name, 
2. recover all deleted files, or 3. exit. The program uses the extundelete
program to find deleted files in /dev/sdb1. When finding a specific file,
it will call extundelete, then use the linux command 'find' to see if the
requested file is in the ~/RECOVERED_FILES directory. 


We discussed the project with Robert Horn, Jamal Adams, and Josh Acklin.
P_open sourced from http://www.lainoox.com/tag/in-system-command/. 
Char and string concatenation sourced from http://www.cplusplus.com/forum/general/4422/.
*/


#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <cstring>
using namespace std;
#define COMMAND_LEN 20
#define DATA_SIZE 512




 void get_popen_data()
{
	  
    FILE *pf;
    char command[COMMAND_LEN];
    char data[DATA_SIZE];
    // Execute a process listing
    sprintf(command, "ps aux wwwf"); 


    bool loop = true;
    while(loop)
    {
    int option = 0;
    cout << "UNDELETE UTILITY: \n1. Enter your deleted file name.\n2. Find all deleted files. \n3. Exit.\n";
    cin >> option;
    switch(option)
	{
         case 1:{
	 string fileIn = "";
	 cout << "Enter file name: ";
	 cin >> fileIn;
	
	string pathName = "";
	cout << "If device path nameS is NOT /dev/sdb1 then enter pathname now. Otherwise enter  N\n";
	cin >> pathName;
	
	string s = "";

	if (pathName == "N" || pathName == "n")
	{

	s = "cd ~/; rm -rf RECOVERED_FILES; extundelete --restore-all /dev/sdb1 > /dev/null; cd ~/RECOVERED_FILES; find ";
		
	}
	else 
	{
	s = "cd ~/; rm -rf RECOVERED_FILES; extundelete --restore-all ";
	s.append(pathName);
	s.append(" > /dev/null; cd ~/RECOVERED_FILES; find ");
	}

	s.append(fileIn);
	char *command = (char*)s.c_str();

	
	

	// Setup our pipe for reading and execute our command.
    	pf = popen(command,"w");


	
	printf("\r\n");
	sleep(2);
	printf("\nIf you see your file name located above, it is located in ~/RECOVERED_FILES.\r\n");
	printf("\r\n");

    	if(!pf){
      	fprintf(stderr, "Could not open pipe for output.\n");
      	return;}


	//if (pclose(pf) != 0){
        //fprintf(stderr," Error: Failed to close command stream \n");}
	break;

	
 
}

	case 2:{
	// Setup our pipe for reading and execute our command.


	string pathName = "";
	cout << "\nIf device path nameS is NOT /dev/sdb1 then enter pathname now. Otherwise enter  N\n";
	cin >> pathName;
	
	string s = "";

	if (pathName == "N" || pathName == "n")
	{

	s = "cd ~/; rm -rf RECOVERED_FILES; extundelete --restore-all /dev/sdb1; echo; echo; echo 'List of recovered files: ';  cd ~/RECOVERED_FILES; ls; echo; echo; echo 'Recovered files located at ~/RECOVERED_FILES'";
		
	}
	else 
	{
	s = "cd ~/; rm -rf RECOVERED_FILES; extundelete --restore-all ";
	s.append(pathName);
	s.append("; echo; echo; echo 'list of recovered files: '; cd ~/RECOVERED_FILES; ls; echo; echo; echo 'Recovered files located at ~/RECOVERED_FILES'");
	}

	
	char *command = (char*)s.c_str();

	
	

	// Setup our pipe for reading and execute our command.
    	pf = popen(command,"w");


    	
	printf("\r\n");
	sleep(2);
	printf("\r\n");
 
    	if(!pf){
      	fprintf(stderr, "Could not open pipe for output.\n");
      	return;}


	if (pclose(pf) != 0){
        fprintf(stderr," Error: Failed to close command stream \n");}
	break;	}

	case 3: {
	cout << "Goodbye!\r\n\r\n";
	loop = false;}
	
	}

    }
 
    
    return;
}


int main()
{
	get_popen_data();
}

