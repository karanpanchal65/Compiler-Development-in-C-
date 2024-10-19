#include "Tokenizer.h"
#include <cctype>  // For character checks (isdigit, isalpha, etc.)
#include <iostream> // For debugging output (optional)
#include <unordered_set> // For faster keyword lookup

// Token constructor
Token::Token(TokenType t, const std::string& val) : type(t), value(val) {}

// Set of C++ keywords for quick lookup
const std::unordered_set<std::string> keywords = {
    "int", "float", "double", "bool", "return", "void", "namespace", "enum",
    "if", "else", "for", "while", "do", "switch", "case", "break", "continue",
    "default", "static", "const", "class", "struct", "public", "private", "protected",
    "virtual", "override", "new", "delete", "try", "catch", "throw", "using", "asm",
    "auto", "char", "extern", "friend", "inline", "long", "register", "signed", "short",
    "this", "typedef", "union", "unsigned", "volatile", "template"
};

// Check if a string is a keyword
bool isKeyword(const std::string& str) {
    return keywords.find(str) != keywords.end();
}

// Check if a character is a valid operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' ||
        c == '<' || c == '>' || c == '!' || c == '&' || c == '|' ||
        c == '^' || c == '%' || c == '~');
}

// Check for multi-character operators (e.g., <<, >>, <=, >=, ==, !=, ++, --, **)
bool isMultiCharOperator(const std::string& input, size_t i) {
    if (i + 1 >= input.length()) return false;
    char next = input[i + 1];
    char current = input[i];

    return (current == '<' && next == '<') || (current == '>' && next == '>') ||
        (current == '<' && next == '=') || (current == '>' && next == '=') ||
        (current == '=' && next == '=') || (current == '!' && next == '=') ||
        (current == '+' && next == '+') || (current == '-' && next == '-') ||
        (current == '*' && next == '*');
}

// Convert TokenType to string for debugging
std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case TOK_HEADER: return "TOK_HEADER";
    case TOK_COMMENT: return "TOK_COMMENT";
    case TOK_INT: return "TOK_INT";
    case TOK_FLOAT: return "TOK_FLOAT";
    case TOK_DOUBLE: return "TOK_DOUBLE";
    case TOK_BOOL: return "TOK_BOOL";
    case TOK_RETURN: return "TOK_RETURN";
    case TOK_IDENTIFIER: return "TOK_IDENTIFIER";
    case TOK_NUMBER: return "TOK_NUMBER";
    case TOK_OPERATOR: return "TOK_OPERATOR";
    case TOK_PUNCTUATION: return "TOK_PUNCTUATION";
    case TOK_STRING: return "TOK_STRING";
    case TOK_CHAR: return "TOK_CHAR";
    case TOK_VOID: return "TOK_VOID";
    case TOK_NAMESPACE: return "TOK_NAMESPACE";
    case TOK_ENUM: return "TOK_ENUM";
    case TOK_TEMPLATE: return "TOK_TEMPLATE";
    case TOK_KEYWORD: return "TOK_KEYWORD";
    case TOK_UNKNOWN: return "TOK_UNKNOWN";

        // Add cases for all keyword token types
    case TOK_IF: return "TOK_IF";
    case TOK_ELSE: return "TOK_ELSE";
    case TOK_FOR: return "TOK_FOR";
    case TOK_WHILE: return "TOK_WHILE";
    case TOK_DO: return "TOK_DO";
    case TOK_SWITCH: return "TOK_SWITCH";
    case TOK_CASE: return "TOK_CASE";
    case TOK_BREAK: return "TOK_BREAK";
    case TOK_CONTINUE: return "TOK_CONTINUE";
    case TOK_DEFAULT: return "TOK_DEFAULT";
    case TOK_STATIC: return "TOK_STATIC";
    case TOK_CONST: return "TOK_CONST";
    case TOK_CLASS: return "TOK_CLASS";
    case TOK_STRUCT: return "TOK_STRUCT";
    case TOK_PUBLIC: return "TOK_PUBLIC";
    case TOK_PRIVATE: return "TOK_PRIVATE";
    case TOK_PROTECTED: return "TOK_PROTECTED";
    case TOK_VIRTUAL: return "TOK_VIRTUAL";
    case TOK_OVERRIDE: return "TOK_OVERRIDE";
    case TOK_NEW: return "TOK_NEW";
    case TOK_DELETE: return "TOK_DELETE";
    case TOK_TRY: return "TOK_TRY";
    case TOK_CATCH: return "TOK_CATCH";
    case TOK_THROW: return "TOK_THROW";
    case TOK_USING: return "TOK_USING";
    case TOK_ASM: return "TOK_ASM";
    case TOK_AUTO: return "TOK_AUTO";
    case TOK_EXTERN: return "TOK_EXTERN";
    case TOK_FRIEND: return "TOK_FRIEND";
    case TOK_INLINE: return "TOK_INLINE";
    case TOK_LONG: return "TOK_LONG";
    case TOK_REGISTER: return "TOK_REGISTER";
    case TOK_SIGNED: return "TOK_SIGNED";
    case TOK_SHORT: return "TOK_SHORT";
    case TOK_THIS: return "TOK_THIS";
    case TOK_TYPEDEF: return "TOK_TYPEDEF";
    case TOK_UNION: return "TOK_UNION";
    case TOK_UNSIGNED: return "TOK_UNSIGNED";
    case TOK_VOLATILE: return "TOK_VOLATILE";
    case TOK_SCOPE: return "TOK_SCOPE";
    default: return "UNKNOWN";
    }
}


// Tokenize input string
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t length = input.length();
    size_t i = 0;

    while (i < length) {
        char current = input[i];

        // Skip whitespace
        if (isspace(current)) {
            i++;
            continue;
        }

        // Handle preprocessor directives
        if (current == '#') {
            std::string directive;
            while (i < length && input[i] != '\n') {
                directive += input[i++];
            }
            tokens.push_back(Token(TOK_HEADER, directive));
            continue;
        }

        // Handle multi-character operators (e.g., ==, <=, ++, **)
        if (isMultiCharOperator(input, i)) {
            tokens.push_back(Token(TOK_OPERATOR, input.substr(i, 2)));  // Capture two-character operator
            i += 2;
            continue;
        }

        // Handle single-line comments
        if (current == '/' && i + 1 < length && input[i + 1] == '/') {
            std::string comment;
            while (i < length && input[i] != '\n') {
                comment += input[i++];
            }
            tokens.push_back(Token(TOK_COMMENT, comment));
            continue;
        }

        // Handle Scope Resolutiona
        if (current == ':' && i + 1 < length && input[i + 1] == ':') {
            tokens.push_back(Token(TOK_SCOPE, "::"));
            i += 2;
            continue;
        }

        // Handle multi-line comments
        if (current == '/' && i + 1 < length && input[i + 1] == '*') {
            std::string comment = "/*";
            i += 2;
            while (i + 1 < length && !(input[i] == '*' && input[i + 1] == '/')) {
                comment += input[i++];
            }
            if (i + 1 < length) {
                comment += "*/";
                i += 2;
            }
            tokens.push_back(Token(TOK_COMMENT, comment));
            continue;
        }

        // Handle keywords, identifiers, and template keyword
        if (isalpha(current) || current == '_') {
            std::string word;
            while (i < length && (isalnum(input[i]) || input[i] == '_')) {
                word += input[i++];
            }

            if (isKeyword(word)) {
                tokens.push_back(Token(wordToTokenType(word), word));
            }
            else {
                tokens.push_back(Token(TOK_IDENTIFIER, word));
            }
            continue;
        }

        // Handle numbers (integers and floats)
        if (isdigit(current)) {
            std::string number;
            while (i < length && (isdigit(input[i]) || input[i] == '.')) {
                number += input[i++];
            }
            tokens.push_back(Token(TOK_NUMBER, number));
            continue;
        }

        // Handle multi-character operators (e.g., ==, <=)
        if (isMultiCharOperator(input, i)) {
            tokens.push_back(Token(TOK_OPERATOR, input.substr(i, 2)));
            i += 2;
            continue;
        }

        // Handle single-character operators
        if (isOperator(current)) {
            tokens.push_back(Token(TOK_OPERATOR, std::string(1, current)));
            i++;
            continue;
        }

        // Handle punctuation (e.g., ';', '{', '}', '(', ')')
        if (ispunct(current) && current != '"' && current != '\'') {
            tokens.push_back(Token(TOK_PUNCTUATION, std::string(1, current)));
            i++;
            continue;
        }

        // Handle string literals
        if (current == '\"') {
            std::string strLit;
            strLit += current;
            i++;
            while (i < length && input[i] != '\"') {
                if (input[i] == '\\' && i + 1 < length) {
                    strLit += input[i++];  // Handle escape sequences in strings
                }
                strLit += input[i++];
            }
            if (i < length) {
                strLit += input[i++]; // Add closing quote
            }
            tokens.push_back(Token(TOK_STRING, strLit));
            continue;
        }

        // Handle character literals (e.g., 'a')
        if (current == '\'') {
            std::string charLit;
            charLit += current;
            i++;
            while (i < length && input[i] != '\'') {
                if (input[i] == '\\' && i + 1 < length) {
                    charLit += input[i++];  // Handle escape sequences in char literals
                }
                charLit += input[i++];
            }
            if (i < length) {
                charLit += input[i++]; // Add closing quote
            }
            tokens.push_back(Token(TOK_CHAR, charLit));
            continue;
        }

        // Handle member access (e.g., ., ->)
        if (current == '.' || current == '-') {
            if (current == '-' && i + 1 < length && input[i + 1] == '>') {
                tokens.push_back(Token(TOK_PUNCTUATION, "->"));
                i += 2;
            }
            else {
                tokens.push_back(Token(TOK_PUNCTUATION, "."));
                i++;
            }
            continue;
        }

        

        // Handle unknown characters
        tokens.push_back(Token(TOK_UNKNOWN, std::string(1, current)));
        i++;
    }

    return tokens;
}

// Map keyword strings to TokenType
TokenType wordToTokenType(const std::string& word) {
    if (word == "int") return TOK_INT;
    if (word == "float") return TOK_FLOAT;
    if (word == "double") return TOK_DOUBLE;
    if (word == "bool") return TOK_BOOL;
    if (word == "return") return TOK_RETURN;
    if (word == "void") return TOK_VOID;
    if (word == "namespace") return TOK_NAMESPACE;
    if (word == "enum") return TOK_ENUM;
    if (word == "if") return TOK_IF;
    if (word == "else") return TOK_ELSE;
    if (word == "for") return TOK_FOR;
    if (word == "while") return TOK_WHILE;
    if (word == "do") return TOK_DO;
    if (word == "switch") return TOK_SWITCH;
    if (word == "case") return TOK_CASE;
    if (word == "break") return TOK_BREAK;
    if (word == "continue") return TOK_CONTINUE;
    if (word == "default") return TOK_DEFAULT;
    if (word == "static") return TOK_STATIC;
    if (word == "const") return TOK_CONST;
    if (word == "class") return TOK_CLASS;
    if (word == "struct") return TOK_STRUCT;
    if (word == "public") return TOK_PUBLIC;
    if (word == "private") return TOK_PRIVATE;
    if (word == "protected") return TOK_PROTECTED;
    if (word == "virtual") return TOK_VIRTUAL;
    if (word == "override") return TOK_OVERRIDE;
    if (word == "new") return TOK_NEW;
    if (word == "delete") return TOK_DELETE;
    if (word == "try") return TOK_TRY;
    if (word == "catch") return TOK_CATCH;
    if (word == "throw") return TOK_THROW;
    if (word == "using") return TOK_USING;
    if (word == "asm") return TOK_ASM;
    if (word == "auto") return TOK_AUTO;
    if (word == "char") return TOK_CHAR;
    if (word == "extern") return TOK_EXTERN;
    if (word == "friend") return TOK_FRIEND;
    if (word == "inline") return TOK_INLINE;
    if (word == "long") return TOK_LONG;
    if (word == "register") return TOK_REGISTER;
    if (word == "signed") return TOK_SIGNED;
    if (word == "short") return TOK_SHORT;
    if (word == "this") return TOK_THIS;
    if (word == "typedef") return TOK_TYPEDEF;
    if (word == "union") return TOK_UNION;
    if (word == "unsigned") return TOK_UNSIGNED;
    if (word == "volatile") return TOK_VOLATILE;

    // If not a keyword, return generic keyword token
    return TOK_KEYWORD;
}


