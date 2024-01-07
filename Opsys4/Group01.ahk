; Run ford.exe
Run, ford.exe
WinWait, ford ; Wait for the window to appear
WinGet, activeWindow, ID, A ; Get the ID of the active window

; Activate the window
WinActivate, ahk_id %activeWindow%

; Wait for the window to be fully activated (adjust the sleep duration as needed)
Sleep, 1000

WinGetActiveTitle, Title

; Get the position of the active window
WinGetPos, x, y, width, height, A

; Send some data to the active window (adjust as needed)
Loop, 6
{
    Send %A_Index%	
}
m:=Width/2
n:=Height/2
; Move the mouse to coordinates (237, 145) and click
MouseMove, 237, 145
Click
Sleep, 2000
RunWait, screenshot-cmd.exe -wh %activeWindow% -rc 110 70 220 112
Process, Close, %activeWindow%
; You can add additional logic or actions after taking the screenshot

WinGetActiveStats, Title, Width, Height, X, Y
MsgBox, The active window %Title% is %Width% wide , %Height% tall , and positioned at %X% ,%Y%.
