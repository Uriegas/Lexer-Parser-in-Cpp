# Lexer Parser in C++
This is my implementation of a lexer and parser function in C++, the lexer is a tokenizer and the parser implements the Shunting Yard Algorithm to retrive the formula in postfix notation.

### NOTE
This is part of the [Moodle_C](https://github.com/Uriegas/Moodle_C-) repo.

# TODO
* Implement the evalute() function
* There is a problem with assigning function parenthesis in lexer_part_1 function
* Implement the following functions:
```c++
    std::vector<tokens> lexer_part_3(std::vector <tokens> string){
        for(int i = 0; i < string.size(); i++){
            if( string[i].ID == OPEN_FUNC || string[i].ID == CLOSE_FUNC){
                string.erase(string.begin()+i);
                i-2;
            }
        }
        return string;
    }
    std::string evaluate_negative_sign(){}
```
**This lexer does not support negative sign yet.**

## BUILD
Run the [testing.sh](testing.sh) for build the project, implementing CMake.