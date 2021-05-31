#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <unordered_map>
#include <vector>

#include "node.h"

/**
 * @author gehao
 * 
 * 符号表，以stack的形式保存不同作用域下的{符号: 类型}关系
 * 这些类型都是由Declaration类来描述的
 * 方案1：由于变量符号可以是变量、函数、类，因此这里的”类型“应该单独用一个类来描述
 * 方案2：map保存{name: Declaration}, 每次在当前block下扫到一个Declaration
 * 就塞进栈顶map里，这样需要类型检查时就可以从栈顶到栈底来寻找名称为name的最近的变量声明(变量、函数、类)
 * 目前采用：方案2✅，优势：无需多设计一个类，在map的push、pop过程中不会导致内存泄漏，此外，map的value是指针，可以节省内存空间
 */
class SymbolTable {
   private:
    std::vector<std::unordered_map<std::string, Declaration*>> symbolTable;

   public:
    SymbolTable() {}
    ~SymbolTable() {}

    Declaration* findSymbol(std::string name);

    void push();

    void pop();

    std::unordered_map<std::string, Declaration*> top();
};

#endif