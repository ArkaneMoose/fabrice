//c++ math library operating on large integers using strings
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cmath>
#include <sstream>
using namespace std;
string big_int_greater(string number1, string number2)
{
	if (number1.length() != number2.length())
	{
		if (number1.length() > number2.length())
		{
			return number1;
		}
		else
		{
			return number2;
		}
	}
	else
	{
		for (int i = 0; i < number1.length(); i++)
		{
			stringstream ssdigit1, ssdigit2;
			string sdigit1, sdigit2; 
			ssdigit1 << number1[i];
			ssdigit2 << number2[i];
			ssdigit1 >> sdigit1;
			ssdigit2 >> sdigit2; 
			int digit1, digit2;
			istringstream(sdigit1) >> digit1;
			istringstream(sdigit2) >> digit2; 
			bool same = true; 
			if (digit1 != digit2)
			{
				same = false; 
				if (digit1 > digit2)
				{
					return number1;
				}
				else
				{
					return number2;
				}
			}
			if (same == true)
			{
				return number1;
			}
		}
	}
}
string big_int_lesser(string number1, string number2)
{
	if (number1 == number2)
	{
		return number1;
	}
	else
	{
		string greater_int = big_int_greater(number1, number2);
		if (greater_int == number1)
		{
			return number2;
		}
		else
		{
			return number1; 
		}
	}
}
string big_int_add(string number1, string number2)
{
	if (number1.length() == number2.length())
	{
		string backward_result = ""; 
		int carryover = 0; 
		for (int i = number1.length() -1; i >= 0; i--)
		{
			stringstream ssdigit1, ssdigit2;
			string sdigit1, sdigit2; 
			ssdigit1 << number1[i];
			ssdigit2 << number2[i];
			ssdigit1 >> sdigit1;
			ssdigit2 >> sdigit2; 
			int digit1, digit2;
			istringstream(sdigit1) >> digit1;
			istringstream(sdigit2) >> digit2; 
			int newdigit = digit1 + digit2 + carryover; 
			//cout << "digit:" << newdigit << endl; 
			if (newdigit < 10)
			{
				carryover = 0;
				stringstream digitstringstream;
				string digitstring; 
				digitstringstream << newdigit;
				digitstringstream >> digitstring; 
				backward_result += digitstring; 
			}
			else if (newdigit >= 10 && i == 0)
			{
				stringstream digitstringstream;
				string digitstring; 
				digitstringstream << newdigit;
				digitstringstream >> digitstring; 
				backward_result += digitstring[1];
				backward_result += digitstring[0]; 
			}
			else
			{
				stringstream digitstringstream;
				string digitstring; 
				digitstringstream << newdigit;
				digitstringstream >> digitstring; 
				backward_result += digitstring[1];
				stringstream charstream;
				string charstring;
				charstream << digitstring[0];
				charstream >> charstring;
				istringstream(charstring) >> carryover; 
			}
		}
		return string(backward_result.rbegin(), backward_result.rend());
	}
	else
	{
		if (number1.length() > number2.length())
		{
			int difference = number1.length() - number2.length(); 
			string leadzero = "";
			for (int a = 0; a < difference; a++)
			{
				leadzero += "0";
			}
			number2 = leadzero + number2; 
			string backward_result = ""; 
			int carryover = 0; 
			for (int i = number1.length() -1; i >= 0; i--)
			{
				stringstream ssdigit1, ssdigit2;
				string sdigit1, sdigit2; 
				ssdigit1 << number1[i];
				ssdigit2 << number2[i];
				ssdigit1 >> sdigit1;
				ssdigit2 >> sdigit2; 
				int digit1, digit2;
				istringstream(sdigit1) >> digit1;
				istringstream(sdigit2) >> digit2; 
				int newdigit = digit1 + digit2 + carryover; 
				//cout << "digit:" << newdigit << endl; 
				if (newdigit < 10)
				{
					carryover = 0;
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring; 
					backward_result += digitstring; 
				}
				else if (newdigit >= 10 && i == 0)
				{
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring;
					backward_result += digitstring[1];
					backward_result += digitstring[0]; 
				}
				else
				{
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring;
					backward_result += digitstring[1];
					stringstream charstream;
					string charstring;
					charstream << digitstring[0];
					charstream >> charstring;
					istringstream(charstring) >> carryover; 
				}
			}
			return string(backward_result.rbegin(), backward_result.rend());
		}
		else
		{
			int difference = number2.length() - number1.length();
			string leadzero = "";
			for (int a = 0; a < difference; a++)
			{
				leadzero += "0";
			}
			number1 = leadzero + number1; 
			string backward_result = ""; 
			int carryover = 0; 
			for (int i = number1.length() -1; i >= 0; i--)
			{
				stringstream ssdigit1, ssdigit2;
				string sdigit1, sdigit2; 
				ssdigit1 << number1[i];
				ssdigit2 << number2[i];
				ssdigit1 >> sdigit1;
				ssdigit2 >> sdigit2; 
				int digit1, digit2;
				istringstream(sdigit1) >> digit1;
				istringstream(sdigit2) >> digit2; 
				int newdigit = digit1 + digit2 + carryover; 
				//cout << "digit:" << newdigit << endl; 
				if (newdigit < 10)
				{
					carryover = 0;
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring;
					backward_result += digitstring; 
				}
				else if (newdigit >= 10 && i == 0)
				{
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring;
					backward_result += digitstring[1];
					backward_result += digitstring[0]; 
				}
				else
				{
					stringstream digitstringstream;
					string digitstring; 
					digitstringstream << newdigit;
					digitstringstream >> digitstring;
					backward_result += digitstring[1];
					stringstream charstream;
					string charstring;
					charstream << digitstring[0];
					charstream >> charstring;
					istringstream(charstring) >> carryover; 
				}
			}
			return string(backward_result.rbegin(), backward_result.rend());
		}
}
}
