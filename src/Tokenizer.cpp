#include "Tokenizer.h"
#include <cctype>

LinkedList Tokenizer::tokenize(const std::string &text) {
  LinkedList tokens;
  std::string word = "";

  for (char ch : text) {
    bool isAlpha = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    bool isDigit = (ch >= '0' && ch <= '9');

    if (isAlpha || isDigit) {
      word += tolower(ch);
    } else {
      if (!word.empty()) {
        tokens.addNode(new std::string(word));
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tokens.addNode(new std::string(word));
  }

  return tokens;
}
