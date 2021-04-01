#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Lexer {
  string text;
  char character;
  int cursor;
  bool end;

  Lexer(string text) {
    this->text = text;
    this->character = 0;
    this->cursor = -1;
    this->end = false;
  }

  void advance() {
    cursor += 1;
    int length = text.length();

    if (cursor < length) {
      character = text[cursor];
    } else {
      end = true;
      character = 0;
    }
  }

  list<string> tokenize() {
    list <string> tokens;
    advance();

    while (!end) {
      if (isWhiteSpace(character)) {
        advance();
      }
      if (isDigit(character)) {
        tokens.push_back(matchNumber());
      }
    }

    return tokens;
  }

  string matchNumber() {
    string num = "";
    bool dot = false;

    while (isDigit(character) || character == '.') {
      if (dot && character == '.') break;

      if (character == '.') {
        dot = true;
      }

      num += character;
      advance();
    }

    if (character == '.') {
      throw "Invalid Syntax";
    }

    string type = dot ? "FLOAT" : "INT";
    return type + "_" + num;
  }

  bool isWhiteSpace(char c) {
    return c == ' ' || c == '\t';
  }

  bool isDigit(char c) {
    return c >= '0' && c <= '9';
  }

  bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
  }

  bool isLetter(char c) {
    bool lowercase = c >= 'a' && c <= 'z';
    bool uppercase = c >= 'A' && c <= 'Z';
    return lowercase || uppercase;
  }
};

int main()
{
  auto lexer = new Lexer("31 4.5 123  ");
  auto tokens = lexer->tokenize();

  while (!tokens.empty()) {
    cout << tokens.front() << endl;
    tokens.pop_front();
  }

  return 0;
}
