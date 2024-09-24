#pragma once
#include <string>
#include <vector>
	enum TokenType {
	OP,
	NAME,
	NUMBER,
	SEPERATOR,
	EOL,
	COMMENT,
	ERRTOKEN

	};
	struct Token {
		int Type;
		std::string value;

	};
	class Tokenizer
	{
	private:
		int ind = 0;
		void tokenize(std::string input);
		void handleToken(std::string::iterator& it, std::string& tempString, std::string& input, int& retFlag);
		std::vector <Token> Tokens;
		std::vector<char> Operators = { '+', '-', '*' , '/' };
		std::vector<char> Separators = { '(', ')' };
		int parenthesisInt;
		void checkErrors();
	public:
		Tokenizer(std::string input);
		std::string get_current();
		std::string get_previous();
		bool next();
		bool is_name();
		bool is_number();
		bool is_at_end();
		void print();


		Tokenizer() = default;
	};
	class SyntaxError : public std::exception {
	public:
		const char* mess;
		SyntaxError(const char* message)
		{
			mess = message;
		}
		const char* what() {
			return mess;
		}
	};

	class TokenError : public std::exception {
	public:
		const char* mess;
		TokenError(const char* message)
		{
			mess = message;
		}
		const char* what() {
			return mess;
		}
	};

	
	




