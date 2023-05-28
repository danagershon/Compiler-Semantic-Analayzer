#ifndef HW3_BISON_CODE_H
#define HW3_BISON_CODE_H

#include "SymTable.hpp"

extern int yylineno;

void initSymTable(SymTable* symbol_table, std::vector<std::string>& predefined_func);
void checkMain(SymTable* symbol_table);

bool isNumeric(Type type);
Type checkIfBool(Type type);
Type checkByteVal(int val);

Type checkBinopExp(Type type1, Type type2);
Type checkRelopExp(Type type1, Type type2);
Type checkLogicExp(Type type1, Type type2);
Type checkConversion(Type target_type, Type type);

Type checkVarDeclaredBeforeUsed(SymTable* symbol_table, const char* name);
void checkVarNotDeclared(SymTable* symbol_table, const char* name);
void checkAssign(const char* id_name, Type id_type, Type exp_type);
void handleVarDec(SymTable* symbol_table, const char* name, Type type);
void handleVarInitialization(SymTable* symbol_table, const char* name, Type type, Type exp_type);
void handleVarReassign(SymTable* symbol_table, const char* name, Type exp_type);
Type checkIfLegalCall(SymTable* symbol_table, const char* func_name, std::vector<Type>* arg_types);

void checkBreakInWhile(std::vector<bool>& in_while);
void checkContinueInWhile(std::vector<bool>& in_while);
void checkEmptyRet(Type last_ret_type);
void checkExpRet(Type last_ret_type, Type exp_type);

void addFunc(SymTable* symbol_table, const char* func_name, Type ret_type, std::vector<ArgInfo*>* arg_list, bool is_override);
void addFuncScope(SymTable* symbol_table, std::vector<ArgInfo*>* arg_list);

void addScope(SymTable* symbol_table);
void printAndDelTopScope(SymTable* symbol_table);

#endif //HW3_BISON_CODE_H
