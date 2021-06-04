#include "parser/parser.h"
#include "tree/node.h"

#include <iostream>
#include <string>
#include <fstream>
#include "codegen/CodeGen.h"

using namespace std;

enum class OutputType {
    EXE, OBJ, ASM, LL
} output_type = OutputType::EXE;
enum class ParseArgException {
    HELP, ERROR, ACCEPT
};
std::string input_name = "../testCode/sample.pfl", output_name = "";
bool debug = false, keep = false, b_type = false;

ParseArgException get_args(int argc, char **argv) {
    const std::string help_str =
            "SPL Compiler\n"
            "Usage: SPL-compiler [options] file...\n"
            "Options:\n"
            "  -o <name>  Specify the name of output file.\n"
            "  -t <type>  Specify the type of output file. It can be exe, obj, asm and ll.\n"
            "             By default, executable file will be generated.\n"
            "  -d         Print debug message.\n"
            "  -k         Keep intermediate file.\n"
            "  -h         Show usage\n";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (! output_name.empty()) {
                std::cout << "more than one output file name is specified" << std::endl;
                return ParseArgException::ERROR;
            } else if (i + 1 < argc) {
                ++i;
                output_name = argv[i];
            } else {
                std::cout << "unknown output file name" << std::endl;
                return ParseArgException::ERROR;
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            debug = true;
        } else if (strcmp(argv[i], "-k") == 0) {
            keep = true;
        } else if (strcmp(argv[i], "-t") == 0) {
            if (b_type) {
                std::cout << "more than one output type is specified" << std::endl;
                return ParseArgException::ERROR;
            } else if (i + 1 < argc) {
                ++i;
                b_type = true;
                if (strcmp(argv[i], "exe") == 0) {
                    output_type = OutputType::EXE;
                } else if (strcmp(argv[i], "obj") == 0) {
                    output_type = OutputType::OBJ;
                } else if (strcmp(argv[i], "asm") == 0) {
                    output_type = OutputType::ASM;
                } else if (strcmp(argv[i], "ll") == 0) {
                    output_type = OutputType::LL;
                } else {
                    std::cout << "unknown output type" << std::endl;
                    return ParseArgException::ERROR;
                }
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            std::cout << "help" << std::endl;
            return ParseArgException::HELP;
        } else {
            if (input_name.empty()) {
                input_name = argv[i];
            } else {
                std::cout << "more than one input file is specified" << std::endl;
                return ParseArgException::ERROR;
            }
        }
    }
    if (input_name.empty()) {
        std::cout << "no input file is specified" << std::endl;
        return ParseArgException::ERROR;
    }
    return ParseArgException::ACCEPT;
}


int main(int argc, char **argv) {

    auto arg_ret = get_args(argc, argv);
    if (arg_ret != ParseArgException::ACCEPT) {
        if (arg_ret == ParseArgException::HELP) {
            return 0;
        } else {
            return -1;
        }
    }

    auto file_ret = freopen(input_name.c_str(), "r", stdin);
    if (file_ret == nullptr) {
        std::cout << "can't open file '" << input_name << "'" << std::endl;
        return -2;
    }

    Block* programBlock = buildTree();
    auto root = programBlock->genJSON();

    string jsonFile = "../visualization/AST_tree.json";
    std::ofstream astJSON(jsonFile);
    if( astJSON.is_open() ){
        astJSON << root;
        astJSON.close();
        cout << "json write to " << jsonFile << endl;
    }

    CodeGen codeGen;
    codeGen.genCode(programBlock, output_name.empty() ? "a.ll" : output_name);


    std::cout << "Hello posfol!" << std::endl;
    return 0;
}