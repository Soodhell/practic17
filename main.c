#include <windows.h>

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);
#define ID_MY_BUTTON_ONE 1
#define ID_MY_BUTTON_TWO 2
#define ID_MY_BUTTON_TREE 3

char buf[256]="";
HINSTANCE h;

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int ss) {
    WNDCLASS wc;
    wc.style=0;
    wc.lpfnWndProc=MainWinProc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    wc.hInstance=hInst;
    wc.hIcon=NULL;
    wc.hCursor=NULL;
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+2);
    wc.lpszMenuName="Ex4_Menu";
    wc.lpszClassName="Example 4 MainWnd Class";
    if (!RegisterClass(&wc)) return FALSE;

    HWND hMainWnd=CreateWindow("Example 4 MainWnd Class","EXAMPLE 4",WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);
    if (!hMainWnd) return FALSE;
    ShowWindow(hMainWnd,ss);
    UpdateWindow(hMainWnd);

    MSG msg;
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

BOOL CALLBACK DlgFuncModal(HWND hw, UINT msg, WPARAM wp, LPARAM lp){
    switch (msg) {
        case WM_CREATE:
            return TRUE;
        case WM_COMMAND:
            if (LOWORD(wp) == 2) EndDialog(hw, 0);

    }
    return FALSE;
}

LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("button", "Click me", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         50, 100, 100, 50, hw, (HMENU) ID_MY_BUTTON_ONE, NULL, NULL);
            CreateWindow("button", "Click me", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         165, 100, 100, 50, hw, (HMENU) ID_MY_BUTTON_TWO, NULL, NULL);
            CreateWindow("button", "Click me", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         280, 100, 100, 50, hw, (HMENU) ID_MY_BUTTON_TREE, NULL, NULL);
            return 0;

        case WM_COMMAND:

            if (LOWORD(wp) == 6)
                PostQuitMessage(0);
            else {
                if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MY_BUTTON_ONE))
                    DialogBox(h, "RomanDialogBox", hw, DlgFuncModal);
                if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MY_BUTTON_TWO)){
                    HWND hwndGoto = NULL;
                    hwndGoto = CreateDialog(h, "RomanDialogBox", hw, DlgFuncModal);
                    ShowWindow(hwndGoto, SW_SHOW);
                }
                if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MY_BUTTON_TREE)){
                    HWND hwndGoto = NULL;
                    for (int i = 0; i < 4; ++i) {
                        hwndGoto = CreateDialog(h, "RomanDialogBox", hw, DlgFuncModal);
                        ShowWindow(hwndGoto, SW_SHOW);
                    }
                }

                return 0;
            }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}