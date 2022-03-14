// FNTASTIC_Test1.cpp : Here is a program to transform strings into a bunch of '('s and ')'s. I promise there is logic behind this.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<char> vectorFromString(string& input);
void printVector(vector<char> input);
void makeCharsLowercase(string& chars);

string transformString_A(string& input);
string transformString_B(string& input);
string transformString_C(string& input);

int main()
{   
	c:
	cout << "Enter any text:\n";
    //---------------
    //take input
    string input;
	getline(cin, input);
  
	//---------------
	//algorithms to transform the input string into string with '('s and ')'s
	makeCharsLowercase(input);
    const string output_a = transformString_A(input);
	const string output_b = transformString_B(input);
	const string output_c = transformString_C(input);

	//---------------
	//print result and start again
	printf("a: %s \nb: %s\nc: %s\n", output_a.c_str(), output_b.c_str(), output_c.c_str());

	goto c;
}

//--------------------------------
// get chars vector from string
vector<char> vectorFromString(string& input)
{
	vector<char> input_vec(input.begin(), input.end());
	return input_vec;
}

//--------------------------------
//print vector of chars
void printVector(vector<char> input)
{
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		cout << input[i] << endl;
	}
}

//--------------------------------
//make all the chars in vector lowercase
void makeCharsLowercase(string& chars)
{
	for (char& c : chars)
	{
		if (isupper(c)) c = tolower(c);
	}
}

//--------------------------------
//Algorithm A | Complexity: O(N^2)
string transformString_A(string& const input)
{
	string result = "";
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		for (unsigned int j = 0; j < input.size(); ++j)
		{
			if (input[i] == input[j] && i != j)
			{
				result.push_back(')');
				break;
			}

			if (j == input.size() - 1)
			{
				result.push_back('(');
				break;
			}
		}
	}

	return result;
}

//--------------------------------
//Algorithm B | Complexity: O(N)
string transformString_B(string& const input)
{
	string result = "";
	map<char, unsigned int> charsNum;

	for (auto c : input)
	{
		++charsNum[c];
	}
	
	for (auto c : input)
	{
		if (charsNum[c] > 1) result.push_back(')');
		else result.push_back('(');
	}

	return result;
}

//--------------------------------
//Algorithm C | Complexity: O(N)
string transformString_C(string& const input)
{
	string result = string(input.size(), '(');
	
	set<char> uniqueChars;
	set<char> repeatingChars;

	for (unsigned int i = 0; i < input.size(); ++i)
	{
		set<char>::iterator it_unique = uniqueChars.find(input[i]);
		set<char>::iterator it_repeating = repeatingChars.find(input[i]);
		if (it_repeating != repeatingChars.end())
		{
			continue;
		}
		else if (it_unique == uniqueChars.end() && it_repeating == repeatingChars.end())
		{
			uniqueChars.insert(input[i]);
		}
		else
		{
			uniqueChars.erase(it_unique);
			repeatingChars.insert(input[i]);
		}
	}

	for (unsigned int i = 0; i < input.size(); ++i)
	{
		if (repeatingChars.find(input[i]) != repeatingChars.end())
		{
			result[i] = ')';
		}
	}

	return result;
}