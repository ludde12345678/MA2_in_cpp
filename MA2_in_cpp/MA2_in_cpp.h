#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <functional>
#include "Tokenizer.h"


double arglist(Tokenizer& tok, std::map<std::string, double>& variables);

double statement(Tokenizer& tok, std::map<std::string, double>& variables);

double assignment(Tokenizer& tok, std::map<std::string, double>& variables);

double expression(Tokenizer& tok, std::map<std::string, double>& variables);

double term(Tokenizer& tok, std::map<std::string, double>& variables);

double factor(Tokenizer& tok, std::map<std::string, double>& variables);

int main();
