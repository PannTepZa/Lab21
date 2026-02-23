#define UNICODE
#include <windows.h>
#include <string>

using namespace std;


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    static HWND textfield; 
	static HWND input1, input2;
	HINSTANCE hInst = GetModuleHandle(NULL);;
	static HWND btnAdd,btnMin,btnMul,btnDiv;

    switch(Message) {

        case WM_CREATE:
            textfield = CreateWindow(
                TEXT("STATIC"),
                TEXT("Please input two numbers"),
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                12, 12, 210, 25,
                hwnd,
                NULL,
                NULL,
                NULL
            );
			input1 = CreateWindow(L"EDIT", L"",
    							WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
    							55, 50, 130, 25,
    							hwnd, NULL, hInst, NULL);

			input2 = CreateWindow(L"EDIT", L"",
    							WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
    							55, 85, 130, 25,
    							hwnd, NULL, hInst, NULL);
			btnAdd = CreateWindow(L"BUTTON",L"+",
        						WS_VISIBLE | WS_CHILD,
        						23, 125, 40, 30,     
        						hwnd,
        						(HMENU)1,            
        						hInst,
        						NULL);
			btnMin = CreateWindow(L"BUTTON",L"-",
        						WS_VISIBLE | WS_CHILD,
        						73, 125, 40, 30,     
        						hwnd,
        						(HMENU)2,            
        						hInst,
        						NULL);
			btnMul = CreateWindow(L"BUTTON",L"*",
        						WS_VISIBLE | WS_CHILD,
        						123, 125, 40, 30,     
        						hwnd,
        						(HMENU)3,            
        						hInst,
        						NULL);
			btnDiv = CreateWindow(L"BUTTON",L"/",
        						WS_VISIBLE | WS_CHILD,
        						173, 125, 40, 30,     
        						hwnd,
        						(HMENU)4,            
        						hInst,
        						NULL);
        break; 

		case WM_COMMAND:
				WCHAR inp1[50], inp2[50], resultText[50];
				float a,b,result;
				GetWindowText(input1, inp1, 50);
            	GetWindowText(input2, inp2, 50);
				a = _wtof(inp1);
				b = _wtof(inp2);

				switch (LOWORD(wParam)){
					case 1:
					::MessageBeep(MB_ICONERROR);
					result = a + b;
					swprintf(resultText, 50, L"%f", result);
					::MessageBox(hwnd, resultText, L"Result", MB_OK);
					break;

					case 2:
					::MessageBeep(MB_ICONERROR);
					result = a - b;
					swprintf(resultText, 50, L"%f", result);
					::MessageBox(hwnd, resultText, L"Result", MB_OK);
					break;

					case 3:
					::MessageBeep(MB_ICONERROR);
					result = a * b;
					swprintf(resultText, 50, L"%f", result);
					::MessageBox(hwnd, resultText, L"Result", MB_OK);
					break;

					case 4:
					::MessageBeep(MB_ICONERROR);
					result = a / b;
					swprintf(resultText, 50, L"%f", result);
					::MessageBox(hwnd, resultText, L"Result", MB_OK);
					break;
				}
				
		break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,200,120));
	wc.lpszClassName = L"WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,L"WindowClass",L"My Calculator",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	if(hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
