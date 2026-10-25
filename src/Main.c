//#include "/home/codeleaded/System/Static/Library/IRVM.h"
#include "/home/codeleaded/System/Static/Library/IRVM_Exe.h"

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
    IRVM_AddScript(&vm,"./code/Main." IRVM_TYPE);
    
    IRVM_Exe exe = IRVM_Exe_New(vm,"./bin");

    IRVM_Exe_Variable a = IRVM_Exe_Variable_New("a","i16",(Number[]){ 1UL },IRVM_Impl_Size("i16"),0,0);
    IRVM_Exe_CallFunction(&exe,"main",(IRVM_Exe_Variable[]){
        a,
        IRVM_Exe_Variable_Null()
    });
    IRVM_Exe_Variable_Print(&a);
    IRVM_Exe_Variable_Free(&a);
    
    IRVM_Exe_Free(&exe);
    return 0;
}