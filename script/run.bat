@REM rem 自动执行bin目录下的exe文件（如果有多个exe文件，会自动执行最后找到的exe文件）
@REM @echo off
@REM pushd .

@REM if not exist bin (
@REM     echo "bin directory not exists!"
@REM     popd
@REM     exit(1)
@REM )

@REM set EXE_FILE=""
@REM for /r ./bin %%f in (*.exe) do (
@REM     set EXE_FILE=%%f
@REM )
@REM echo %EXE_FILE%

@REM if EXE_FILE!=="" (
@REM     echo "exe file not exists in bin directory!"
@REM     popd
@REM     exit(1)
@REM )

@REM %EXE_FILE%

@REM popd
rem 运行 bin 目录下的测试可执行文件，优先选择 Experiment1-main.exe；否则回退到最后一个 .exe
@echo off
setlocal enabledelayedexpansion

rem 将工作目录切到仓库根（脚本所在目录的上一级）
pushd "%~dp0.."

if not exist .\bin (
    echo [run.bat] bin directory not exists!
    popd
    exit /b 1
)

set "EXE_FILE="

rem 优先运行当前项目生成的测试可执行文件
if exist .\bin\Experiment1-main.exe (
    set "EXE_FILE=.\bin\Experiment1-main.exe"
) else (
    rem 回退：在 bin 下查找任意 .exe，取最后一个
    for %%f in (".\bin\*.exe") do (
        set "EXE_FILE=%%~f"
    )
)

if not defined EXE_FILE (
    echo [run.bat] exe file not exists in bin directory!
    popd
    exit /b 1
)

echo [run.bat] Running: %EXE_FILE% %*
"%EXE_FILE%" %*

popd
endlocal