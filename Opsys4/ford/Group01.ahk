Run, ford.exe
WinWait, FORD
WinActivate, FORD
MouseMove, 237, 145
Sleep, 1000
WinGet, activeWindow, ID, A ; Get the ID of the active window

SetWorkingDir %A_ScriptDir%
FileCreateDir, %A_ScriptDir%\Group01

; Activate the window
WinActivate, ahk_id %activeWindow%

Sleep, 1000

WinGetTitle, title, ahk_id %activeWindow%
ControlGet, OutputVar, Hwnd,, ThunderRT5TextBox5, %title%

startserialnumber:=000000

endserialnumber:=000008

loopcounter:=endserialnumber - startserialnumber + 1

; Send some data to the active window (adjust as needed)

WinSet, AlwaysOnTop,, %title% 
Loop, %loopcounter%
{
    WinActivate, %title%
    Sleep, 200
    WinActivate, %title%

    a:=Format("{:06d}", startserialnumber)

    WinActivate, %title%
    Sleep, 200
    WinActivate, %title%

    SendInput %a%

    WinActivate, %title%
    Sleep, 200
    WinActivate, %title%

    SendEvent {Click 237 145}

    WinActivate, %title%
    Sleep, 200
    WinActivate, %title%

    Run, screenshot-cmd.exe -wh %OutputVar% -o Group01\%a%.png

    WinActivate, %title%
    Sleep, 600
    WinActivate, %title%

    startserialnumber+=1

    WinActivate, %title%
    Sleep, 200
    WinActivate, %title%

    SendEvent {Click 270 98}
    WinActivate, %title%
}

; Move the mouse to coordinates (237, 145) TO Button 5 and click
SendEvent {Click 38 89}


