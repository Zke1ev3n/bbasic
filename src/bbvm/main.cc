#include "anvm.h"
#include "Screen.h"

Cpu *cpu;
Screen *scn;
unsigned char *vmem;
Keyboard *keybd;
Gpu *gpu;
Storage *storage;

unsigned int LoadFile(const char *File, unsigned char *vmem)
{
    char version[16];
	FILE *fp = fopen(File, "rb");
	if (fp == NULL)
	{
		Error("Cannot open %s", File);
		return -1;
	}

	fread(version, 16, 1, fp);

	fseek(fp, 0, SEEK_END);
	int Size = ftell(fp);
	fseek(fp, 16, SEEK_SET);
	if (ferror(fp) != 0)
	{
		return -1;
	}
	fread(vmem, Size, 1, fp);
	fclose(fp);
	return Size;
}

void ExitProc()
{
	SDL2Input::WaitKey();
	delete keybd;
	delete cpu;
	delete gpu;
	delete storage;
	delete scn;
}

int main(int argc, char **argv)
{
	atexit(ExitProc);
	scn = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
	Log("Screen Device...OK!\n");
	Log("Memory...");
	vmem = (unsigned char *)malloc(MEMSIZE);
	const char *_binFile = (argc != 2)? DEFAULTBIN : argv[1];
	if (vmem == NULL)
	{
		Error("Cannot create virtual memory.");
		return -1;
	}
	memset(vmem, '\0', MEMSIZE);
	Log("OK!\nLoad Bootstrap...");
	int binlen = LoadFile(_binFile, vmem);
	if (binlen == -1)
	{
		Error("Cannot load [%s] to memory.", _binFile);
		return -1;
	}
	Log("OK!\nCPU...");
	cpu = new Cpu();
	Log("OK!\nGPU...");
	gpu = new Gpu();
	Log("OK!\nKeyboard...");
	keybd = new Keyboard();
	Log("OK!\nStorage...");
	storage = new Storage();
	Log("OK!\nBooting...\n");
	cpu->StateBase = binlen;

	cpu->Run(vmem);

	scn->Display("anvm exit");
	return 0;
}