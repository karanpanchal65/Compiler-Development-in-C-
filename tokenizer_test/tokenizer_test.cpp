#include <iostream>
#include <vector>
#include "Tokenizer.h"

int main() {
    std::string input = R"(int x = 5;
x++;
--x;
int y = x ** 2;
)";

    std::vector<Token> tokens = tokenize(input); // Assuming you have a tokenize function

    // Print the tokens
    for (const Token& token : tokens) {
        if (tokenTypeToString(token.type) == "TOK_KEYWORD");
        std::cout << tokenTypeToString(token.type) <<" " << token.value << std::endl;
    }

    return 0;
}
