#include "symbol.h"

Declaration* SymbolTable::findSymbol(std::string name) {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); it++) {
        if (it->count(name) != 0) {
            return (*it)[name];
        }
    }
    return nullptr;
}

void SymbolTable::push() {
    std::unordered_map<std::string, Declaration*> curMap;
    symbolTable.push_back(curMap);
}

void SymbolTable::pop() {
    symbolTable.pop_back();
}

std::unordered_map<std::string, Declaration*> SymbolTable::top() {
    return symbolTable.back();
}