#include <iostream>
#include <bits/stdc++.h> 
#include <queue>
#include <stack>

enum{ NUMBER, VARIABLE, FUNCTION, OPERATOR, OPEN_FUNC, CLOSE_FUNC, OPEN_VAR, CLOSE_VAR, OPEN_PAR, CLOSE_PAR};

struct tokens{
    int ID;
    std::string value;
};

bool is_a_number(char letter){
    if(letter == '1' || letter == '2' || letter == '3' || letter == '4' || letter == '5' ||
       letter == '6' || letter == '7' || letter == '8' || letter == '9' || letter == '0'){
           return true;
       }
    else{
        return false;
    }
}

bool is_a_separator(char letter){
    if(letter == ',' || letter == '.' || letter == '(' || letter == ')' ||
       letter == '{' || letter == '}' || letter == '_'){// '_' case is for the - sign in negative numbers
           return true;
       }
    else{
        return false;
    }
}

bool is_an_operator(char letter) {
    if(letter == '*' || letter == '/' || letter == '+' ||
       letter == '-' || letter == '%'){
           return true;
       }
    else{
        return false;
    }
}

std::string evaluate_negative_sign(){}

//Lexical analyzer, lexer or tokenizer function
//It scans a string and divides it into tokens
std::vector <tokens> lexer(std::string string){
    std::vector <tokens> tokenized_string;
    tokens current_token;
    std::string buffer;

    for(int i = 0; i < string.size(); i++){
        if( is_an_operator(string[i]) ){
            buffer += string[i];
            current_token = {OPERATOR, buffer};
            buffer.clear();
            continue;
        }
        else if( is_a_separator(string[i]) ){
            if( string[i] == '.' && is_an_operator(string[i-1]) ){//is a float number
                buffer += string[i];
                continue;
            }
            else { //It is a separator
                buffer += string[i];
                current_token = {OPEN_FUNC, buffer};
                buffer.clear();
                continue;
            }
        }
        else if( is_a_number(string[i]) ){
            buffer += string[i];
            continue;
        }
        if( !is_a_number(string[i]) && !is_a_separator(string[i]) && !is_an_operator(string[i]) ){//There is a function or variable
            buffer += string[i];
        }
    }
}

std::stack <tokens> parser(std::vector <tokens> string){

}

int main(){
    std::string string = "pow({x},2)+(sin({y})*4/2.87)";
    std::vector<tokens> tokenized_string = lexer(string);
    std::cout << "String\t " << string << "tokenized to: \n";
    for(int i = 0; i < tokenized_string.size(); i++)
        std::cout << tokenized_string[i].ID << "\t" << tokenized_string[i].value << "\n";
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
int main(){
    std::string hola = "0.74";
    double st = std::stod(hola);
    std::cout << st << std::endl;
}
//Proving