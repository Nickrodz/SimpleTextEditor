#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#define OPEN_FILE 1
#define SAVE_FILE 2
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
//https://www.youtube.com/@ThePentamollisProject  <-- youtube tutorial
void AddControls(HWND);
HWND hEdit;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc)){
        return -1;
    } else {

     CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100,100,500,500,NULL,NULL,NULL,NULL);
    }

    MSG msg = {0};
    while(GetMessage(&msg,NULL,NULL,NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void display_file(char* path){

    FILE *file;
    file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
   int _size = ftell(file);
   rewind(file);
   char *data = new char[_size+1];
   fread(data, _size, 1, file);
   data[_size] = '\0';
    
   SetWindowText(hEdit, data);
   fclose(file);

}


void open_file(HWND hWnd){
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;


    GetOpenFileName(&ofn);
    display_file(ofn.lpstrFile);
}


void write_file(char* path){
    FILE *file;
    file = fopen(path, "w");
    
    int _size = GetWindowTextLength(hEdit);
    char *data = new char[_size+1];
    GetWindowText(hEdit, data, _size+1);

    fwrite(data, _size+1, 1, file);
    fclose(file);

}

void save_file(HWND hWnd){
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;


    GetSaveFileName(&ofn);
    
    write_file(ofn.lpstrFile);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

    switch (msg)
    {
        case WM_COMMAND:
           switch(wp){
                case OPEN_FILE:
                open_file(hWnd);
                break;
                case SAVE_FILE:
                save_file(hWnd);
                break;
            }
        break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd,msg,wp,lp);
    }

}



void AddControls(HWND hWnd){
   
     CreateWindowW(L"Button", L"Open File", WS_VISIBLE | WS_CHILD, 90, 50, 98, 38 , hWnd, (HMENU)OPEN_FILE, NULL, NULL);

     CreateWindowW(L"Button", L"Save File", WS_VISIBLE | WS_CHILD, 200, 50, 98, 38 , hWnd, (HMENU)SAVE_FILE, NULL, NULL);

    hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL, 75, 100, 300, 300 , hWnd, NULL, NULL, NULL);
   
}



