#include "symbol.h"

#include "sem_util.h"

Declaration* SymbolTable::findSymbol(std::string name) {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); it++) {
        if (it->count(name) != 0) {
            return (*it)[name];
        }
    }
    return nullptr;
}

Type SymbolTable::getSymbolType(std::string name) {
    Declaration* decl = this->findSymbol(name);
    if (decl == nullptr) {
        return ERROR;
    } else {
        if (instanceof <VariableDeclaration>(decl)) {
            VariableDeclaration* var = dynamic_cast<VariableDeclaration*>(decl);
            return var->getVarType()->getType();
        } else if (instanceof <FunctionDeclaration>(decl)) {
            return FUNCTION;
        } else if (instanceof <ClassDeclaration>(decl)) {
            return CLASS;
        } else if (instanceof <InterfaceDeclaration>(decl)) {
            return INTERFACE;
        } else {
            return ERROR;
        }
    }
}

bool SymbolTable::isDeclared(std::string name) {
    return this->top().count(name) != 0;
}

void SymbolTable::pushAR() {
    std::unordered_map<std::string, Declaration*> curMap;
    symbolTable.push_back(curMap);
}

void SymbolTable::popAR() {
    symbolTable.pop_back();
}

std::unordered_map<std::string, Declaration*> SymbolTable::top() {
    return symbolTable.back();
}

void SymbolTable::push(std::string name, Declaration* decl) {
    this->top()[name] = decl;
}

void SymbolTable::pop(std::string name) {
    this->top().erase(name);
}