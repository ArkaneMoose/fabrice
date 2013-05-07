#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "bigmath.h"
using namespace std;
int concurrency = 1;
string cmd_template = ""; 
string cmd_config = ""; 
string readFile(string file)
{
string data = "";
string line;
ifstream txtfile(file.c_str());
if (txtfile.is_open())
{
while (txtfile.good())
{
getline(txtfile,line);
cout << line << endl;
data += line;
}
txtfile.close();
}
else
{
cout << "ERROR" << endl;
} 
return data;
}
string GetStdoutFromCommand(string cmd) {
string data;
FILE * stream;
const int max_buffer = 256;
char buffer[max_buffer];
cmd.append(" 2>&1");
stream = popen(cmd.c_str(), "r");
if (stream) {
while (!feof(stream))
if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
pclose(stream);
}
return data;
}
int main (int argc, char* argv[])
{
cout << big_int_add("69", "100") << endl; 
cout << GetStdoutFromCommand("du /usr/lib") << endl;
cout << GetStdoutFromCommand("du /home/jwpilly/Git") << endl;
cout << readFile("test.txt") << endl;
cout << "Parameters \n" << endl;
bool templateset = false; 
bool configset = false; 
for (int i = 1; i < argc; i++)
{
cout << i << endl;
stringstream ss;
string s;
ss << argv[i];
ss >> s;
if (s.substr(0, 4) == "-ci=")
{

istringstream(s.substr(4)) >> concurrency;
cout << "concurrency integer set to " << concurrency << endl;
}
else if (s.substr(0, 3) == "-t=")
{
cmd_template = readFile(s.substr(3));
templateset = true; 
}
else if (s.substr(0, 3) == "-c=")
{
cmd_config = readFile(s.substr(3)); 
configset = true; 
}
}
if (templateset == false || configset == false)
{
cout << "Config file or Template file argument not detected, exiting" << endl;
exit(1); 
}

cout << "------------" << endl;
return EXIT_SUCCESS;
}
