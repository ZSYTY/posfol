#include "symbol.h"

#include "sem_util.h"

const Declaration* SymbolTable::findSymbol(std::string name) {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); it++) {
        if (it->count(name) != 0) {
            return (*it)[name];
        }
    }
    return nullptr;
}

Type SymbolTable::getSymbolType(std::string name) {
    const Declaration* decl = this->findSymbol(name);
    if (decl == nullptr) {
        return ERROR;
    } else {
        if (instanceof <const VariableDeclaration>(decl)) {
            const VariableDeclaration* var = dynamic_cast<const VariableDeclaration*>(decl);
            return var->getVarType()->getType();
        } else if (instanceof <const FunctionDeclaration>(decl)) {
            return FUNCTION_REAL;
        } else if (instanceof <const ClassDeclaration>(decl)) {
            return CLASS_REAL;
        } else if (instanceof <const InterfaceDeclaration>(decl)) {
            return INTERFACE_REAL;
        } else {
            return ERROR;
        }
    }
}

bool SymbolTable::isDeclared(std::string name) {
    return this->top().count(name) != 0;
}

void SymbolTable::pushAR() {
    std::unordered_map<std::string, const Declaration*> curMap;
    symbolTable.push_back(curMap);
}

void SymbolTable::popAR() {
    symbolTable.pop_back();
}

std::unordered_map<std::string, const Declaration*>& SymbolTable::top() {
    return symbolTable.back();
}

void SymbolTable::push(std::string name, const Declaration* decl) {
    this->top()[name] = decl;
}

void SymbolTable::pop(std::string name) {
    this->top().erase(name);
}

SymbolTable::SymbolTable() {
    pushAR();
}

bool SymbolTable::isGlobal() {
    return symbolTable.size() == 1;
}
