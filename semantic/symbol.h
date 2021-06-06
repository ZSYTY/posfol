#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <unordered_map>
#include <vector>

#include "../tree/node.h"
#include "../tree/type.h"

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
    std::vector<std::unordered_map<std::string, const Declaration*> > symbolTable;

   public:
    SymbolTable();
    ~SymbolTable() {}
    // 寻找该符号是否存在
    const Declaration* findSymbol(std::string name);
    // 如果是变量则返回具体类型，如果是函数、类、接口，则返回对应抽象类型
    Type getSymbolType(std::string name);
    // 判断在当前作用域内是否已经声明，注：在外层作用域声明的话，本层作用域会用新的symbol引用覆盖
    bool isDeclared(std::string name);
    // 往栈里新push一个AR，表示进入一个新的作用域(Block)
    void pushAR();
    // 从栈顶pop一个AR，表示跳出该作用域(Block)
    void popAR();
    // 获取栈顶的AR，即当前作用域(Block)
    std::unordered_map<std::string, const Declaration*> top();

    // push新的Declaration
    void push(std::string name, const Declaration* decl);
    // pop旧的Declaration
    void pop(std::string name);
    // 判断当前是否处于全局作用域
    bool isGlobal();
};

#endif