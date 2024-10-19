//#include "Tokenizer.h"
//#include <cctype>     // For character checks (isdigit, isalpha, etc.)
//#include <iostream>   // For debugging output (optional)
//#include <unordered_set> // For faster keyword lookup
//
//// Token constructor
//Token::Token(TokenType t, const std::string& val) : type(t), value(val) {}
//
//// Set of C++ keywords for quick lookup
//const std::unordered_set<std::string> keywords = {
//    "int", "float", "double", "bool", "return", "void",
//    "namespace", "enum", "if", "else", "for", "while", "do", "switch", "case", "break",
//    "continue", "default", "static", "const", "class", "struct", "public", "private",
//    "protected", "virtual", "override", "new", "delete", "try", "catch", "throw", "using",
//    "asm", "auto", "char", "const", "extern", "friend", "inline", "long", "register", "signed",
//    "short", "this", "typedef", "union", "unsigned", "volatile"
//};
//
//// Check if a string is a keyword
//bool isKeyword(const std::string& str) {
//    return keywords.find(str) != keywords.end();
//}
//
//// Check if a character is a valid operator
//bool isOperator(char c) {
//    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' ||
//        c == '<' || c == '>' || c == '!' || c == '&' || c == '|' ||
//        c == '^' || c == '%' || c == '~');
//}
//
//// Function to convert TokenType to string for output
//std::string tokenTypeToString(TokenType type) {
//    switch (type) {
//    case TOK_HEADER: return "TOK_HEADER";
//    case TOK_COMMENT: return "TOK_COMMENT";
//    case TOK_INT: return "TOK_INT";
//    case TOK_FLOAT: return "TOK_FLOAT";
//    case TOK_DOUBLE: return "TOK_DOUBLE";
//    case TOK_BOOL: return "TOK_BOOL";
//    case TOK_RETURN: return "TOK_RETURN";
//    case TOK_IDENTIFIER: return "TOK_IDENTIFIER";
//    case TOK_NUMBER: return "TOK_NUMBER";
//    case TOK_OPERATOR: return "TOK_OPERATOR";
//    case TOK_PUNCTUATION: return "TOK_PUNCTUATION";
//    case TOK_STRING: return "TOK_STRING";
//    case TOK_CHAR: return "TOK_CHAR";
//    case TOK_VOID: return "TOK_VOID";
//    case TOK_NAMESPACE: return "TOK_NAMESPACE";
//    case TOK_ENUM: return "TOK_ENUM";
//    case TOK_TEMPLATE: return "TOK_TEMPLATE"; // New token type
//    case TOK_KEYWORD: return "TOK_KEYWORD";
//    case TOK_UNKNOWN: return "TOK_UNKNOWN";
//    default: return "UNKNOWN";
//    }
//}
//
//// Tokenize the input string
//std::vector<Token> tokenize(const std::string& input) {
//    std::vector<Token> tokens;
//    size_t length = input.length();
//    size_t i = 0;
//    // Inside your tokenize function
//
//   // Inside your tokenize function
//
//    while (i < length) {
//        char current = input[i];
//
//        // Skip whitespace
//        if (isspace(current)) {
//            i++;
//            continue;
//        }
//
//        // Handle preprocessor directives (e.g., #include)
//        if (current == '#') {
//            std::string directive;
//            while (i < length && input[i] != '\n') {
//                directive += input[i++];
//            }
//            tokens.push_back(Token(TOK_HEADER, directive)); // Capture entire directive
//            continue;
//        }
//
//        // Handle single-line comments
//        if (current == '/' && i + 1 < length && input[i + 1] == '/') {
//            std::string comment;
//            while (i < length && input[i] != '\n') {
//                comment += input[i++];
//            }
//            tokens.push_back(Token(TOK_COMMENT, comment)); // Capture comment
//            continue;
//        }
//
//        // Handle multi-line comments
//        if (current == '/' && i + 1 < length && input[i + 1] == '*') {
//            std::string comment = "/*"; // Include the opening '/*'
//            i += 2; // Skip '/*'
//            while (i + 1 < length && !(input[i] == '*' && input[i + 1] == '/')) {
//                comment += input[i++];
//            }
//            if (i + 1 < length) {
//                comment += "*/"; // Include the closing '*/'
//                i += 2; // Skip '*/'
//            }
//            else {
//                tokens.push_back(Token(TOK_UNKNOWN, comment)); // Handle unclosed comment
//                continue;
//            }
//            tokens.push_back(Token(TOK_COMMENT, comment)); // Capture entire multi-line comment
//            continue;
//        }
//
//        // Handle keywords and identifiers
//        if (isalpha(current) || current == '_') {
//            std::string word;
//            while (i < length && (isalnum(input[i]) || input[i] == '_')) {
//                word += input[i++];
//            }
//
//            // Classify the word
//            if (isKeyword(word)) {
//                /*tokens.push_back(Token(static_cast<TokenType>(wordToTokenType(word)), word));*/
//                tokens.push_back(Token(TOK_KEYWORD, word));
//            }
//            else {
//                tokens.push_back(Token(TOK_IDENTIFIER, word));
//            }
//            continue;
//        }
//
//        // Handle numbers (integers, octals, hexadecimals, and floats)
//        if (isdigit(current) || (current == '0' && i + 1 < length && (input[i + 1] == 'x' || input[i + 1] == 'X'))) {
//            std::string number;
//            bool isHex = false, isFloat = false;
//
//            // Check for hexadecimal numbers
//            if (current == '0' && i + 1 < length && (input[i + 1] == 'x' || input[i + 1] == 'X')) {
//                number += input[i++];
//                number += input[i++]; // Capture '0x' or '0X'
//                isHex = true;
//            }
//
//            while (i < length && (isalnum(input[i]) || input[i] == '.')) {
//                if (input[i] == '.') {
//                    isFloat = true;
//                }
//                number += input[i++];
//            }
//
//            // Check for scientific notation
//            if (isFloat && i < length && (input[i] == 'e' || input[i] == 'E')) {
//                number += input[i++];
//                if (i < length && (input[i] == '-' || input[i] == '+')) {
//                    number += input[i++];
//                }
//                while (i < length && isdigit(input[i])) {
//                    number += input[i++];
//                }
//            }
//
//            tokens.push_back(Token(TOK_NUMBER, number)); // Handle number
//            continue;
//        }
//
//        // Handle operators
//        if (isOperator(current)) {
//            std::string op(1, current);
//            tokens.push_back(Token(TOK_OPERATOR, op));
//            i++;
//            continue;
//        }
//
//        // Handle member access (e.g., . or ->)
//        if (current == '.' || current == '-') {
//            if (current == '-' && i + 1 < length && input[i + 1] == '>') {
//                tokens.push_back(Token(TOK_PUNCTUATION, "->")); // Handle -> operator
//                i += 2;
//            }
//            else {
//                tokens.push_back(Token(TOK_PUNCTUATION, ".")); // Handle . operator
//                i++;
//            }
//            continue;
//        }
//
//        // Handle for loop syntax
//        if (current == 'f' && i + 2 < length && input.substr(i, 3) == "for") {
//            tokens.push_back(Token(TOK_KEYWORD, "for")); // Add 'for' as a keyword
//            i += 3; // Move past 'for'
//
//            // Expect '(' after 'for'
//            if (i < length && input[i] == '(') {
//                i++; // Skip '('
//
//                // Handle variable declaration (const int& num)
//                std::string type;
//                bool hasConst = false;
//
//                // Check for 'const'
//                if (input.substr(i, 5) == "const") {
//                    hasConst = true;
//                    type += "const ";
//                    i += 5; // Move past 'const'
//                }
//
//                // Capture the type (int)
//                while (i < length && (isalnum(input[i]) || input[i] == ' ' || input[i] == '&')) {
//                    if (input[i] == ' ') {
//                        i++;
//                        continue;
//                    }
//                    type += input[i++];
//                }
//
//                if (!type.empty()) {
//                    tokens.push_back(Token(TOK_UNKNOWN, type)); // Capture type (could be TOK_TYPE if defined)
//                }
//
//                // Capture variable name (num)
//                std::string varName;
//                while (i < length && (isalnum(input[i]) || input[i] == '_')) {
//                    varName += input[i++];
//                }
//                tokens.push_back(Token(TOK_IDENTIFIER, varName)); // Capture variable name (num)
//
//                // Handle ':' symbol
//                if (i < length && input[i] == ':') {
//                    tokens.push_back(Token(TOK_PUNCTUATION, ":"));
//                    i++; // Skip ':'
//                }
//
//                // Capture the container (numbers)
//                std::string container;
//                while (i < length && input[i] != ')') {
//                    if (isspace(input[i])) {
//                        i++;
//                        continue;
//                    }
//                    container += input[i++];
//                }
//
//                if (!container.empty()) {
//                    tokens.push_back(Token(TOK_IDENTIFIER, container)); // Capture container name (numbers)
//                }
//
//                // Expect ')' to close the for statement
//                if (i < length && input[i] == ')') {
//                    tokens.push_back(Token(TOK_PUNCTUATION, ")"));
//                    i++; // Skip ')'
//                }
//                continue; // Finish processing this token
//            }
//        }
//
        //// Handle Scope resolution 
        //if (current == ':') {
        //    if (i + 1 < length && input[i + 1] == ':') {
        //        std::string namespaceId = tokens.back().value + "::"; // Append the namespace
        //        tokens.pop_back(); // Remove the previous identifier
        //        tokens.push_back(Token(TOK_IDENTIFIER, namespaceId));
        //        i += 2; // Skip the next ':'
        //        continue;
        //    }
        //}
//
//        // Handle Template Declaration
//        if (current == '<') {
//            std::string templateType;
//            while (i < length && input[i] != '>') {
//                templateType += input[i++];
//            }
//            if (i < length) {
//                templateType += input[i++]; // Include '>'
//            }
//            tokens.push_back(Token(TOK_TEMPLATE, templateType)); // Define a new token type
//            continue;
//        }
////
//        // Handle punctuation
//        if (current == ';' || current == '{' || current == '}' || current == '(' || current == ')' || current == '[' || current == ']') {
//            std::string punctuation(1, current);
//            tokens.push_back(Token(TOK_PUNCTUATION, punctuation));
//            i++;
//            continue;
//        }
//
//        // Handle string literals
//        if (current == '\"') {
//            std::string strLit;
//            strLit += current; // Start with opening quote
//            i++; // Skip the opening quote
//            while (i < length && input[i] != '\"') {
//                strLit += input[i++];
//            }
//            if (i < length) {
//                strLit += input[i++]; // Add closing quote
//            }
//            tokens.push_back(Token(TOK_STRING, strLit));
//            continue;
//        }
//
//        // Handle character literals
//        if (current == '\'') {
//            std::string charLit;
//            charLit += current; // Start with opening quote
//            i++; // Skip the opening quote
//            if (i < length) {
//                charLit += input[i++];
//            }
//            if (i < length && input[i] == '\'') {
//                charLit += input[i++]; // Add closing quote
//            }
//            tokens.push_back(Token(TOK_CHAR, charLit));
//            continue;
//        }
//
//        // If none of the above, consider it an unknown token
//        tokens.push_back(Token(TOK_UNKNOWN, std::string(1, current)));
//        i++;
//    }
//
//    return tokens;
//
//}
//
//// Helper function to map keyword strings to TokenType
//TokenType wordToTokenType(const std::string& word) {
//    if (word == "int") return TOK_INT;
//    if (word == "float") return TOK_FLOAT;
//    if (word == "double") return TOK_DOUBLE;
//    if (word == "bool") return TOK_BOOL;
//    if (word == "return") return TOK_RETURN;
//    if (word == "void") return TOK_VOID;
//    if (word == "namespace") return TOK_NAMESPACE;
//    if (word == "enum") return TOK_ENUM;
//    // Add more keywords as needed
//    return TOK_UNKNOWN; // Default case
//}
//
//
