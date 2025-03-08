# OpenGL C++ Compilation and Execution with PowerShell

This guide provides a PowerShell function to easily compile and run OpenGL programs using **FreeGLUT**, **GLEW**, and **GLFW** on Windows.

---

## 📂 Setup Required Folders
Ensure the following folders exist in `C:\`:
- `C:\glew-2.1.0`
- `C:\glfw-3.4.bin.WIN64`
- `C:\freeglut`

These contain necessary OpenGL libraries.

---

## 📝 Modify PowerShell Profile
1. Open PowerShell and type:
   ```powershell
   notepad $PROFILE
   ```
   If the file does not exist, Notepad will prompt you to create it.

2. Add the following function:
   ```powershell
   function run {
       param (
           [string[]]$files,  # Accept multiple C++ files
           [string]$exe = ""  # Optional executable name
       )

       # If no executable name is provided, use the first file's name
       if ($exe -eq "") {
           $exe = [System.IO.Path]::GetFileNameWithoutExtension($files[0]) + ".exe"
       } else {
           $exe += ".exe"  # Ensure .exe extension
       }

       # Compile all given C++ files
       Write-Host "🔄 Compiling: $($files -join ', ') → Output: $exe" -ForegroundColor Cyan
       $compileOutput = g++ -g `
           -I C:\glew-2.1.0\include `
           -I C:\glfw-3.4.bin.WIN64\include `
           -I C:\freeglut\include `
           $files -o $exe `
           -L C:\glew-2.1.0\lib\Release\x64 `
           -L C:\glfw-3.4.bin.WIN64\lib-mingw-w64 `
           -L C:\freeglut\lib\x64 `
           -lglew32 -lglfw3dll -lfreeglut -lopengl32 -lglu32 2>&1

       # Check if compilation was successful
       if ($?) {
           Write-Host "✅ Compilation successful. Running $exe..." -ForegroundColor Green
           
           # Ensure executable exists before running
           if (Test-Path ".\$exe") {
               & ".\$exe"
           } else {
               Write-Host "❌ Executable not found. Compilation may have failed." -ForegroundColor Red
           }
       } else {
           Write-Host "❌ Compilation failed. Error details below:" -ForegroundColor Red
           Write-Host $compileOutput
       }
   }
   ```

3. Save and close Notepad.

---

## 🔄 Apply Changes
Run the following command in PowerShell:
```powershell
. $PROFILE
```
This reloads the updated profile without restarting the terminal.

---

## 🚀 Usage

### ✅ Compile and Run a Single File
```powershell
run opengl1.cpp
```
This will create and execute `opengl1.exe`.

### ✅ Specify a Custom Executable Name
```powershell
run opengl1.cpp -exe myprogram
```
This will create and execute `myprogram.exe`.

### ✅ Compile Multiple C++ Files
```powershell
run main.cpp helper.cpp -exe myapp
```

---

## 🛠 Troubleshooting

### ⚠ PowerShell Script Execution Policy Error?
If you get an error about running scripts, enable script execution by running:
```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### ⚠ Missing Dependencies?
Ensure `g++` (MinGW) is installed and accessible via the system PATH.

---

Now you can compile and run OpenGL C++ programs with a single command! 🚀

