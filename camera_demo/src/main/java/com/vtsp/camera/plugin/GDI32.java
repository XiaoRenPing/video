package com.vtsp.camera.plugin;

import com.sun.jna.Native;
import com.sun.jna.examples.win32.W32API;

public interface GDI32 extends W32API
{
    GDI32 INSTANCE = (GDI32) Native.loadLibrary("gdi32", GDI32.class, DEFAULT_OPTIONS);

    public static final int TRANSPARENT = 1;

    int SetBkMode(HDC hdc, int i);

    HANDLE CreateSolidBrush(int icolor);
}