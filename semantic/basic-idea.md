#### 程序基本元素分解

>   program -> stmts -> stmt 

#### 程序分解

##### declaration

声明：

-   变量声明(variable)：
    -   纯声明：`int a;`、`A a;`
    -   声明+定义：`int a = b + 1;`、`A a = new A();`
-   函数声明(function)：
    -   纯声明：`int f(int a, int b);`
    -   声明+定义：`int f(int a, int b){...}`
-   类声明(class)：
    -   纯声明：`class A;`
    -   声明+定义：`class A{...}`

##### expression

表达式：

-   赋值语句：`a = 1;`
-   基本运算：`a = b + c;`
-   调用函数：`a = f(b);`

##### statement

语句：

-   if语句：`if cond {...} else {...}`
-   for语句：`for(...){...}`
-   while语句：`while(...){...}`

#### 作用域说明

##### scope

作用域：进入if/for/while的{}、function的{}、以及class的{}内，都会得到一个新的local scope，变量的引用从本作用域内到外层再一直到全局作用域为止

#### 词法/语法分析、语义分析、LLVM

>   词法/语法分析相对独立，语义分析和LLVM可以并行做

##### 词法/语法分析

词法分析主要用lex从字符流中生成token，语法分析则是yacc利用BNF表达式将token list转化为AST

注意，此时终结符(如基本变量)作为AST里的基本节点，都已经被赋好了值

##### 语义分析

yacc的{}里的动作属于语义分析：

所有new节点的操作都只能在yacc的{}里做，`node.h`的所有类成员变量都只保存：

-   指向非终结符的指针
-   终结符的值

以`int f(int a, int b, ...)`为例：

~~~cpp
class FunctionDeclaration {
    Identifier returnType;
    Identifier func;
    std::vector<VariableDeclaration*>* paramList;
}
~~~

int和f都是终结符，只需要给Identifier赋上type类型和name名称即可

而param list作为一个整体是非终结符，需要用一个BNF的yacc推导来完成，在推导过程中，每个变量声明VariableDeclaration作为一个基本单元(向下还会继续解析，这里不再阐述)，可以看做是一个子树，我们需要返回该子树的root指针，这么些root指针组成一个vector就是param list的子树了，同样的，我们要把param list的子树的root指针返回给FunctionDeclaration节点，因此FunctionDeclaration类中会有`vector<VariableDeclaration*>*`这个成员变量，来接收param list子树



此外，语义分析还需要对AST进行类型检查，只要保证每条赋值语句、运算语句、函数调用语句的相关变量类型是对的，代码最后必然就能够成功执行

这里我选择用unordered_map来做{name: type}的映射，方便做类型检查，像之前说的，不同作用域下的map不同，需要利用栈结构来保证合理的变量引用

通常有三种类型错误：范围包括变量、函数和类，这里统称为"对象"

-   未定义：stack里的map都没有该对象

-   重复定义：stack.top()的map里已经有重名对象，此时为重复定义

    注：若栈顶的map里没有重名对象，但栈内的其他map里存在重名对象，此时栈顶作用域优先，不算重复定义

-   类型不匹配：表达式类型不匹配，如`int a = 1 + "2"`

##### LLVM

LLVM负责把AST转化为可执行的目标代码，我们只需要生成LLVM IR即可

注意，词法/语法分析中已经完成了AST，因此即使没有语法分析的类型检查，LLVM这一阶段照样可以进行，故语法分析与LLVM是可以并行开发的



