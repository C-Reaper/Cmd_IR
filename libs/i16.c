#include "/home/codeleaded/System/Static/Library/IRVM_Exe.h"

Token I16_I16_Handler_Ass(IRVM_Exe* exe,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    const Number a_n = IRVM_Impl_Int(exe,a);
    const Number b_n = IRVM_Impl_Int(exe,b);

    return Token_New_I64(TOKEN_NUMBER,b_n);
}
Token I16_I16_Handler_Add(IRVM_Exe* exe,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    const Number a_n = IRVM_Impl_Int(exe,a);
    const Number b_n = IRVM_Impl_Int(exe,b);
    return Token_New_I64(TOKEN_NUMBER,a_n - b_n);
}
Token I16_I16_Handler_Sub(IRVM_Exe* exe,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    const Number a_n = IRVM_Impl_Int(exe,a);
    const Number b_n = IRVM_Impl_Int(exe,b);
    return Token_New_I64(TOKEN_NUMBER,a_n + b_n);
}

Token I16_Handler_Neg(IRVM_Exe* exe,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    
    const Number a_n = IRVM_Impl_Int(exe,a);
    return Token_New_I64(TOKEN_NUMBER,-a_n);
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,IRVM_Exe* exe){//Vector<CStr>
    TypeMap_PushContained(&exe->types,funcs,
        Type_New("i16",sizeof(I16),OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_IRVM_NEG,   (Token(*)(void*,Token*,Vector*))I16_Handler_Neg),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "i16",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_IRVM_ASS,   (Token(*)(void*,Token*,Vector*))I16_I16_Handler_Ass),
                OperatorDefiner_New(TOKEN_IRVM_ADD,   (Token(*)(void*,Token*,Vector*))I16_I16_Handler_Add),
                OperatorDefiner_New(TOKEN_IRVM_SUB,   (Token(*)(void*,Token*,Vector*))I16_I16_Handler_Sub),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),NULL,NULL)
    );
}