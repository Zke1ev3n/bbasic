#include "bbvm.h"
#include "utils.h"

int main(int argc, char **argv)
{

    if(argc < 2){
        Utils::Error("bbvm filename\n");
        return -1;
    }

    BBVM* bbvm = new BBVM();
    if(bbvm->Start() == -1){
        Utils::Error("bbvm start failed.\n");
        return -1;
    }
    if(bbvm->LoadBinFile(argv[1]) == -1){
        Utils::Error("bbvm load file failed.\n");
        return -1;
    }
    bbvm->Run();

    bbvm->Exit();

    Utils::Log("bbvm exit.\n");

	return 0;
}