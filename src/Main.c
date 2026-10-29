//#include "/home/codeleaded/System/Static/Library/IRVM.h"
#include "/home/codeleaded/System/Static/Library/IRVM_Exe.h"

FunctionRT IRVM_Exe_Func_i16_println(IRVM_Exe* exe,Vector* vars){
    if(vars->size != 1){
        IRVM_ErrorHandler(&exe->vm,"Exe_Func_i16_println: args invalid!");
        return FUNCTIONRT_ERROR;
    }else{
        IRVM_Exe_Variable* arg = (IRVM_Exe_Variable*)Vector_Get(vars,0);
        const Number n = IRVM_Int_From(exe,arg->data,arg->type);
        printf("%" TYPES_I64_FORMAT "\n",n);
    }
    return FUNCTIONRT_NONE;
}
FunctionRT IRVM_Exe_Func_println(IRVM_Exe* exe,Vector* vars){
    for(int i = 0;i<vars->size;i++){
        IRVM_Exe_Variable* arg = (IRVM_Exe_Variable*)Vector_Get(vars,i);
        const Number n = IRVM_Int_From(exe,arg->data,arg->type);
        printf("%" TYPES_I64_FORMAT,n);

        if(i + 1 < vars->size) printf(" ");
    }
    printf("\n");
    return FUNCTIONRT_NONE;
}

int main(int argc,char** argv){
    //if(argc < 2){
    //    printf("[IRVM]: Arguments -> Usage: irvm <.iralx>\n");
    //    return 0;
    //}

    /*
    IRVM vm = IRVM_New();
    IRVM_AddScript(&vm,"./code/Main." IRVM_TYPE);
    IRVM_Print(&vm);
    IRVM_Save(&vm,"./code/Output." IRVM_TYPE);
    IRVM_Free(&vm);
    */

    IRVM vm = IRVM_New();
    /*
    Algebraic Simplification:   "./test/Opt/AS."
    Strength Reduction:         "./test/Opt/SR."
    Constant Folding:           "./test/Opt/CF."
    Constant Propagation:       "./test/Opt/CP."
    */
    IRVM_AddScript(&vm,"./test/Opt/AS." IRVM_TYPE);
    IRVM_Print(&vm);
    IRVM_Build(&vm);
    IRVM_Optimiser_Exe(&vm,0U);
    IRVM_Print(&vm);
    IRVM_Free(&vm);
    
    /*
    IRVM_Exe exe = IRVM_Exe_New(vm);
    IRVM_Exe_LinkFunction(&exe,"i16_println",IRVM_Exe_Func_i16_println);
    IRVM_Exe_LinkFunction(&exe,"println",IRVM_Exe_Func_println);

    IRVM_Exe_Variable a = IRVM_Exe_Variable_New("a",IRVM_TYPE_I16,(Number[]){ 1UL },IRVM_Impl_Size(IRVM_TYPE_I16),0,0);
    IRVM_Exe_CallFunction(&exe,"main",(IRVM_Exe_Variable[]){
        a,
        IRVM_Exe_Variable_Null()
    });
    IRVM_Exe_Variable_Print(&a);
    IRVM_Exe_Variable_Free(&a);
    IRVM_Exe_Print(&exe);
    IRVM_Exe_Free(&exe);
    */
    return 0;
}