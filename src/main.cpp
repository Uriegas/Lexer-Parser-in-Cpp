#include "parser.h"
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
//Parser function           Infix to Postfix Notation
//Evaluate function         Postfix to Result
//Main function
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 1 FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//All of this are bool functions implemented in the lexical analyzer function
bool operator==(const tokens& compare1, const tokens compare2){
    if((compare1.ID == compare2.ID) && (compare1.value == compare2.value))
        return true;
    else
        return false;
}

bool is_a_number(const char& letter){ //Consider '.' as a number for make easier to save float numbers
    if(letter == '1' || letter == '2' || letter == '3' || letter == '4' || letter == '5' ||
       letter == '6' || letter == '7' || letter == '8' || letter == '9' || letter == '0' || letter == '.'){
        return true;
       }
    else{
        return false;
    }
}

bool is_a_separator(const char& letter){
    if(letter == ',' || letter == '{' || letter == '}' || letter == '_'){// '_' case is for the - sign in negative numbers
        return true;
       }
    else{
        return false;
    }
}

bool is_a_parenthesis(const char& letter){
    if(letter == '(' || letter == ')'){//Special case because there are to types of parenthesis
           return true;
       }
    else{
        return false;
    }
}

bool is_an_operator(const char& letter) {//There are not unary operators here
    if(letter == '*' || letter == '/' || letter == '+' ||
       letter == '-' || letter == '%'){
           return true;
       }
    else{
        return false;
    }
}

//Just a function that returns a token when it found an special character
tokens select_special_character(const char& a){
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
void return_error(const int& err){
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

//Currently there are 3 binary function
bool is_binary_function(const tokens& function){
    if(function.value == "pow" || function.value == "fmod" || function.value == "round" || function.value == "atan2")
        return true;
    else
        return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER FUNCTION FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

const char* print_ID( const char& ID ){
    switch (ID)
    {
    case NUMBER: return "NUUMBERR";
    case VARIABLE: return "VARIABLE";
    case FUNCTION: return "FUNCTION";
    case OPERATOR: return "OPERATOR";
    case OPEN_FUNC: return "OPEN_FUNC";
    case CLOSE_FUNC: return "CLOSE_FUNC";
    case OPEN_VAR: return "OPEN_VAR";
    case CLOSE_VAR: return "CLOSE_VAR";
    case OPEN_PAR: return "OPEN_PAR";
    case CLOSE_PAR: return "CLOSE_PAR";
    case SEPARATOR: return "SEPARATOR";
    default: return "UNDEFINED";
    }
}

//This function prints all the tokens of vector token
//Using IDs as words, for debugging
std::ostream& operator<<(std::ostream& out, std::vector<tokens>& vector_token){
    for(int i = 0; i < vector_token.size(); i++)
        out << print_ID(vector_token[i].ID) << "\t" << vector_token[i].value << "\n";
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<PARSER FUNCTION FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

std::ostream& operator<<(std::ostream& output, std::queue<tokens> vector_token){
    while(!vector_token.empty()){
        output << print_ID(vector_token.front().ID) << "\t" << vector_token.front().value << "\n";
        vector_token.pop();
    }
    return output;
}

//Check precedence in functions and operators
int precedence(const tokens token){
    if(token.value == "*" || token.value == "/")
        return 3;
    else if(token.value == "+" || token.value == "-")
        return 2;
    else if(token.value == "pow")//Here all binary functions
        return 1;
    else//Here all unary functions
        return 0;
    
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<EVALUATE FUNCTION FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
//Implemented moodle functions
float bin2dec(std::string number)
{
    int result = 0, pow = 1;
    for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (number[i] - '0') * pow;

    return (float)result;
}*/

//Instantiate variables randomly
float instantiate(int lower, int upper){
    srand(time(NULL));
    return (float)(rand()%(1+upper-lower))+lower;
}

//Convert string to float
float string_to_float(std::string string){
    return ::atof(string.c_str());
}

//Binary operation
float compute( std::string operation, float a, float b ){
    //Decide which operation
    if(operation == "pow")    return pow(a, b);
    else if(operation == "+") return a+b;
    else if(operation == "-") return a-b;
    else if(operation == "*") return a*b;
    else if(operation == "/") return a/b;
    else if(operation == "fmod") return fmod(a,b);
    else if(operation == "round") return round(a/b)*b;//Moodle round
    else if(operation == "atan2") return atan2(a,b);
}

//Unary operation
float compute( std::string operation, float a ){
    //Decide which operation
    //Decide which operation
    if(operation == "abs")    return abs(a);
    else if(operation == "acos") return acos(a);
    else if(operation == "acosh") return acosh(a);
    else if(operation == "asin") return asin(a);
    else if(operation == "asinh") return asinh(a);
    else if(operation == "atan") return atan(a);
    else if(operation == "atanh") return atanh(a);
//    else if(operation == "bindec") return bin2dec(a);//Note tested yet
    else if(operation == "ceil") return ceil(a);
    else if(operation == "cos") return cos(a);
    else if(operation == "cosh") return cosh(a);
//    else if(operation == "decbin") return decbin(a);
//    else if(operation == "decoct") return decoct(a);
//    else if(operation == "deg2rad") return deg2rad(a);
    else if(operation == "exp") return exp(a);
    else if(operation == "expm1") return exp(a)-1;
    else if(operation == "floor") return floor(a);
//    else if(operation == "is_finite") return is_finit(a);//Encuentra si es que un valor es un número finito legal
//    else if(operation == "is_infinite") return is_infinit(a);//Encuentra si es que un valor es infinito
//    else if(operation == "is_nan") return is_nan(a);//Encuentra si es que un valor no es un número
    else if(operation == "log10") return log10(a);
    else if(operation == "log1p") return log(1+a);
    else if(operation == "log") return log(a);
//    else if(operation == "max") return max(a);
//    else if(operation == "min") return min(a);
//    else if(operation == "octdec") return octdec(a);
//    else if(operation == "rad2deg") return rad2deg(a);
    else if(operation == "sin") return sin(a);
    else if(operation == "sinh") return sinh(a);
    else if(operation == "sqrt") return sqrt(a);
    else if(operation == "tan") return tan(a);
    else if(operation == "tanh") return tanh(a);
}

//No operands operation
float compute( std::string operation ){
    //Decide which operation
    if(operation == "rand") return (float)rand();
    else if(operation == "pi") return E_PI;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER PART 1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Lexical analyzer, lexer or tokenizer function
//It scans a string and divides it into tokens
std::vector <tokens> lexer_part_1(std::string string){
    std::vector <tokens> tokenized_string;
    tokens current_token;
    std::string buffer;
    std::string char_to_string;
    std::stack<tokens> parenthesis_stack;

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
                    char_to_string += string[i];
                    current_token = {OPEN_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    parenthesis_stack.push(current_token);
                    char_to_string.clear();
                }
                else{//We found an asocciative parenthesis
                    char_to_string += string[i];
                    current_token = {OPEN_PAR, char_to_string};
                    tokenized_string.push_back(current_token);
                    parenthesis_stack.push(current_token);
                    char_to_string.clear();
                }
            }
            else if(string[i] == ')'){
                if(parenthesis_stack.top().ID == OPEN_PAR){
                    char_to_string += string[i];
                    current_token = {CLOSE_PAR, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                    parenthesis_stack.pop();
                }
                else if(parenthesis_stack.top().ID == OPEN_FUNC){
                    char_to_string += string[i];
                    current_token = {CLOSE_FUNC, char_to_string};
                    tokenized_string.push_back(current_token);
                    char_to_string.clear();
                    parenthesis_stack.pop();
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
//And converts function notation to infix and parenthesis notations
int lexer_part_3(std::vector <tokens>& string){
    int comma_flag = 0;
    std::stack<tokens> func_stack;//Store functions to then replace commas by funcs (convert them to infix notation)
    for(int i = 0; i < string.size(); i++){
        //Treat unary functions
        if(string[i].ID == FUNCTION && is_binary_function(string[i]) == false ){
            if(string[i+1].ID == OPEN_FUNC){
                string[i+1] = string[i];
                string[i] = { OPEN_FUNC, "("};
                i++;
                continue;
            }
            else
                return MISSING_FUNCTION;
        }
        //Treat binary functions
        else if( string[i].ID == FUNCTION && is_binary_function(string[i]) && string[i+1].ID == OPEN_FUNC ) {
            func_stack.push(string[i]);
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
    }
    //If all commas were not fullfiled then there is an error
    if(comma_flag != 0)
        return MISSING_FUNCTION;
    else
        return NOERROR;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LEXER FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Tokenizer
std::vector<tokens> lexer(std::string string){
//Uncomment for debugging
    int error;
    std::vector<tokens> tokenized_string;

    //Delete whitespaces
    string.erase(remove_if(string.begin(), string.end(), isspace), string.end());
    tokenized_string = lexer_part_1(string);
//    std::cout << "String Tokenization\t " << string << "\t tokenized to: \n";
//    print_tokens(tokenized_string);
    error = lexer_part_2(tokenized_string);
//    std::cout << "String Tokenization\t " << string << "\t tokenized to: \n";
//    print_tokens(tokenized_string);
    if( error != NOERROR )
        return_error(error);
    
    error = lexer_part_3(tokenized_string);

    if( error != NOERROR )
        return_error(error);

    //Convert values from std::string to char
    return tokenized_string;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<PARSER FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Converts a tokens vector into postfix or RPN notation
//Using in the Shunting Yard Algorithm
//Returns a tokens vector
std::queue <tokens> parser(std::vector <tokens> string){
    std::stack <tokens> operations;
    std::queue <tokens> queue;

    while(!string.empty()){//Iterate over tokens vector
        //There is a operand, push it to the queue and delete on the string
        if( string[0].ID == VARIABLE || string[0].ID == NUMBER )
            queue.push(string[0]);
        //Opening parenthesis goes to the operations stack
        else if( string[0].ID == OPEN_PAR || string[0].ID == OPEN_FUNC )
            operations.push(string[0]);
        //If there is a closing parenthesis, pop operations to the queue till an openning one.
        else if( string[0].ID == CLOSE_PAR || string[0].ID == CLOSE_FUNC ){
            while ( !(operations.top().ID == OPEN_PAR || operations.top().ID == OPEN_FUNC) ){
                queue.push(operations.top());
                operations.pop();
            }
            operations.pop();//Pop the opening parenthesis
        }
        //This is the interesting part
        else if( string[0].ID == FUNCTION || string[0].ID == OPERATOR ){
            if(operations.top().ID == OPEN_PAR || operations.top().ID == OPEN_FUNC )
                operations.push(string[0]);
            //Same precedence pop from stack to the queue and pop from vector to the stack
            //Lower precedence pop from stack to the queue and pop from vector to the stack
            else if( ( precedence(string[0]) == precedence(operations.top()) ) ||
                     ( precedence(string[0]) < precedence(operations.top()) )     ){
                queue.push(operations.top());
                operations.pop();
                operations.push(string[0]);
            }
            //Higher precedence, just push from vector to the stack
            else if( precedence(string[0]) > precedence(operations.top()) ){
                operations.push(string[0]);
            }
        }
        string.erase(string.begin());
    }
    //If there are still operations on the stach just push them into the queue till emptying the stack
    while(!operations.empty()){
        queue.push(operations.top());
        operations.pop();
    }
    return queue;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<EVALUATE FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Converts a queue of tokens in postfix notation into a result, instantiating variables
//It is an implementation of algorithm to evaluate postfix notation
float evaluate(std::queue<tokens> string, float lower, float upper){
    std::stack<float> result;
    float a, b;
    while(!string.empty()){
        //If it is a numebr convert it to float
        if( string.front().ID == NUMBER)
            result.push(string_to_float(string.front().value));
        //If it is a variable instantiate it randomly
        else if (string.front().ID == VARIABLE)
            result.push(instantiate(lower, upper));
        //If it is a function or operator which reciebes 2 operands compute it and store into the stack
        else if( string.front().ID == OPERATOR || is_binary_function(string.front()) ){
            b = result.top();
            result.pop();
            a = result.top();
            result.pop();
            result.push(compute(string.front().value, a, b));
        }
        //It is an unary function
        else if( (string.front().ID == FUNCTION && !is_binary_function(string.front())) || string.front().value == "_"){
            a = result.top();
            result.pop();
            result.push( compute(string.front().value, a) );
        }
        //It is a no operands function
        else
            result.push( compute(string.front().value) );
        string.pop();
        std::cout << result.top() << '\n';
    }
    return result.top();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MAIN FUNCTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*Usage example
int main(){
//    std::string string = "pow(pow(2,2), 0)";
//    std::string string = "pow(pow(4,cos({var})),cos(cos({x})))";
    std::string string = "cos(2*sqrt(3)+14)";
    std::vector<tokens> tokenized_string;
    std::queue<tokens> RPN;//Reverse Polish Notation
    float result;

    tokenized_string = lexer(string);
    //Print vector
    std::cout << "String Tokenization\t " << string << "\t tokenized to: \n"
              << tokenized_string;
    RPN = parser(tokenized_string);
    std::cout << "String Parsing\t " << string << "\t to: \n"
              << RPN;
    result = evaluate(RPN, 40, 90);
    std::cout << "Result is: " << result << std::endl;
}
*/