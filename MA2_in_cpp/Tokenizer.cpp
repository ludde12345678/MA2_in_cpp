#include "Tokenizer.h"
#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// public
Tokenizer::Tokenizer(std::string input)
{
	// set initial variables
	parenthesisInt = 0;

	// Tokenize

	tokenize(input);
	checkErrors();
}

void Tokenizer::print() 
{
	for (const auto& elem : Tokens) {
		std::cout << "\n" << elem.Type << " , " << elem.value << " \n ";
	}

}
string Tokenizer::get_current() 
{
	return Tokens[ind].value;
}

std::string Tokenizer::get_previous()
{
	return Tokens[ind-1].value;
}

bool Tokenizer::next()
{
	if (Tokens[ind].Type == EOL) {
		return false;
	}
	else {
		ind++;
		return true;
	}
}

bool Tokenizer::is_name()
{
	if (Tokens[ind].Type == NAME) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Tokenizer::is_number()
{
	if (Tokens[ind].Type == NUMBER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Tokenizer::is_at_end()
{
	if (Tokens[ind].Type == EOL) {
		return true;
	}
	else {
		return false;
	}
}

// private
void Tokenizer::tokenize(std::string input) {
	
	
	string tempString;
	string::iterator it;

	for (it = input.begin(); it != input.end(); it++)
	{
		try
		{
			int retFlag;
			handleToken(it, tempString, input, retFlag);
			if (retFlag == 3) continue;
		}
		catch (TokenError err)
		{
			Tokens.push_back({ ERRTOKEN, "ERR" });
			cout << err.what();
		}
		catch (const std::exception&)
		{
			Tokens.push_back({ ERRTOKEN, "ERR"});
			cout << ("Something went wrong with tokenization!\n");
		}
		

	}
	Tokens.push_back({EOL, "EOL" });

}

void Tokenizer::handleToken(std::string::iterator& it, std::string& tempString, std::string& input, int& retFlag)
{
	retFlag = 1;
	if (std::find(Operators.begin(), Operators.end(), *it) != Operators.end())
	{
		//If token is op
		Tokens.push_back({ OP, string(1,*it) });
		{ retFlag = 3; return; };
	}
	else if (std::find(Separators.begin(), Separators.end(), *it) != Separators.end())
	{
		//if token is separator
		if (*it == '(') { parenthesisInt++; }
		else { parenthesisInt--; };
		Tokens.push_back({ SEPERATOR, string(1,*it) });
		{ retFlag = 3; return; };
	}
	else if (isdigit(*it) || *it == '.')
	{//if token is num
		while (isdigit(*it) || *it == '.') {
			if (*it == '.' && std::find(tempString.begin(), tempString.end(), *it) != tempString.end()) {
				throw SyntaxError("Error, Broken float\n");
			}
			tempString += *it;
			it++;
			if (it == input.end()) { break; }
		}
		Tokens.push_back({ NUMBER, tempString });
		tempString = "";
		it--;

	}
	else if (*it == ' ')
	{
		//if token is whitespace
		{ retFlag = 3; return; };


	}
	else if (isalpha(*it))
	{	//if token is name
		while (isalpha(*it))
		{
			tempString += *it;
			it++;
			if (it == input.end()) { break; }
		}


		Tokens.push_back({ NAME, tempString });
		tempString = "";
		it--;
	}
	else
	{
		// Error, create Error token
		throw TokenError("Unknown Token\n");
	}
}

void Tokenizer::checkErrors()
{
	if (parenthesisInt != 0) { throw TokenError("Error, Unbalanced Perenthesis\n"); }
}

