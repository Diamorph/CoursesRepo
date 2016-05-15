#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "scientist.h"


const char g_szClassName[] = "myWindowClass";


#define ID_LABEL 131
#define ID_LB    132

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 230,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    HINSTANCE hInstance = GetModuleHandle(NULL);
	static HWND hLabel, hStaticKey, hStaticValue, hWndList;
	static scientist_t scientist1 = NULL, scientist2 = NULL, scientist3 = NULL;
	static char buf[100];
	switch (msg)
	{
	    case WM_CREATE:
	{
		hLabel = CreateWindowEx(
			0,
			"STATIC",
            "Scientists:",
			WS_CHILD | WS_VISIBLE,
			60, 10, 80, 20,
			hwnd,
			(HMENU)131,
            hInstance,
            NULL
			);
		hStaticKey = CreateWindowEx(0,
            "STATIC",
			"Surname",
			WS_CHILD | WS_VISIBLE,
			220, 40, 170, 23,
			hwnd,
			(HMENU)1,
			hInstance,
			NULL);
		hStaticValue = CreateWindowEx(0,
			"STATIC",
			"Full Information",
			WS_CHILD | WS_VISIBLE,
			220, 70, 170, 23,
			hwnd,
			(HMENU)2,
			hInstance,
			NULL);
		hWndList = CreateWindowW(
			L"listbox",
			L"Update timer",
			WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | WS_BORDER | LBS_NOTIFY,
			10, 40, 185, 125,
			hwnd, (HMENU)ID_LB, NULL, NULL
			);

		scientist1 = scientist_new("Marie", "Curie", 1867);
		scientist_insert(scientist1, hWndList);

		scientist2 = scientist_new("Albert", "Einstein", 1879);
		scientist_insert(scientist2, hWndList);

		scientist3 = scientist_new("Ronald", "Fisher", 1890);
		scientist_insert(scientist3, hWndList);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
            case ID_LB:  // It's our listbox, check the notification code
			switch (HIWORD(wParam))
			{
                case LBN_SELCHANGE:  // Selection changed, do stuff here.
			{
                    HWND hLabel = GetDlgItem(hwnd, ID_LABEL);
                    HWND control = GetDlgItem(hwnd, ID_LB);

                    char text[256];
                    // get the number of items in the box.
                    int count = SendMessage(control, LB_GETCOUNT, 0, 0);
                    int iSelected = -1;
                    // go through the items and find the first selected one
                    for (int i = 0; i < count; i++)
                    {
                        // check if this item is selected or not..
					if (SendMessage(control, LB_GETSEL, i, 0) > 0)
					{
					    // yes, we only want the first selected so break.
						iSelected = i;
					}
					// get the text of the selected item
					if (iSelected != -1){
                        char key[100] = "";
						SendMessage(control, LB_GETTEXT, (WPARAM)iSelected, (LPARAM)key);
						SetWindowText(hStaticKey, key);
						char * value = (char*)SendMessage(control, LB_GETITEMDATA, (WPARAM)iSelected, 0);
						SetWindowText(hStaticValue, value);
					}
				}
			}
			break;
			}
			break;
		}
	}
	break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
