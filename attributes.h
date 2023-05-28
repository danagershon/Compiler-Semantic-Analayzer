#ifndef HW3_ATTRIBUTES_H
#define HW3_ATTRIBUTES_H

#include <string>

enum Type {
    STRING_TYPE = 0,
    INT_TYPE = 1,
    BYTE_TYPE = 2,
    BOOL_TYPE = 3,
    VOID_TYPE = 4,
};

class ArgInfo {
public:
    std::string arg_name;
    Type arg_type;
};

#endif //HW3_ATTRIBUTES_H
