// MA2_in_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
#include "Tokenizer.h"
#include <vector>
#include <map>
#include <functional>
#include "MA2_in_cpp.h"
//#include <Eigen/Eigen/Dense> 
//TODO: Expand MA2 with imaginary numbers

using namespace std;


map<string, function<double(double)>> functions_1 = {
       {"sin", static_cast<double(*)(double)>(&sin)},
       { "cos", static_cast<double(*)(double)>(&cos) },
       { "exp", static_cast<double(*)(double)>(&exp) },
        {"log", static_cast<double(*)(double)>(&log)},
        {"abs", static_cast<double(*)(double)>(&abs)}
};
map<string, function<double(double)>> functions_n = {
       {"sin", static_cast<double(*)(double)>(&sin)},
       { "cos", static_cast<double(*)(double)>(&cos) }
}; //TODO: Implement functions_n


double arglist(Tokenizer& tok, map < string, double >& variables)
{
    return 0; //TODO: Implement arglist
}
double statement(Tokenizer& tok, map< string, double >& variables)
{
    if (tok.is_at_end()) { return 0; }
    double result = assignment(tok,variables);
    if (!tok.is_at_end()) { throw SyntaxError("Characters left in statement"); }
    return result;
}
double assignment(Tokenizer& tok, map< string, double >& variables)
{
    double result = expression(tok, variables);
    while (tok.get_current() == "=") {
        tok.next();
        if (!tok.is_name()) { throw SyntaxError("Incorrenct Assignment "); }
        variables[tok.get_current()] = result;
        tok.next();
    }
    return result;
}
double expression(Tokenizer& tok, map < string, double >& variables) {
    double result = term(tok, variables);
    string curr = tok.get_current();
    while (curr == "+" || curr == "-")
    {
        tok.next();
        if (curr == "+") { result = result + term(tok, variables); }
        else if (curr == "-") { result = result - term(tok, variables); }
        curr = tok.get_current();
    }
     return result;
}
double term(Tokenizer& tok, map < string, double >& variables) {
    double result = factor(tok, variables);
    string curr = tok.get_current();
    while (curr == "*" || curr == "/") {
        tok.next();
        if (curr == "*") { result = result * factor(tok, variables); }
        else if (curr == "/") { result = result / factor(tok, variables); }
        curr = tok.get_current();
    }
    return result;
}
double factor(Tokenizer& tok, map <string,double >& variables)
{
    string curr = tok.get_current();
    double result{};
    if (curr == "(") 
    {
        tok.next();
        result = assignment(tok, variables);
        if (tok.get_current() != ")") {
            throw SyntaxError("Expected )");
        }
        else {
            tok.next();
        }
    }
    else if (functions_1.count(curr)) 
    {
        tok.next();
        if (tok.get_current() != "(") { throw SyntaxError("No perenthesis after function call"); }
        tok.next();
        double tempres = assignment(tok, variables);
        result = functions_1[curr](tempres);
        tok.next();
 
    }
    else if (functions_n.count(curr))
    {
    //TODO: Implement multifunctions in factor
    }
    else if (tok.is_name())
    {   
        if (!variables.count(tok.get_current())) { throw SyntaxError("Undeclared Variable!"); }
        result = variables[tok.get_current()];
        tok.next();
    }
    else if (tok.is_number())
    {
        result = stod(tok.get_current());
        tok.next();
    }
    else if (curr == "-")
    {
        tok.next();
        result = -factor(tok, variables);
    }
    else
    {
        throw SyntaxError("Expected number or '('");
    }

    return result;
}




int main()
{

    map < string, double > variables = { {"ans", 0 }, {"PI",3.1415}, {"E",2.7182 }};


    while (true)
    {
        Tokenizer tok;
        string input;
        cout << "Enter statement: " << "\n";
        getline(cin, input);
        try
        {
            tok = Tokenizer(input);
            if (tok.get_current() == "quit") { return 0; }
            double result = statement(tok, variables);
            variables["ans"] = result;
            cout << "Result: " << result << "\n";

        }
        catch (SyntaxError error)
        {
            cout << error.what() << "\n";
        }
        catch (TokenError error)
        {
            cout << error.what() << "\n";
        }
    }
        

    
    

    
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
