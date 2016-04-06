/** @file Command.cc
 * Implementation of class Command.
 */
#include <iostream>
#include <cstdlib>		// for: getenv()
#include <unistd.h>		// for: getcwd(), close(), execv(), access()
#include <limits.h>		// for: PATH_MAX
#include <fcntl.h>		// for: O_RDONLY, O_CREAT, O_WRONLY, O_APPEND
#include "asserts.h"
#include "unix_error.h"
#include "Command.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;


// Iff PATH_MAX is not defined in limits.h
#ifndef	PATH_MAX
# define	PATH_MAX (4096)	/* i.e. virtual pagesize */
#endif


Command::Command()
	: append(false)
{
}

void	Command::addWord(string& word)
{
	words.push_back(word);
}


void	Command::setInput(std::string& the_input)
{
	require(input.empty());		// catch multiple inputs
	input = the_input;
}

void	Command::setOutput(std::string& the_output)
{
	require(output.empty());	// catch multiple outputs
	output = the_output;
	append = false;
}

void	Command::setAppend(std::string& the_output)
{
	require(output.empty());	// catch multiple outputs
	output = the_output;
	append = true;
}

// A true "no-nothing" command?
bool	Command::isEmpty() const
{
	return input.empty() && output.empty() && words.empty();
}


// ===========================================================


// Execute a command
void	Command::execute()
{
	// TODO:	Handle I/O redirections.
	//			Don't blindly assume the open systemcall will always succeed!
	// TODO:	Convert the words vector<string> to: array of (char*) as expected by 'execv'.
	//			Note: In this case it safe to typecast from 'const char*' to 'char *'.
	//			Note: Make sure the last element of that array will be a 0 pointer!
	// TODO:	Determine the path of the program to be executed.
	// 			If the name contains a '/' it already is a path name,
	//				either absolute like "/bin/ls" or relative to the
	//				current directory like "sub/prog".
	// 			Otherwise it is the name of an executable file to be
	// 				searched for using the PATH environment variable.
	// TODO:	Execute the program passing the arguments array.
	// Also see: close(2), open(2), getcwd(3), getenv(3), access(2), execv(2), exit(2)
	// TODO: replace the code below with something that really works

#if 1	/* DEBUG code: Set to 0 to turn off the next block of code */
	cerr <<"Command::execute ";
	// Show the I/O redirections first ...
	if (!input.empty())
		cerr << " <"<< input;
	if (!output.empty()) {
		if (append)
			cerr << " >>"<< output;
		else
			cerr << " >"<< output;
	}
	// ... now show the command & parameters to execute
	if (words.empty())
		cerr << "\t(EMPTY_COMMAND)" << endl;
	else {
		cerr << "\t";
		for (vector<string>::iterator  i = words.begin() ; i != words.end() ; ++i)
			cerr << " " << *i;
		cerr << endl;

       if(string(words.front()) == "cat") {
           executeCatCommand();
        }


	}
#endif	/* end DEBUG code */
}


std::vector<std::string> catParameters;

void	Command::executeCatCommand()
{

    for (vector<string>::iterator  i = words.begin() ; i != words.end() ; ++i)
    {
        //Cat Commando
        if(i == words.begin())
        {
            cerr <<  "First parameter: " << *i <<endl;
        }
        //Cat commando parameters
        else if(std::find(catCommands.begin(), catCommands.end(), *i) != catCommands.end())
        {
            catParameters.push_back(*i);
        }
        //Cat bestanden
        else
        {
            int f=0,n;
            char l[80];
            struct stat s;

            std::string str = string(*i);

            const char * filename =  str.c_str();

            //Kijk of het bestand wel benaderbaar is
            if(access(filename,F_OK))
           {
                 cerr << "File doesn't exist" << endl;
                 return;
           }
            //Kijk of het eeb geldig bestand is
           if(S_ISREG(s.st_mode)<0)
           {
                cerr << "Not a Regular file" << endl;
                 return;
           }

            //Open het bestand en scrhijf output naar de console.
           if(geteuid()==s.st_uid)
                   if(s.st_mode & S_IRUSR)
                           f=1;
           else if(getegid()==s.st_gid)
                   if(s.st_mode & S_IRGRP)
                           f=1;
           else if(s.st_mode & S_IROTH)
                   f=1;
           if(!f)
           {
               cerr << "Permission denied" << endl;
                 return;
           }

           f=open(filename,O_RDONLY);
           while((n=read(f,l,80))>0)
                   write(1,l,n);

        }
    }


}



// vim:ai:aw:ts=4:sw=4:
