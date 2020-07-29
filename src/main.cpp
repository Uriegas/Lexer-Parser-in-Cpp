#include <iostream>
#include <bits/stdc++.h> 
#include <queue>
#include <stack>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Lexer_Token Parser -> String Formula Analyzer

//The code is divided into:
//Enums
//Support functions
//lexer_part_1 function     tokenizer
//lexer_part_2 function     error handling
//Main function

//Just for using names instead of numbers in the code to tokenize the string
enum STRING{ NUMBER, VARIABLE, FUNCTION, OPERATOR, OPEN_FUNC, CLOSE_FUNC, OPEN_VAR, CLOSE_VAR, OPEN_PAR, CLOSE_PAR, SEPARATOR };

enum ERRORS{ NOERROR = 1, SYNTAXERROR, MISSING_VARIABLE, MISSING_BRACKET, MISSING_PARENTHESIS, MISSING_COMMA, MISSING_FUNCTION };

//Simple Data Structure for tokenization
struct tokens{
    int ID;
    std::string value;
};

//All of this are bool functions implemented in the lexical analyzer function
bool operator==(const tokens& compare1, const tokens compare2){
    if((compare1.ID == compare2.ID) && (compare1.value == compare2.value))
        return true;
    else
        return false;
}

bool is_a_number(char letter){ //Consider '.' as a number for make easier to save float numbers
    if(letter == '1' || letter == '2' || letter == '3' || letter == '4' || letter == '5' ||
       letter == '6' || letter == '7' || letter == '8' || letter == '9' || letter == '0' || letter == '.'){
        return true;
       }
    else{
        return false;
    }
}

bool is_a_separator(char letter){
    if(letter == ',' || letter == '{' || letter == '}' || letter == '_'){// '_' case is for the - sign in negative numbers
        return true;
       }
    else{
        return false;
    }
}

bool is_a_parenthesis(char letter){
    if(letter == '(' || letter == ')'){//Special case because there are to types of parenthesis
           return true;
       }
    else{
        return false;
    }
}

bool is_an_operator(char letter) {//There are not unary operators here
    if(letter == '*' || letter == '/' || letter == '+' ||
       letter == '-' || letter == '%'){
           return true;
       }
    else{
        return false;
    }
}
//Just a function that returns a token when it found an special character
tokens select_special_character(char a){
    tokens res;
    std::string ch;
    switch (a){
    case '{':
        res = {OPEN_VAR, (ch += a)};
        break;
    case '}':
        res = {CLOSE_VAR, (ch += a)};
        break;
    case ',':
        res = {SEPARATOR, (ch += a)};
        break;
    default:
        break;
    }
    return res;
}

//To future implementation
std::string evaluate_negative_sign(){}

//Lexical analyzer, lexer or tokenizer function
//It scans a string and divides it into tokens
std::vector <tokens> lexer_part_1(std::string string){
    std::vector <tokens> tokenized_string;
    tokens current_token;
    std::string buffer;
    std::string char_to_string;
    int parenthesis_flag = 0;

    string = '(' + string;
    char_to_string += '(';
    tokenized_string.push_back({OPEN_PAR, char_to_string});
    char_to_string.clear();

    for(int i = 1; i < string.size(); i++){
        //We are reading an sepecial character
        if( is_a_separator(string[i]) ){
            tokenized_string.push_back(select_special_character(string[i]));
            continue;
        }
        //We are reading an operator simply store it
        else if( is_an_operator(string[i]) ){
            char_to_string += string[i];
            current_token = {OPERATOR, char_to_string};
            tokenized_string.push_back(current_token);
            char_to_string.clear();
            continue;
        }
        //We are reading a number
        //It could be part of a real number or variable
        //Ej. number = 20549; var = {myvar1}
        else if(is_a_number(string[i])){
            char_to_string += '{';
            current_token = {OPEN_VAR, char_to_string};
            //We are in a variable
            if(tokenized_string.back() == current_token){
                buffer += string[i];//Fill bufer until we find the end of the variable
                if(string[i+1] == '}'){//We are close to exit the variable
                    current_token = {VARIABLE, buffer};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                    buffer.clear();
                }
            }
            //This else is that we are reading a real number
            else{
                buffer+= string[i];
                //This if is that we are finishing reading the real number, so lets store it
                if( is_an_operator(string[i+1]) || is_a_separator(string[i+1]) || (string[i+1] == ')') ){
                    current_token = {NUMBER, buffer};
                    tokenized_string.push_back(current_token);
                    buffer.clear();
                }
            }
            char_to_string.clear();
            continue;
        }
        if(is_a_parenthesis(string[i])){
            if(string[i] == '('){
                if(tokenized_string.back().ID == FUNCTION){//We found a function parenthesis
                    parenthesis_flag = 1; //Turn the flag on
                    char_to_string += string[i];
                    current_token = {OPEN_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
                else{//We found an asocciative parenthesis
                    parenthesis_flag = 0; //Turn the flag off
                    char_to_string += string[i];
                    current_token = {OPEN_PAR, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
            }
            else if(string[i] == ')'){
                if(parenthesis_flag == 1){//We are reading a closing function parhentesis
                    parenthesis_flag = 0; //Turn the flag off
                    char_to_string += string[i];
                    current_token = {CLOSE_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
                else if(parenthesis_flag == 0){//We found a closing associative parenthesis
                    parenthesis_flag = 1; //Turn the flag off
                    char_to_string += string[i];
                    current_token = {CLOSE_PAR, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
            }
            continue;
        }
        //If nothing of the above, then we are reading a letter
        //This menas a function or a variable
        else{
            buffer += string[i];
            if(string[i+1] == '('){//We are terminating reading a function
                current_token = {FUNCTION, buffer};
                tokenized_string.push_back(current_token);
                buffer.clear();
            }
            else if(string[i+1] == '}'){//We are terminating reading a variable
                current_token = {VARIABLE, buffer};
                tokenized_string.push_back(current_token);
                buffer.clear();
            }
        }
    }
    tokenized_string.erase(tokenized_string.begin());
    return tokenized_string;
}

//Prints the kind of error
void return_error(int err){
    switch (err){
    case SYNTAXERROR:
        std::cout << "Syntax Error, maybe a missing operand";
        break;
    case MISSING_VARIABLE:
        std::cout << "Error in variable name, you should enter just letters and numbers in it";
        break;
    case MISSING_BRACKET:
        std::cout << "Missing bracket: '{' or '}'";
        break;
    case MISSING_PARENTHESIS:
        std::cout << "Missing parenthesis '(' or ')'";
        break;
    case MISSING_COMMA:
        std::cout << "Error in function parameters, maybe there is a missing comma or closing parenthesis";
        break;
    case MISSING_FUNCTION:
        std::cout << "Misspelling in function prototype, this function does not exist";
        break;
    default:
        std::cout << "There is no error";
        break;
    }
    std::cout << "\n";
}
//Second iteration over string
//Returns 1 if there is not an error
int lexer_part_2(std::vector <tokens>& string){
    int var_flag = 0;
    int open_parenthesis = 0, closing_parenthesis = 0;
    int open_func = 0, closing_func = 0;
    for(int i = 0; i < string.size(); i++){
        if( string[i].ID == OPEN_VAR){
            string.erase(string.begin()+i);
            var_flag = 2;
            --i;
            continue;
        }
        else if( var_flag == 2 ){
            if( string[i].ID == VARIABLE )
                var_flag --;
            else
                return MISSING_BRACKET;
        }
        else if( var_flag == 1 ){
            if( string[i].ID == CLOSE_VAR ){
                string.erase(string.begin()+i);
                var_flag--;
                --i;
                continue;
            }
            else
                return MISSING_VARIABLE;
        }
        else if(string[i].ID == OPEN_PAR)
            open_parenthesis++;
        else if(string[i].ID == CLOSE_PAR)
            closing_parenthesis++;
        else if(string[i].ID == OPEN_FUNC)
            open_func++;
        else if(string[i].ID == CLOSE_FUNC)
            closing_func++;
        else if( string[i].ID == CLOSE_VAR && var_flag != 1 )
            return MISSING_BRACKET;
    }
    if(open_parenthesis != closing_parenthesis)//Not matching parenthesis number
        return MISSING_PARENTHESIS;
    else if (open_func != closing_func)
        return MISSING_FUNCTION;
    else
        return NOERROR;//We ended the looping without errors
}

//Third interation over string, now to convert functions to operators
//Also evaluates the correctness of the syntax
std::vector<tokens> lexer_part_3(std::vector <tokens> string){
    for(int i = 0; i < string.size(); i++){
        if( string[i].ID == OPEN_FUNC || string[i].ID == CLOSE_FUNC){
            string.erase(string.begin()+i);
            i-2;
        }
    }
    return string;
}
//std::stack <tokens> parser(std::vector <tokens> string){}

int main(){
    int lex2; //Variable to save the error result of lex2
    std::string string = "pow(({yosoy}+5),2)/(sin(4.5)*{elpofe123})";
    std::vector<tokens> tokenized_string = lexer_part_1(string);
    std::cout << "First String Tokenization\t " << string << "\t tokenized to: \n";

    for(int i = 0; i < tokenized_string.size(); i++)
        std::cout << tokenized_string[i].ID << "\t" << tokenized_string[i].value << "\n";
        
    lex2 = lexer_part_2(tokenized_string);

    if(lex2 == 1){
        std::cout << "Second String Iteration\t " << string << "\t tokenized to: \n";
        for(int i = 0; i < tokenized_string.size(); i++)
            std::cout << tokenized_string[i].ID << "\t" << tokenized_string[i].value << "\n";
    }
    else
        return_error(lex2);
}

/*
// function to split string into substrings on the 
// basis of delimiter and return the substrings 
// after split in a vector of strings
std::vector<std::string> split_string(std::string str, char dl){
    std::string word = ""; 
    // to count the number of split strings 
    int num = 0; 
    // adding delimiter character at the end 
    // of 'str' 
    str = str + dl; 
    // length of 'str' 
    int l = str.size(); 
    // traversing 'str' from left to right 
    std::vector<std::string> substr_list; 
    for (int i = 0; i < l; i++) { 
        // if str[i] is not equal to the delimiter 
        // character then accumulate it to 'word' 
        if (str[i] != dl) 
            word = word + str[i]; 
        else { 
            // if 'word' is not an empty string, 
            // then add this 'word' to the array 
            // 'substr_list[]' 
            if ((int)word.size() != 0) 
                substr_list.push_back(word); 
            // reset 'word' 
            word = ""; 
        } 
    } 
    // return the splitted strings 
    return substr_list; 
}

//This are the steps for creating the algorithm
//First, split the string into tokens (tokenization)
//Tokens can be numbers, operands, and parenthesis
//The algorithm reads tokens and uses the following logic
//If it is a number token, it is pushed on a number stack (or the output queue, if we were generating RPN)
//If it is an operator, pop operators from the operator stack and evaluate them with values from the number stack, until we reach one that has lower precedence. Then we push the original operator.
//In the case of a right associative operator, we also stop if we reach an operator of the same precedence.
//If it a left parenthesis, just push it.
//If it is a right parenthesis, we pop all operators (and evaluate them) until the matching left parenthesis. The parentheses are thrown away.
//After all tokens are read, the remaining operators on stack are popped and evaluated.

//https://en.wikipedia.org/wiki/Shunting-yard_algorithm
// with small adjustment for expressions in functions. Wiki example works only for constants as arguments
//Implementation on Java can be found at:
//https://github.com/vtsyvina/sim-it/blob/master/src/main/java/sim/grammar/SimItGrammarParser.java#L248-L326

//std::stack<std::string> stack = new stack<>();
//std::initializer_list<Token> result = new ArrayList<>();

//Tokenization Section
//Tokenizer Code
//Could create a data strucutre that tokenize the variables in the queue
//Ej. {x}, variable
//      +, operand
//      pow, function
std::queue <std::string> tokenizer(std::string& formula){
    std::queue<std::string> tokenized_formula;
    std::string buffer;

    for( int i = 0; i < formula.size(); i++){
        buffer += formula[i];
        if(formula[i-1] != operand()){
            if(formula[i] == '('){ //It is an openining parenthesis
                //It is a function
            }
            else{//It is a conjunction parenthesis
                tokenized_formula.push(buffer);
            }
        }
        else if (formula[i] == ')'){
            tokenized_formula.push(buffer);
        }
        else if (formula == '{'){ //Begins a variable
            buffer += formula[i];
            continue;
        }
        else if(formula == '}'){ //Its the end of a variable
            buffer += formula;
            tokenized_formula.push(buffer);
        }
        buffer.clear();
    }
}
for (Token token : tokens) {
    if (isNumber(token) || isIdentifier(token)) {
        result.add(token);
        continue;
    }
    if (isFunction(token)) {
        stack.push(token);
        continue;
    }


    // if OP(open parentheses) then put to stack
    if (isOP(token)) {
        stack.push(token);
        continue;
    }
    // CP(close parentheses) pop stack to result until OP
    if (isCP(token)) {
        Token cur = stack.pop();
        while (!isOP(cur)) {
            if (!isComma(cur)) {
                result.add(cur);
            }
            cur = stack.pop();
        }
        continue;
    }
    if (isBinaryOperation(token)) {
        if (!stack.empty()) {
            Token cur = stack.peek();
            while ((!isBinaryOperation(cur)
                    || (isBinaryOperation(cur) && hasHigherPriority(cur, token))
                    || (hasEqualPriority(cur, token) && isLeftAssociative(token)))
                    && !isOP(cur)
            ) {
                // no need in commas in resulting list if we now how many parameters the function need
                if (!isComma(cur)) {
                    result.add(cur);
                }

                stack.pop();
                if (!stack.empty()) {
                    cur = stack.peek();
                }
            }
        }
        stack.push(token);
        continue;
    }

    if (isComma(token)) {
        Token cur = stack.peek();
        while (!(isOP(cur) || isComma(cur))) {
            result.add(cur);
            stack.pop();
            if (!stack.empty()) {
                cur = stack.peek();//  don't pop if priority is less
            }
        }
        stack.push(token);

    }
}
while (!stack.empty()) {
    Token pop = stack.pop();
    if (!isComma(pop)) {
        result.add(pop);
    }

}
return result;
*/