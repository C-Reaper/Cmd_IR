//#include "/home/codeleaded/System/Static/Library/IRVM.h"
#include "/home/codeleaded/System/Static/Library/IRVM_Exe.h"

#define IRVM_TESTTYPE       IRVM_TYPE_I16
#define IRVM_TESTTYPE_C     short

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
int IRVM_Testing(CStr file,Number a_out,Number b_in,Number c_in){
    IRVM vm = IRVM_New();
    IRVM_AddScript(&vm,file);
    IRVM_Build(&vm);
    
    IRVM_Exe exe = IRVM_Exe_New(vm);
    //IRVM_Exe_LinkFunction(&exe,"i16_println",IRVM_Exe_Func_i16_println);
    //IRVM_Exe_LinkFunction(&exe,"println",IRVM_Exe_Func_println);

    IRVM_Exe_Variable a = IRVM_Exe_Variable_New("a",IRVM_TESTTYPE,(Number[]){ 0UL }, IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    IRVM_Exe_Variable b = IRVM_Exe_Variable_New("b",IRVM_TESTTYPE,(Number[]){ b_in },IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    IRVM_Exe_Variable c = IRVM_Exe_Variable_New("c",IRVM_TESTTYPE,(Number[]){ c_in },IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    
    IRVM_Exe_CallFunction(&exe,"main",(IRVM_Exe_Variable[]){
        a,
        b,
        c,
        IRVM_Exe_Variable_Null()
    });
    //IRVM_Exe_Variable_Print(&a);

    const Number v_a = *(IRVM_TESTTYPE_C*)a.data;
    const Number v_b = *(IRVM_TESTTYPE_C*)b.data;
    const Number v_c = *(IRVM_TESTTYPE_C*)c.data;
    const int result = v_a == a_out && v_b == b_in && v_c == c_in;

    IRVM_Exe_Variable_Free(&c);
    IRVM_Exe_Variable_Free(&b);
    IRVM_Exe_Variable_Free(&a);

    //IRVM_Exe_Print(&exe);
    IRVM_Exe_Free(&exe);
    return result;
}
int IRVM_Testing_Opt(CStr file,Number a_out,Number b_in,Number c_in){
    IRVM vm = IRVM_New();
    IRVM_AddScript(&vm,file);
    IRVM_Build(&vm);
    IRVM_Optimiser_Exe(&vm,0U);
    
    IRVM_Exe exe = IRVM_Exe_New(vm);
    //IRVM_Exe_LinkFunction(&exe,"i16_println",IRVM_Exe_Func_i16_println);
    //IRVM_Exe_LinkFunction(&exe,"println",IRVM_Exe_Func_println);

    IRVM_Exe_Variable a = IRVM_Exe_Variable_New("a",IRVM_TESTTYPE,(Number[]){ 0UL }, IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    IRVM_Exe_Variable b = IRVM_Exe_Variable_New("b",IRVM_TESTTYPE,(Number[]){ b_in },IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    IRVM_Exe_Variable c = IRVM_Exe_Variable_New("c",IRVM_TESTTYPE,(Number[]){ c_in },IRVM_Impl_Size(IRVM_TESTTYPE),0,0);
    
    IRVM_Exe_CallFunction(&exe,"main",(IRVM_Exe_Variable[]){
        a,
        b,
        c,
        IRVM_Exe_Variable_Null()
    });
    //IRVM_Exe_Variable_Print(&a);

    const Number v_a = *(IRVM_TESTTYPE_C*)a.data;
    const Number v_b = *(IRVM_TESTTYPE_C*)b.data;
    const Number v_c = *(IRVM_TESTTYPE_C*)c.data;
    const int result = v_a == a_out && v_b == b_in && v_c == c_in;

    IRVM_Exe_Variable_Free(&c);
    IRVM_Exe_Variable_Free(&b);
    IRVM_Exe_Variable_Free(&a);

    //IRVM_Exe_Print(&exe);
    IRVM_Exe_Free(&exe);
    return result;
}
int IRVM_Testing_Exe(CStr file,Number a_out,Number b_in,Number c_in){
    const int as_result = IRVM_Testing(file,a_out,b_in,c_in);
    const int as_result_opt = IRVM_Testing_Opt(file,a_out,b_in,c_in);
    printf("Nrm: %-24s: %s\n",file,as_result ? "Passed" : "Failed!!!");
    printf("Opt: %-24s: %s\n",file,as_result_opt ? "Passed" : "Failed!!!");
    return as_result + as_result_opt;
}

int main(int argc,char** argv){
    const int max_successful = 9 * 2;
    int successful = 0;

    printf("--------------------------------\n");
    successful += IRVM_Testing_Exe("./test/Opt/AS."  IRVM_TYPE,9,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/SR."  IRVM_TYPE,11,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/CF."  IRVM_TYPE,30,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/CP."  IRVM_TYPE,-1,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/DCE." IRVM_TYPE,30,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/CSE." IRVM_TYPE,90,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/UCE." IRVM_TYPE,0,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/BS."  IRVM_TYPE,0,10,20);
    successful += IRVM_Testing_Exe("./test/Opt/BBS." IRVM_TYPE,60,10,20);
    printf("--------------------------------\n");

    printf("Test result: %d/%d\n",successful,max_successful);
    

    //if(argc < 2){
    //    printf("[IRVM]: Arguments -> Usage: irvm <.iralx>\n");
    //    return 0;
    //}

    /*
    Algebraic Simplification:           "./test/Opt/AS."
    Strength Reduction:                 "./test/Opt/SR."
    Constant Folding:                   "./test/Opt/CF."
    Constant Propagation:               "./test/Opt/CP."
    Dead Code Elimination:              "./test/Opt/DCE."
    Common Subexpression Elimination:   "./test/Opt/CSE."
    Unreachable Code Elimination:       "./test/Opt/UCE."
    Branch Simplification:              "./test/Opt/BS."
    */
    
    /*
    IRVM vm = IRVM_New();
    IRVM_AddScript(&vm,"./test/Opt/BBS." IRVM_TYPE);
    IRVM_Print(&vm);
    IRVM_Build(&vm);
    IRVM_Optimiser_Exe(&vm,0U);
    IRVM_Print(&vm);
    //IRVM_Free(&vm);
    
    IRVM_Exe exe = IRVM_Exe_New(vm);
    
    IRVM_Exe_Variable a = IRVM_Exe_Variable_New("a",IRVM_TYPE_I16,(Number[]){ 0UL }, IRVM_Impl_Size(IRVM_TYPE_I16),0,0);
    IRVM_Exe_Variable b = IRVM_Exe_Variable_New("b",IRVM_TYPE_I16,(Number[]){ 10UL },IRVM_Impl_Size(IRVM_TYPE_I16),0,0);
    IRVM_Exe_Variable c = IRVM_Exe_Variable_New("c",IRVM_TYPE_I16,(Number[]){ 20UL },IRVM_Impl_Size(IRVM_TYPE_I16),0,0);
    
    IRVM_Exe_CallFunction(&exe,"main",(IRVM_Exe_Variable[]){
        a,
        b,
        c,
        IRVM_Exe_Variable_Null()
    });
    
    IRVM_Exe_Variable_Print(&a);
    IRVM_Exe_Variable_Print(&b);
    IRVM_Exe_Variable_Print(&c);

    IRVM_Exe_Variable_Free(&c);
    IRVM_Exe_Variable_Free(&b);
    IRVM_Exe_Variable_Free(&a);

    IRVM_Exe_Free(&exe);
    */
    return 0;
}