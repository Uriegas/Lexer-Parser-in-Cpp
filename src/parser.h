#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <bits/stdc++.h> 
#include <queue>
#include <stack>

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

//Just for using names instead of numbers in the code to tokenize the string
enum STRING{    NUMBER, VARIABLE, FUNCTION, OPERATOR, OPEN_FUNC, CLOSE_FUNC, 
                OPEN_VAR, CLOSE_VAR, OPEN_PAR, CLOSE_PAR, SEPARATOR             };

enum ERRORS{    NOERROR = 1, SYNTAXERROR, MISSING_VARIABLE, MISSING_BRACKET, 
                MISSING_PARENTHESIS, MISSING_COMMA, MISSING_FUNCTION            };

enum PARENT{    UNARY, BINARY   };

//Simple Data Structure for tokenization
struct tokens{
    int ID;
    std::string value;
};

struct vector_error{
    std::vector<tokens> vector;
    int error;
};

//Analize and porcess string and also retrieve errors
vector_error lexer(std::string string);
std::queue <tokens> parser(std::vector <tokens> string);
float evaluate(std::queue<tokens> string, float lower, float upper);
void return_error(const int& err);

std::ostream& operator<<(std::ostream& out, std::vector<tokens>& vector_token);
std::ostream& operator<<(std::ostream& output, std::queue<tokens> vector_token);

#endif //PARSER_H