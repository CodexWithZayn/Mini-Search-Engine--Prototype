#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include "DataStructures/LinkedList.h"

class Tokenizer {
public:
    static LinkedList tokenize(const std::string& text);
};

#endif
