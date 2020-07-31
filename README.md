# Lexer Parser in C++
This is my implementation of a lexer and parser function in C++, the lexer is a tokenizer and the parser implements the Shunting Yard Algorithm to retrive the formula in postfix notation.

**DO NOT SOPORT NEGATIVE NUMBERS YET**

### NOTE
This is part of the [Moodle_C](https://github.com/Uriegas/Moodle_C-) repo.

# TODO
* Check correctness of the evalute() function
```c++
    float evaluate(std::queue<tokens> string, float lower, float upper){
```
* Implement negative numbers
```c++
    std::string evaluate_negative_sign(){}
```

## BUILD
Run the [testing.sh](testing.sh) for build the project, implementing CMake.