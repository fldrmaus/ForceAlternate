#include <Windows.h>
#include <stdio.h>
int lastKey;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (lParam != NULL)
    {
        int keyCode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        if (((keyCode == 0x43) || (keyCode == 0x58))) {
            printf("lastKey: %i, keyCode: %i\n", lastKey, keyCode);
            if (wParam == WM_KEYDOWN) {
                bool supress = false;
                if (keyCode == lastKey)
                {
                    supress = true;
                    printf("supressing key\n");
                }
                lastKey = keyCode;
                if (supress) return 1;
            }
        }
    }
    
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    MessageBoxW(NULL, L"Forcing full alt on C and X", L"", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
    UnhookWindowsHookEx(hHook);
    return 0;
}