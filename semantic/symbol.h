#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <unordered_map>
#include <vector>

#include "../tree/type.h"

class SymbolTable {
   private:
    std::vector<std::unordered_map<std::string, Type>> symbolTable;

   public:
    SymbolTable() {}
    ~SymbolTable() {}

    Type findSymbol(std::string name);

    void push();

    void pop();

    std::unordered_map<std::string, Type> top();
};

#endif