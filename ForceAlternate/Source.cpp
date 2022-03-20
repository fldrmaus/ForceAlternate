static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (lParam != NULL)
    {
        bool supress = false;
        int keyCode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        if (((keyCode == 0x43) || (keyCode == 0x58))) {
            printf("lastKey: %i, keyCode: %i\n", lastKey, keyCode);
            if (wParam == WM_KEYDOWN && (keyCode == lastKey))
            {
                supress = true;
                printf("supressing key\n");
            }
            if (wParam == WM_KEYDOWN) {
                lastKey = keyCode;
            }
            if (supress) return 1;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}