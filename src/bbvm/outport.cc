#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "bbvm.h"

static union _conv
{
	unsigned int i;
	float f;
} conv;


void BBVM::OutPort(unsigned int Port, unsigned int Argu)
{
    switch(Port)
    {
	case 0:		// disp integer + \n
		scn_->Display((int)Argu);
		scn_->NewLine();
		break;
	case 1:		// disp string + \n
		scn_->Display((char *)this->GetIOString(Argu));
		scn_->NewLine();
		break;
	case 2:		// disp string
		scn_->Display((char *)this->GetIOString(Argu));
		break;
	case 3:		// disp integer
		scn_->Display((int)Argu);
		break;
	case 4:		// disp charactor
		{
			char tmp[2] = {(char)Argu, '\0'};
			scn_->Display(tmp);
		}
		break;
	case 5:		// disp float
		conv.i = Argu;
		scn_->Display(conv.f);
		break;
	case 10:		// input int
		this->r3 = GetInteger();
		break;
	case 11:		// input string
		this->StrMan->PutString(this->r3, GetString());
		break;
	case 12:		// input float
		conv.f = GetFloat();
		this->r3 = conv.i;
		break;
	case 13:		// get data as integer
		this->r3 = GetMem(this->DataPtr);
		this->DataPtr += 4;
		break;
	case 14:		// get data as string
		{
			unsigned char *tmp = this->GetIOString(this->DataPtr);
			this->DataPtr += strlen((char *)tmp) + 1;
			this->StrMan->PutString(this->r3, tmp);
		}
		break;
	case 15:		// get data as float
		this->r3 = GetMem(this->DataPtr);
		this->DataPtr += 4;
		break;
	case 16:		// set simulator screen size
		scn_->SetScreenSize(this->r2, this->r3);
		break;
	case 17:		// allocate a surface
	    //TODO
		this->r3 = renderer_->AllocSurface();
		break;
	case 18:		// free a surface
		renderer_->FreeSurface(this->r3);
		break;
	case 19:		// load picture
		this->r3 = (unsigned int)renderer_->LoadPicture((char *)this->GetIOString(this->r3), this->r2);
		break;
	case 20:		// copy rectange
		renderer_->DrawPicture(
						GetMem(this->r3 + 32), GetMem(this->r3 + 28), GetMem(this->r3 + 24),
						GetMem(this->r3 + 20), GetMem(this->r3 + 16), GetMem(this->r3 + 12),
						GetMem(this->r3 + 8), GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 21:		// show surface
		renderer_->CloneSurface(this->r3, -1);
		break;
	case 22:		// clone surface
		renderer_->CloneSurface(this->r3, this->r2);
		break;
	case 23:		// fill surface
		renderer_->FillSurface(
						GetMem(this->r3 + 20), GetMem(this->r3 + 16), GetMem(this->r3 + 12),
						GetMem(this->r3 + 8), GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 24:		// write pixel
		renderer_->WritePixel(GetMem(this->r3 + 12), GetMem(this->r3 + 8),
						GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 25:		// read pixel
		this->r3 = renderer_->ReadPixel(GetMem(this->r3 + 8), GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 26:		// free picture
		renderer_->FreePicture(this->r3);
		break;
	case 27:		// delay
		scn_->Delay(this->r3);
		break;
	case 32:		// set random seed
		srand(this->r3);
		break;
	case 33:		// get random
		this->r3 = rand() % this->r3;
		break;
	case 34:		// keypress
//		this->r3 = (SDL2Input::KeyPress() == this->r3)? 1 : 0;
//		break;
//      this->r3 = (scn->KeyPressed() == this->r3) ? 1 : 0;
//      break;
        this->r3 = input_->KeyPressed(this->r3) ? 1 : 0;
        break;
	case 35:		// clean screen
		scn_->CleanScreen();
		break;
	case 36:		// set locate as text
		scn_->SetTextLocation(r2, r3);
		break;
	case 37:		// set font color
		scn_->SetTextColor(GetMem(this->r3 + 8), GetMem(this->r3 + 4));
		break;
	case 38:		// set font size
		scn_->SetFont(this->r3);
		break;
	case 39:		// wait key
		this->r3 = input_->WaitKey();
		break;
	case 40:		// get picture width
		this->r3 = renderer_->GetPictureWidth(this->r3);
		break;
	case 41:		// get picture heigth
		this->r3 = renderer_->GetPictureHeigth(this->r3);
		break;
	case 42:		// set locate as pixel
		scn_->SetDispPosition(this->r2, this->r3);
		break;
	case 43:		// clone a part of surface
		renderer_->CloneSurface(
							GetMem(this->r3), GetMem(this->r3 + 4),
							GetMem(this->r3 + 12), GetMem(this->r3 + 8));
		break;
	case 44:		// set background mode
		scn_->SetTransparent(this->r3 == 1);
		break;
	case 45:		// get key charactor string
		{
			unsigned char tmp[2];
			tmp[0] = input_->WaitKey();
			tmp[1] = '\0';
			this->StrMan->PutString(this->r3, tmp);
		}
		break;
	case 46:		// get key code
	    //TODO get key code
		this->r3 = input_->WaitKey();
		break;
	case 48:		// open file
		storage_->OpenFile((char *)this->GetIOString(this->r3), this->r1);
		break;
	case 49:		// close file
		storage_->CloseFile(Argu);
		break;
	case 50:		// read from file
		switch(Argu)
		{
		case 16:	// Int
			this->r3 = storage_->ReadFile_Int(this->r1, this->r2);
			break;
		case 17:	// Float
			conv.f = storage_->ReadFile_Float(this->r1, this->r2);
			this->r3 = conv.i;
			break;
		case 18:	// String
			unsigned char *tmp = storage_->ReadFile_String(this->r1, this->r2);
			this->StrMan->PutString(this->r3, tmp);
			break;
		}
		break;
	case 51:		// write to file
		switch(Argu)
		{
		case 16:
			storage_->WriteFile_Int32(this->r1, this->r2, this->r3);
			break;
		case 17:
			storage_->WriteFile_Int32(this->r1, this->r2, this->r3);
			break;
		case 18:
			storage_->WriteFile_String(this->r1, this->r2, (char *)this->GetIOString(this->r3));
			break;
		}
		break;
	case 52:		// feof
		this->r3 = storage_->Eof(this->r3);
		break;
	case 53:		// get file size
		this->r3 = storage_->GetFileSize(this->r3);
		break;
	case 54:		// get position
		this->r3 = storage_->GetPosition(this->r3);
		break;
	case 55:		// fseek
		storage_->MovePosition(this->r2, this->r3);
		break;
	case 64:		// set pen
		renderer_->SetPenColor(GetMem(this->r3 + 12), GetMem(this->r3));
		break;
	case 65:		// set brush
		break;
	case 66:		// move pen
		renderer_->MovePen(this->r1, this->r2, this->r3);
		break;
	case 67:		// draw line
		renderer_->DrawLine(this->r1, this->r2, this->r3);
		break;
	case 68:		// draw rectange
		renderer_->DrawRectangle(GetMem(this->r3 + 16),
							GetMem(this->r3 + 12), GetMem(this->r3 + 8),
							GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 69:		// draw circle
		renderer_->DrawCircle(
						GetMem(this->r3 + 12), GetMem(this->r3 + 8),
							GetMem(this->r3 + 4), GetMem(this->r3));
		break;
	case 80:		// vm test - useless
	    //复制部分画布扩展
	    //TODO 扩展
        renderer_->CloneSurface(
                GetMem(this->r3 + 28), GetMem(this->r3 + 24),
                GetMem(this->r3 + 20), GetMem(this->r3 + 16), GetMem(this->r3 + 12), GetMem(this->r3 + 8), GetMem(this->r3 + 4), GetMem(this->r3));
		break;
    }
}


int BBVM::InputNewline(Point ptr, int screen_width, int char_width){
    int free_char = ((screen_width - ptr.x + 1) - char_width) / char_width + 1;
    this->input_buffer_->push_back(new Line);
    this->input_buffer_->back()->PrintPosition = ptr;
    this->input_buffer_->back()->LineText = "";
    return free_char;
}


//从键盘输入字符串
unsigned char* BBVM::GetKeyString()
{
    this->input_buffer_ = new vector<Line*>();
    bool quit = false;
    int screen_width, screen_height;
    int char_width = scn_->GetFontWidth();
    scn_->GetScreenSize(&screen_width, &screen_height);
    int FreeChar = InputNewline(scn_->GetDispPosition(), screen_width, screen_height);
    while (quit == false) {
        //TODO
        unsigned char key = input_->WaitKey(true);
        //unsigned char key = input_->GetKeycode();
        if (key == KEYCODE_ENTER) {
            quit = true;
//        } else if (key == SDLK_ESCAPE) {
//            scn->NewLine();
//            scn->Display("reinput:");
//            for (unsigned int i = 0; i < this->InputBuffer->size(); i++) {
//                delete this->InputBuffer->at(i);
//            }
//            this->InputBuffer->clear();
//            FreeChar = InputNewline(scn->GetDispPosition(), ScnWidth, CharWidth);
        } else if (key == KEYCODE_BACKTRACE) {
            Line *line_ptr = this->input_buffer_->back();
            if (line_ptr->LineText.length() == 0)
            {
                if (this->input_buffer_->size() >= 2)
                {
                    delete line_ptr;
                    this->input_buffer_->pop_back();
                    line_ptr = this->input_buffer_->back();
                    FreeChar = 0;
                }
            }
            int len = line_ptr->LineText.length(), dx = 0, dy = 0;
            if (len > 0) {
                line_ptr->LineText.erase(--len, 1);
            }
            if (scn_->GetDispPosition().y <= 0 && line_ptr->PrintPosition.y > 0) {
                Point ptmp;
                ptmp.x = ptmp.y = 0;
                FreeChar = InputNewline(ptmp, screen_width, char_width);
                line_ptr = this->input_buffer_->back();
                dx = dy = 0;
            } else {
                dx = line_ptr->PrintPosition.x + len * char_width;
                dy = line_ptr->PrintPosition.y;
                FreeChar++;
            }
            scn_->Display(" ", dx, dy);
            scn_->SetDispPosition(dx, dy);
        } else if (isprint(key) == 0) {
            continue ;
        } else {
            if (FreeChar == 0)
            {
                scn_->NewLine();
                FreeChar = InputNewline(scn_->GetDispPosition(),
                                        screen_width,
                                        char_width);
            }
            this->input_buffer_->back()->LineText.append(1, key);
            FreeChar--;
            scn_->Display((char)key);
        }
    }
    string buf;
    for (auto & it : *this->input_buffer_) {
        buf.append(it->LineText);
        delete it;
    }
    delete this->input_buffer_;
    scn_->NewLine();
    return (unsigned char *)strdup(buf.c_str());
}

unsigned char* BBVM::GetString() {
    return GetKeyString();
}

unsigned int BBVM::GetInteger()
{
    return atoi((char *)GetKeyString());
}

float BBVM::GetFloat()
{
    return atof((char *)GetKeyString());
}