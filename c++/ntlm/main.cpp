#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <cmath>
using namespace std;
//Init values
#define INIT_A 0x67452301
#define INIT_B 0xefcdab89
#define INIT_C 0x98badcfe
#define INIT_D 0x10325476
 
#define SQRT_2 0x5a827999
#define SQRT_3 0x6ed9eba1
 
unsigned int nt_buffer[16];
unsigned int output[4];
char hex_format[33];
char itoa16[17] = "0123456789ABCDEF";
char chars[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-', '='};
string t;
int charsetLength;
int si = 0;
int fi = 0;
int minpw = 0;
int maxpw = 0; 
string sc = "";
string fc = ""; 
int maxChars = 15;
//unsigned long long int counter = 4294967295; 
unsigned long long int counter = 0;
unsigned long long int max_counter = 100000000;
unsigned long long int distancei = 0; 
bool start_reached = false; 
//bool counterplusplus = true; 
void checkPassword(string password);
void recurse(int width, int position, string baseString);
void decrypt(string input)
{
	cout << "Decrypt Input:" << endl << input << endl;
    t = input;
    charsetLength = sizeof(chars);
    cout << "charset length: " << charsetLength << endl;
    cout << "charset: " << chars << endl;
    cout << "maxchar length: " << maxChars << endl;
    for(int i=0;i<maxChars+1;i++) {
    	if ((minpw == 0 || i >= minpw) && (maxpw == 0 || i <= maxpw))
    	{
	      cout << "checking passwords width [" << i << "]..." << endl;
	      recurse(i,0,"");
      	}
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
void NTLM(char *key)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Prepare the string for hash calculation
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int i = 0;
	int length = strlen(key);
	memset(nt_buffer, 0, 16*4);
	//The length of key need to be <= 27
	for(; i<length/2; i++)	
		nt_buffer[i] = key[2 * i] | (key[2 * i + 1] << 16);
 
	//padding
	if(length % 2 == 1)
		nt_buffer[i] = key[length - 1] | 0x800000;
	else
		nt_buffer[i] = 0x80;
	//put the length
	nt_buffer[14] = length << 4;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// NTLM hash calculation
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned int a = INIT_A;
	unsigned int b = INIT_B;
	unsigned int c = INIT_C;
	unsigned int d = INIT_D;
 
	/* Round 1 */
	a += (d ^ (b & (c ^ d)))  +  nt_buffer[0]  ;a = (a << 3 ) | (a >> 29);
	d += (c ^ (a & (b ^ c)))  +  nt_buffer[1]  ;d = (d << 7 ) | (d >> 25);
	c += (b ^ (d & (a ^ b)))  +  nt_buffer[2]  ;c = (c << 11) | (c >> 21);
	b += (a ^ (c & (d ^ a)))  +  nt_buffer[3]  ;b = (b << 19) | (b >> 13);
 
	a += (d ^ (b & (c ^ d)))  +  nt_buffer[4]  ;a = (a << 3 ) | (a >> 29);
	d += (c ^ (a & (b ^ c)))  +  nt_buffer[5]  ;d = (d << 7 ) | (d >> 25);
	c += (b ^ (d & (a ^ b)))  +  nt_buffer[6]  ;c = (c << 11) | (c >> 21);
	b += (a ^ (c & (d ^ a)))  +  nt_buffer[7]  ;b = (b << 19) | (b >> 13);
 
	a += (d ^ (b & (c ^ d)))  +  nt_buffer[8]  ;a = (a << 3 ) | (a >> 29);
	d += (c ^ (a & (b ^ c)))  +  nt_buffer[9]  ;d = (d << 7 ) | (d >> 25);
	c += (b ^ (d & (a ^ b)))  +  nt_buffer[10] ;c = (c << 11) | (c >> 21);
	b += (a ^ (c & (d ^ a)))  +  nt_buffer[11] ;b = (b << 19) | (b >> 13);
 
	a += (d ^ (b & (c ^ d)))  +  nt_buffer[12] ;a = (a << 3 ) | (a >> 29);
	d += (c ^ (a & (b ^ c)))  +  nt_buffer[13] ;d = (d << 7 ) | (d >> 25);
	c += (b ^ (d & (a ^ b)))  +  nt_buffer[14] ;c = (c << 11) | (c >> 21);
	b += (a ^ (c & (d ^ a)))  +  nt_buffer[15] ;b = (b << 19) | (b >> 13);
 
	/* Round 2 */
	a += ((b & (c | d)) | (c & d)) + nt_buffer[0] +SQRT_2; a = (a<<3 ) | (a>>29);
	d += ((a & (b | c)) | (b & c)) + nt_buffer[4] +SQRT_2; d = (d<<5 ) | (d>>27);
	c += ((d & (a | b)) | (a & b)) + nt_buffer[8] +SQRT_2; c = (c<<9 ) | (c>>23);
	b += ((c & (d | a)) | (d & a)) + nt_buffer[12]+SQRT_2; b = (b<<13) | (b>>19);
 
	a += ((b & (c | d)) | (c & d)) + nt_buffer[1] +SQRT_2; a = (a<<3 ) | (a>>29);
	d += ((a & (b | c)) | (b & c)) + nt_buffer[5] +SQRT_2; d = (d<<5 ) | (d>>27);
	c += ((d & (a | b)) | (a & b)) + nt_buffer[9] +SQRT_2; c = (c<<9 ) | (c>>23);
	b += ((c & (d | a)) | (d & a)) + nt_buffer[13]+SQRT_2; b = (b<<13) | (b>>19);
 
	a += ((b & (c | d)) | (c & d)) + nt_buffer[2] +SQRT_2; a = (a<<3 ) | (a>>29);
	d += ((a & (b | c)) | (b & c)) + nt_buffer[6] +SQRT_2; d = (d<<5 ) | (d>>27);
	c += ((d & (a | b)) | (a & b)) + nt_buffer[10]+SQRT_2; c = (c<<9 ) | (c>>23);
	b += ((c & (d | a)) | (d & a)) + nt_buffer[14]+SQRT_2; b = (b<<13) | (b>>19);
 
	a += ((b & (c | d)) | (c & d)) + nt_buffer[3] +SQRT_2; a = (a<<3 ) | (a>>29);
	d += ((a & (b | c)) | (b & c)) + nt_buffer[7] +SQRT_2; d = (d<<5 ) | (d>>27);
	c += ((d & (a | b)) | (a & b)) + nt_buffer[11]+SQRT_2; c = (c<<9 ) | (c>>23);
	b += ((c & (d | a)) | (d & a)) + nt_buffer[15]+SQRT_2; b = (b<<13) | (b>>19);
 
	/* Round 3 */
	a += (d ^ c ^ b) + nt_buffer[0]  +  SQRT_3; a = (a << 3 ) | (a >> 29);
	d += (c ^ b ^ a) + nt_buffer[8]  +  SQRT_3; d = (d << 9 ) | (d >> 23);
	c += (b ^ a ^ d) + nt_buffer[4]  +  SQRT_3; c = (c << 11) | (c >> 21);
	b += (a ^ d ^ c) + nt_buffer[12] +  SQRT_3; b = (b << 15) | (b >> 17);
 
	a += (d ^ c ^ b) + nt_buffer[2]  +  SQRT_3; a = (a << 3 ) | (a >> 29);
	d += (c ^ b ^ a) + nt_buffer[10] +  SQRT_3; d = (d << 9 ) | (d >> 23);
	c += (b ^ a ^ d) + nt_buffer[6]  +  SQRT_3; c = (c << 11) | (c >> 21);
	b += (a ^ d ^ c) + nt_buffer[14] +  SQRT_3; b = (b << 15) | (b >> 17);
 
	a += (d ^ c ^ b) + nt_buffer[1]  +  SQRT_3; a = (a << 3 ) | (a >> 29);
	d += (c ^ b ^ a) + nt_buffer[9]  +  SQRT_3; d = (d << 9 ) | (d >> 23);
	c += (b ^ a ^ d) + nt_buffer[5]  +  SQRT_3; c = (c << 11) | (c >> 21);
	b += (a ^ d ^ c) + nt_buffer[13] +  SQRT_3; b = (b << 15) | (b >> 17);
 
	a += (d ^ c ^ b) + nt_buffer[3]  +  SQRT_3; a = (a << 3 ) | (a >> 29);
	d += (c ^ b ^ a) + nt_buffer[11] +  SQRT_3; d = (d << 9 ) | (d >> 23);
	c += (b ^ a ^ d) + nt_buffer[7]  +  SQRT_3; c = (c << 11) | (c >> 21);
	b += (a ^ d ^ c) + nt_buffer[15] +  SQRT_3; b = (b << 15) | (b >> 17);
 
	output[0] = a + INIT_A;
	output[1] = b + INIT_B;
	output[2] = c + INIT_C;
	output[3] = d + INIT_D;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Convert the hash to hex (for being readable)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for(i=0; i<4; i++)
	{
		int j = 0;
		unsigned int n = output[i];
		//iterate the bytes of the integer		
		for(; j<4; j++)
		{
			unsigned int convert = n % 256;
			hex_format[i * 8 + j * 2 + 1] = itoa16[convert % 16];
			convert = convert / 16;
			hex_format[i * 8 + j * 2 + 0] = itoa16[convert % 16];
			n = n / 256;
		}	
	}
	//null terminate the string
	hex_format[33] = 0;
}
string encrypt_ntlm(string input)
{
    char * inputchar = new char[input.length() + 1];
    strcpy(inputchar, input.c_str());
    NTLM(inputchar);
    delete[] inputchar;
    return hex_format;
    //return (md5(input));
}
void checkPassword(string password) {
	if (max_counter == 0 && counter >= 100000000)
	{
		counter = 0;
	}
	if (counter >= max_counter && max_counter != 0)
	{
		if (start_reached == false)
		{
			cout << "max_counter reached start_reached is false - reset" << endl;
			if (si > 0)
			{
				si = si - counter; 
			}
			if (fi > 0)
			{
				fi = fi - counter; 
			}
			counter = 0;
			checkPassword(password); 
		}
		else
		{
			cout << "max_counter reached - stopping" << endl;
			exit(1); 
		}
	}
	else
	{
	if (sc != "" && password == sc)
	{
		start_reached = true;
		counter = 1; 
		si = 0; 
	}
	if (counter >= si)
	{
		//cout << "counter check - " << counter << endl; 
		if (start_reached == false && sc == "")
		{
			cout << "start_reached = true, counter reset" << endl; 
			start_reached = true; 
			if (si != 0 && fi != 0)
			{
				if (distancei == 0)
				{
				distancei = abs(fi - si) + 1; 	
				}
				fi = fi - si; 
			}
			else if (si == 0 && fi != 0)
			{
				if (distancei == 0)
				{
				distancei = fi + 1; 
				}	
			}
			si = 0;
			cout << "distancei set" << endl << distancei << endl; 
			
			counter = 0; 
			cout << "counter reset" << endl; 
			cout << counter << endl; 
			//return; 
		}
		//cout << "counter check 2- " << counter << endl; 
	//if (counter <= fi || fi == 0 && (distancei == 0 || counter <= distancei))
	if (distancei == 0 || counter <= distancei && start_reached == true)
	{
		
    string md5hash = encrypt_ntlm(password);
	//cout << counter << ":" << md5hash << endl;
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
		cout << distancei << endl; 
		cout << "password" << endl << password << endl; 
		cout << "FAIL" << endl; 
		exit(1);	
	}
	}
	if (fc != "" && password == fc)
	{
		cout << "final character - " << fc << " reached. password is " << password << endl; 
		cout << "counter - " << counter << endl; 
		exit(1);
	}
	counter++; 
	}
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
		else if (s.substr(0, 4) == "-mc=")
		{
			istringstream(s.substr(4)) >> max_counter;
		}
		else if (s.substr(0, 4) == "-di=")
		{
			istringstream(s.substr(4)) >> distancei;	
		}
		else if (s.substr(0, 4) == "-sc=")
		{
			sc = s.substr(4);
		}
		else if (s.substr(0, 4) == "-fc=")
		{
			fc = s.substr(4); 
		}
		else if (s.substr(0, 3) == "-n=")
		{
			istringstream(s.substr(3)) >> minpw; 
		}
		else if (s.substr(0, 3) == "-x=")
		{
			istringstream(s.substr(3)) >> maxpw; 
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
