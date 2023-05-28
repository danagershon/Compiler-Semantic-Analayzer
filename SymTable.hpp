#ifndef HW3_SYMTABLE_H
#define HW3_SYMTABLE_H

#include "attributes.h"
#include "hw3_output.hpp"

class SymTableEntry {
public:
    int scope;
    std::string name;
    int offset;
    Type type;

    // for functions
    std::vector<Type> arg_types;
    bool is_func;
    bool is_override;

    SymTableEntry* next;

    SymTableEntry(int scope,
                  const char* name,
                  int offset,
                  Type type,
                  std::vector<Type> arg_types,
                  bool is_func,
                  bool is_override,
                  SymTableEntry* next);
    ~SymTableEntry() = default;
};

// linked list of SymTableEntry
class SymTable {
    SymTableEntry* head;
    int curr_scope;
    std::vector<int> offset_stack;

public:
    SymTable();
    ~SymTable();

    void addVarSymbol(const char* name, Type type);
    void addArgSymbol(const char* name, Type type, int offset);
    void addFuncSymbol(const char* name, Type ret_type, std::vector<Type> arg_types, bool is_override);

    SymTableEntry* getVarSymbol(const char* name);
    std::vector<SymTableEntry*> getFuncSymbol(const char* name, std::vector<Type> arg_types);
    std::vector<SymTableEntry*> getFuncsByName(const char* func_name);

    void deleteTopScope();
    void addNewScope();
    void printTopScope();
};


#endif //HW3_SYMTABLE_H
