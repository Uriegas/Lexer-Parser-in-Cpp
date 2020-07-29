#include <iostream>
#include <bits/stdc++.h> 
#include <queue>
#include <stack>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Lexer_Token Parser -> String Formula Analyzer

//The code is divided into:
//Enums and Struct
//Support functions
//lexer_part_1 function     tokenizer
//lexer_part_2 function     error handling
//lexer_part_3 function     treat functions
//lexer function            combining 3 lexer parts
//Main function

//Just for using names instead of numbers in the code to tokenize the string
enum STRING{    NUMBER, VARIABLE, FUNCTION, OPERATOR, OPEN_FUNC, CLOSE_FUNC, 
                OPEN_VAR, CLOSE_VAR, OPEN_PAR, CLOSE_PAR, SEPARATOR             };

enum ERRORS{    NOERROR = 1, SYNTAXERROR, MISSING_VARIABLE, MISSING_BRACKET, 
                MISSING_PARENTHESIS, MISSING_COMMA, MISSING_FUNCTION            };

//Simple Data Structure for tokenization
struct tokens{
    int ID;
    std::string value;
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 1 FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 2 FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Prints the kind of error
void return_error(int err){
    switch (err){
    case SYNTAXERROR:
        std::cout << "Syntax Error, maybe a bad operand input";
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

//To future implementation
std::string evaluate_negative_sign(){}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 3 FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Currently there is only one binary function
bool is_binary_function(tokens function){
    if(function.value == "pow")
        return true;
    else
        return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Lexical analyzer, lexer or tokenizer function
//It scans a string and divides it into tokens
std::vector <tokens> lexer_part_1(std::string string){
    std::vector <tokens> tokenized_string;
    tokens current_token;
    std::string buffer;
    std::string char_to_string;
    int parenthesis_flag = 0;
    int func_parenthesis_flag = 0;

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
                    func_parenthesis_flag++; //Turn the flag on
                    char_to_string += string[i];
                    current_token = {OPEN_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
                else{//We found an asocciative parenthesis
                    parenthesis_flag++; //Turn the flag on
                    char_to_string += string[i];
                    current_token = {OPEN_PAR, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
            }
            else if(string[i] == ')'){
                if(func_parenthesis_flag > 0){//We are reading a closing function parhentesis
                    func_parenthesis_flag--; //Turn the flag off
                    char_to_string += string[i];
                    current_token = {CLOSE_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                }
                else if(parenthesis_flag > 0){//We found a closing associative parenthesis
                    parenthesis_flag--; //Turn the flag off
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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Second iteration over string
//Returns 1 if there is not an error
int lexer_part_2(std::vector <tokens>& string){
    int var_flag = 0;
    int open_parenthesis = 0, closing_parenthesis = 0;
    int open_func = 0, closing_func = 0;
    for(int i = 0; i < string.size(); i++){
        //Check variables syntax correctness and eliminate brackets
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
        //Check operators correctness
        else if(string[i].ID == OPERATOR){
            if( (string[i-1].ID == FUNCTION) || (string[i-1].ID == OPERATOR) || (string[i+1].ID == OPERATOR)
                    || (string[i-1].ID == SEPARATOR) || (string[i+1].ID == SEPARATOR) ){
                return SYNTAXERROR;
            }
            continue;
        }
        //Check function and non function parenthesis correctness
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
    else if (open_func != closing_func)//Not matching function parenthesis
        return MISSING_FUNCTION;
    else
        return NOERROR;//We ended the looping without errors
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 3>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Third interation over string, now to convert functions to operators
//Also evaluates the correctness of the functions
int lexer_part_3(std::vector <tokens>& string){
    int comma_flag = 0;
    std::stack<tokens> func_stack;//Store functions to then replace commas by funcs (convert them to infix notation)

    for(int i = 0; i < string.size(); i++){
        //Treat unary functions
        if(string[i].ID == FUNCTION && is_binary_function(string[i]) == false ){
            if(string[i+1].ID == OPEN_FUNC){
                string.erase(string.begin()+i+1);
                continue;
            }
            else
                return MISSING_FUNCTION;
        }
        //Treat binary functions
        else if( string[i].ID == FUNCTION && is_binary_function(string[i]) && string[i+1].ID == OPEN_FUNC ) {
                func_stack.push(string[i]);
                string.erase(string.begin()+i);
                string.erase(string.begin()+i);
                comma_flag++;
                --i;
                continue;
        }
        //Treat commas
        else if( string[i].ID == SEPARATOR ){
            string[i] = func_stack.top();
            func_stack.pop();
            comma_flag--;
            continue;
        }
        //Treat closing parenthesis
        else if( string[i].ID == CLOSE_FUNC){
            string.erase(string.begin()+i);
            --i;
        }
    }
    //If all commas were not fullfiled then there is an error
    if(comma_flag != 0)
        return MISSING_FUNCTION;
    else
        return NOERROR;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
std::vector<tokens> lexer(std::string string){
    int error;
    std::vector<tokens> string_tokenized = lexer_part_1(string);

    error = lexer_part_2(string_tokenized);
    if( error != NOERROR )
        return_error(error);
    
    error = lexer_part_3(string_tokenized);
    if( error != NOERROR )
        return_error(error);

    return string_tokenized;
}
//std::stack <tokens> parser(std::vector <tokens> string){}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MAIN FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(){
    int lex2; //Variable to save the error result of lex2
//    std::string string = "pow((pow({yosoy},{string})),2)/(sin(4.5)*{elpofe123})";
    std::string string = "pow(pow({s},(2*4*3)),2)";
    std::vector<tokens> tokenized_string;

/*        
    lex2 = lexer_part_2(tokenized_string);

    //If there is no error the function returnerd 1
    if(lex2 == 1){
        std::cout << "String Iteration\t " << string << "\t tokenized to: \n";
        for(int i = 0; i < tokenized_string.size(); i++)
            std::cout << tokenized_string[i].ID << "\t" << tokenized_string[i].value << "\n";
    }
    else//If there is error evaluate wich one
        return_error(lex2);
        */
    tokenized_string = lexer(string);
    //Print vector
    std::cout << "String Tokenization\t " << string << "\t tokenized to: \n";
    for(int i = 0; i < tokenized_string.size(); i++)
        std::cout << tokenized_string[i].ID << "\t" << tokenized_string[i].value << "\n";
}