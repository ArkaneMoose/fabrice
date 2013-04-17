#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include "md5.h"
using namespace std;
char chars[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-', '='};
string t;
int charsetLength;
int si = 0;
int fi = 0; 
int maxChars = 15;
//unsigned long long int counter = 4294967295; 
unsigned long long int counter = 0;
void checkPassword(string password);
void recurse(int width, int position, string baseString);

void decrypt(string input)
{
	cout << "Decrypt Input:" << endl << input << endl;
	//cout << "Charset length:" << strtolen(chars) << endl;
    t = input;
    charsetLength = sizeof(chars);
    cout << "charset length: " << charsetLength << endl;
    cout << "charset: " << chars << endl;
    cout << "maxchar length: " << maxChars << endl;
    for(int i=0;i<maxChars+1;i++) {
      cout << "checking passwords width [" << i << "]..." << endl;
      recurse(i,0,"");
    }
}
void recurse(int width, int position, string baseString) {
	//cout << "si = " << si << "fi = " << fi << endl; 
    for(int i=0;i<charsetLength;i++) {
      if (position < width-1) {
        recurse(width, position + 1, baseString+chars[i]);
      }
      checkPassword(baseString+chars[i]);
    }
}
string encrypt_md5(string input)
{
    return (md5(input));
}
void checkPassword(string password) {
	if (counter >= si)
	{
	if (counter <= fi || fi == 0)
	{
    string md5hash = encrypt_md5(password);
//cout << md5hash << endl;
    if (md5hash==t) {
      cout << "match [" << md5hash << "]" << endl;
      cout << "counter - " << counter << endl;
      cout << password << endl;
      exit(1);
    }
	}
	else
	{
		cout << "reached final index" << endl;
		cout << "counter - " << counter << endl;
		exit(1);	
	}
	}
	counter++;
}
int main(int argc, char* argv[]) {
	cout << "# of Parameters\n" << argc - 1 << endl;
	cout << "Parameters\n";
	string h;
	for (int i = 1; i < argc; i++)
	{
		cout << i;
		cout << "\n";
		//cout << argv[i];
		//cout << "\n";  
		stringstream ss;
		string s;
		ss << argv[i];
		ss >> s;
		//cout << "Detect flag:" << endl << s.substr(0, 3) << endl;
		if (s.substr(0, 3) == "-h=")
		{
			h = s.substr(3);
		}
		else if (s.substr(0, 4) == "-si=")
		{
			
			int i; 
			istringstream(s.substr(4)) >> i;
			si = i;
		}
		else if (s.substr(0, 4) == "-fi=")
		{
			int i; 
			istringstream(s.substr(4)) >> i;
			fi = i; 
		}
		else
		{
			cout << "Unrecognized parameter - " << s << endl;	
		}
		cout << s << endl;	
	}
	cout << "------------\n";
    decrypt(string(h));
    return EXIT_SUCCESS;
}
