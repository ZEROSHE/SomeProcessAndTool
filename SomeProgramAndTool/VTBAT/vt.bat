@echo on
::this is impotant
setlocal enabledelayedexpansion
SET str1="tag p:3+ ls:2019-06-12T
SET str2=:00:00+ ls:2019-06-12T
SET str3=:00:00-"
SET VAR=1

REM if %VAR% == 1 (
REM echo %VAR% )
REM SET VAR=0
REM echo %VAR%


for %%i in (00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23) do (
for %%j in (01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23) do (
set HTTP_PROXY=xxxxx
::D:\\vtcli\\Windows64\\vt.exe search %str1%%%i%str2%%%j%str3% -I -n 1
set /a a=%%i
set /a b=%%j
set /a c=!b!-!a!
if !c!==1 ^
D:\\vtcli\\Windows64\\vt.exe search %str1%%%i%str2%%%j%str3% -I -n 2
))

::cant download 23:00:00-00:00:00
::echo %str1%%a%%str2%%b%%str3%
::D:\\vtcli\\Windows64\\vt.exe search %str1%%i%%str2%%j%%str3% -I -n 2
::%str1%%%i%str2%%%j%str3%