#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

// Enum to represent different types of tokens
enum TokenType {
    TOK_HEADER = 0,       // For preprocessor directives
    TOK_COMMENT = 1,      // For comments
    TOK_INT = 2,          // For int keyword
    TOK_FLOAT = 3,        // For float keyword
    TOK_DOUBLE = 4,       // For double keyword
    TOK_BOOL = 5,         // For bool keyword
    TOK_RETURN = 6,       // For return keyword
    TOK_IDENTIFIER = 7,   // For variable names, function names
    TOK_NUMBER = 8,       // For numbers
    TOK_OPERATOR = 9,     // For operators like +, -, *, /, etc.
    TOK_PUNCTUATION = 10, // For punctuation like ;, {, }, (, )
    TOK_STRING = 11,      // For string literals
    TOK_CHAR = 12,        // For character literals
    TOK_VOID = 13,        // For void keyword
    TOK_NAMESPACE = 14,   // For namespace keyword
    TOK_ENUM = 15,        // For enum keyword
    TOK_TEMPLATE = 16,    // For template like vector, map
    TOK_KEYWORD = 17,     // Generic keyword token
    TOK_UNKNOWN = 18,     // For unknown tokens

    // Additional C++ keywords
    TOK_ASM = 19,
    TOK_AUTO = 20,
    TOK_BREAK = 21,
    TOK_CASE = 22,
    TOK_CATCH = 23,
    TOK_CLASS = 25,
    TOK_CONST = 26,
    TOK_CONTINUE = 27,
    TOK_DEFAULT = 28,
    TOK_DELETE = 29,
    TOK_DO = 30,
    TOK_ELSE = 32,
    TOK_EXTERN = 34,
    TOK_FOR = 35,
    TOK_FRIEND = 36,
    TOK_GOTO = 37,
    TOK_IF = 38,
    TOK_INLINE = 39,
    TOK_LONG = 40,
    TOK_NEW = 41,
    TOK_PRIVATE = 43,
    TOK_PROTECTED = 44,
    TOK_PUBLIC = 45,
    TOK_REGISTER = 46,
    TOK_SHORT = 47,
    TOK_SIGNED = 48,
    TOK_SIZEOF = 49,
    TOK_STATIC = 50,
    TOK_STRUCT = 51,
    TOK_SWITCH = 52,
    TOK_THIS = 53,
    TOK_THROW = 54,
    TOK_TRY = 55,
    TOK_TYPEDEF = 56,
    TOK_UNION = 57,
    TOK_UNSIGNED = 58,
    TOK_USING = 59,
    TOK_VIRTUAL = 60,
    TOK_VOLATILE = 61,
    TOK_WHILE = 62,
    TOK_OVERRIDE=63,
    // New token types
    TOK_SCOPE = 64,   // For scope resolution operator (::)
};

// Structure to represent a token
struct Token {
    TokenType type;      // Type of token
    std::string value;   // The actual string value of the token

    Token(TokenType t, const std::string& val); // Constructor declaration
};

// Function to tokenize the input string
std::vector<Token> tokenize(const std::string& input); // Function declaration

// Function to convert TokenType to string representation
std::string tokenTypeToString(TokenType type); // Function declaration

// Function to check if a string is a keyword
bool isKeyword(const std::string& str); // Function declaration

// Function to check if a character is a valid operator
bool isOperator(char c); // Function declaration

// Function to map a word to its corresponding TokenType
TokenType wordToTokenType(const std::string& word); // Function declaration

// Function to check if a string is a multi-character operator (e.g., "::", "++", "--")
bool isMultiCharOperator(const std::string& str); // Function declaration

#endif // TOKENIZER_H
