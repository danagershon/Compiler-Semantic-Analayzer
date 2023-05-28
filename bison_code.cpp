#include "bison_code.hpp"
#include <algorithm>

void initSymTable(SymTable* symbol_table, std::vector<std::string>& predefined_func){
    symbol_table->addFuncSymbol(predefined_func[0].c_str(), VOID_TYPE, {STRING_TYPE}, false);
    symbol_table->addFuncSymbol(predefined_func[1].c_str(), VOID_TYPE, {INT_TYPE}, false);
}

void checkMain(SymTable* symbol_table){
    std::string name = "main";
    std::vector<SymTableEntry*> matches = symbol_table->getFuncSymbol(name.c_str(), {});

    // change conditions for error according to staff
    if(matches.empty() || matches[0]->type != VOID_TYPE){
        output::errorMainMissing();
        exit(0);
    }
}

bool isNumeric(Type type){
    return type == INT_TYPE || type == BYTE_TYPE;
}

Type checkIfBool(Type type){
    if(type != BOOL_TYPE) {
        output::errorMismatch(yylineno);
        exit(0);
    }

    return BOOL_TYPE;
}

Type checkByteVal(int val){
    if(val > 255){
        output::errorByteTooLarge(yylineno, std::to_string(val));
        exit(0);
    }

    return BYTE_TYPE;
}

Type checkBinopExp(Type type1, Type type2){
    if(!isNumeric(type1) || !isNumeric(type2)){
        output::errorMismatch(yylineno);
        exit(0);
    }
    if(type1 == INT_TYPE || type2 == INT_TYPE){
        return INT_TYPE;
    }

    return BYTE_TYPE;
}

Type checkRelopExp(Type type1, Type type2){
    if(!isNumeric(type1) || !isNumeric(type2)) {
        output::errorMismatch(yylineno);
        exit(0);
    }

    return BOOL_TYPE;
}

Type checkLogicExp(Type type1, Type type2){
    checkIfBool(type1);
    checkIfBool(type2);
    return BOOL_TYPE;
}

Type checkConversion(Type target_type, Type type){
    bool is_legal = (target_type == INT_TYPE || target_type == BYTE_TYPE) && isNumeric(type);
    if(!is_legal){
        output::errorMismatch(yylineno);
        exit(0);
    }

    return target_type;
}

Type checkVarDeclaredBeforeUsed(SymTable* symbol_table, const char* name){
    SymTableEntry* symbol = symbol_table->getVarSymbol(name);
    if(!symbol){
        output::errorUndef(yylineno, std::string(name));
        exit(0);
    }

    return symbol->type;
}

void checkVarNotDeclared(SymTable* symbol_table, const char* name){
    if(symbol_table->getVarSymbol(name) || !symbol_table->getFuncsByName(name).empty()){
        output::errorDef(yylineno, std::string(name));
        exit(0);
    }
}

void checkAssign(const char* id_name, Type id_type, Type exp_type){
    bool is_legal = (id_type == exp_type) || (id_type == INT_TYPE && exp_type == BYTE_TYPE);
    if(!is_legal){
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void handleVarDec(SymTable* symbol_table, const char* name, Type type){
    checkVarNotDeclared(symbol_table, name);
    symbol_table->addVarSymbol(name, type);
}

void handleVarInitialization(SymTable* symbol_table, const char* name, Type type, Type exp_type){
    checkVarNotDeclared(symbol_table, name);
    checkAssign(name, type, exp_type);
    symbol_table->addVarSymbol(name, type);
}

void handleVarReassign(SymTable* symbol_table, const char* name, Type exp_type){
    Type id_type = checkVarDeclaredBeforeUsed(symbol_table, name);
    checkAssign(name, id_type, exp_type);
}

Type checkIfLegalCall(SymTable* symbol_table, const char* func_name, std::vector<Type>* arg_types){
    std::vector<SymTableEntry*> matches = symbol_table->getFuncsByName(func_name);
    if(matches.empty()) {
        output::errorUndefFunc(yylineno, std::string(func_name));
        exit(0);
    }

    std::vector<SymTableEntry*> candidates;
    if(arg_types){
        candidates = symbol_table->getFuncSymbol(func_name, *arg_types);
    } else{
        candidates = symbol_table->getFuncSymbol(func_name, {});
    }

    if(candidates.empty()) {
        output::errorPrototypeMismatch(yylineno, std::string(func_name));
        exit(0);
    }
    // new ambiguous rule
    if(candidates.size() > 1){
        output::errorAmbiguousCall(yylineno, std::string(func_name));
        exit(0);
    }

    return candidates[0]->type;
}

void checkBreakInWhile(std::vector<bool>& in_while){
    if(in_while.empty()){
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void checkContinueInWhile(std::vector<bool>& in_while){
    if(in_while.empty()){
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void checkEmptyRet(Type last_ret_type){
    if(last_ret_type != VOID_TYPE){
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void checkExpRet(Type last_ret_type, Type exp_type){
    if(last_ret_type == VOID_TYPE){
        output::errorMismatch(yylineno);
        exit(0);
    }

    bool is_legal = last_ret_type == exp_type || (last_ret_type == INT_TYPE && exp_type == BYTE_TYPE);
    if(!is_legal){
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void addFunc(SymTable* symbol_table, const char* func_name, Type ret_type, std::vector<ArgInfo*>* arg_list, bool is_override){
    // check if a variable already exists with the same name
    if(symbol_table->getVarSymbol(func_name)){
        output::errorDef(yylineno, std::string(func_name));
        exit(0);
    }
    // change conditions according to staff
    // if arg_list is null then no args
    if(std::string(func_name) == "main" && !arg_list && ret_type == VOID_TYPE && is_override){
        output::errorMainOverride(yylineno);
        exit(0);
    }

    std::vector<Type> arg_types;
    std::vector<std::string> arg_names;

    if(arg_list){
        for(auto& arg_info: *arg_list){
            if(symbol_table->getVarSymbol(arg_info->arg_name.c_str()) || !symbol_table->getFuncsByName(arg_info->arg_name.c_str()).empty() || func_name == arg_info->arg_name || std::find(arg_names.begin(),arg_names.end(),arg_info->arg_name) != arg_names.end()){
                output::errorDef(yylineno, arg_info->arg_name);
                exit(0);
            }
            arg_types.push_back(arg_info->arg_type);
            arg_names.push_back(arg_info->arg_name);
        }
    }

    std::vector<SymTableEntry*> matches = symbol_table->getFuncsByName(func_name);

    // check for another func with the exact same prototype
    for(auto& match: matches){
        if(match->type == ret_type && match->arg_types == arg_types){
            output::errorDef(yylineno, std::string(func_name));
            exit(0);
        }
    }

    // case of one other func that wasn'spring23-students_tests declared with override
    if(matches.size() == 1 && !matches[0]->is_override){
        output::errorFuncNoOverride(yylineno, std::string(func_name));
        exit(0);
    }

    /* if there is more than one match then all of them should
     * have been declared with override */
    if(!matches.empty() && !is_override){
        output::errorOverrideWithoutDeclaration(yylineno, std::string(func_name));
        exit(0);
    }

    symbol_table->addFuncSymbol(func_name, ret_type, arg_types, is_override);
}

void addFuncScope(SymTable* symbol_table, std::vector<ArgInfo*>* arg_list){
    symbol_table->addNewScope();
    int offset = -1;

    if(arg_list){
        for(auto& arg_info: *arg_list){
            symbol_table->addArgSymbol(arg_info->arg_name.c_str(), arg_info->arg_type, offset);
            offset--;
        }
    }
}

void addScope(SymTable* symbol_table){
    symbol_table->addNewScope();
}

void printAndDelTopScope(SymTable* symbol_table){
    symbol_table->printTopScope();
    symbol_table->deleteTopScope();
}

/*
 * When we can determine exp type:
 * 1. Assigning: [Type] id = exp:
 *    - if exp type can'spring23-students_tests be id type => mismatch
 *    - can be caught in Call check: if exp type can be id type but from multiple src funcs => ambiguity
 * 2. Returning: ret exp:
 *    - if exp type can'spring23-students_tests be func return type => mismatch
 *    - can be caught in Call check: if exp type can be func return type but from multiple src func => ambiguity
 *    - won'spring23-students_tests happen: if exp type can be int or byte and func ret type is int => ambiguity
 * 3. In if/while condition:
 *    - if exp type can'spring23-students_tests be bool => mismatch
 *    - can be caught in Call check: if exp type can be bool but from multiple src func => ambiguity
 * 4. Casting: (type)exp:
 *    - if exp can'spring23-students_tests be int or byte => mismatch
 *    - can be caught in Call check: if exp can be int or byte but from multiple src func => ambiguity
 *    - won'spring23-students_tests happen: exp can be int and byte
 * 5. In relop: exp1 >/</>=/<=/==/!= exp2:
 *    - if exp1 and exp2 can'spring23-students_tests be numeric => mismatch
 *    - can be caught in Call check: if exp1 or exp2 can be numeric from multiple src func => ambiguity
 * 6. In logic: exp1 and/or exp2 , not exp:
 *    - if exp1 or exp2 can'spring23-students_tests be bool => mismatch
 *    - can be caught in Call check: if exp1 or exp2 can be bool from multiple src func => ambiguity
 * 7. In binop: exp1 op exp2:
 *    - if exp1 or exp2 can'spring23-students_tests be numeric => mismatch
 *    - won'spring23-students_tests happen: if exp1 or exp2 can be int and byte we can'spring23-students_tests detect
 *      ambiguity until exp is assigned to numeric var/arg
 */