copy 3 folders in c drive 
type notepad $PROFILE 
add
```function run {
    param (
        [string[]]$files,  # Accept multiple C++ files
        [string]$exe = ""  # Optional executable name
    )

    # If no exe name is given, use the first file's name
    if ($exe -eq "") {
        $exe = [System.IO.Path]::GetFileNameWithoutExtension($files[0]) + ".exe"
    } else {
        $exe += ".exe"  # Ensure .exe extension
    }

    # Compile all given C++ files
    Write-Host "Compiling: $($files -join ', ') → Output: $exe" -ForegroundColor Cyan
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
}```

type ". $PROFILE"

type run <filename.cpp> -exe filename.exe 