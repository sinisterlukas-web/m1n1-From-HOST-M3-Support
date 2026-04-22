# dtb_generator.ps1 - Compiles M4 hardware maps on Windows
Write-Host "--- M4 DTB Generator (Windows Edition) ---" -ForegroundColor Cyan

$srcFile = "src/dt/m4.dts"
$destFile = "dtbucket/m4.dtb"

if (Test-Path $srcFile) {
    # Check if dtc is available (usually via MSYS2 or WSL)
    if (Get-Command dtc -ErrorAction SilentlyContinue) {
        Write-Host "Compiling $srcFile..."
        dtc -I dts -O dtb -o $destFile $srcFile
        Write-Host "Success! Check the dtbucket." -ForegroundColor Green
    } else {
        Write-Host "Error: 'dtc' not found. Please install via MSYS2 or WSL2." -ForegroundColor Red
    }
} else {
    Write-Host "Error: $srcFile not found." -ForegroundColor Red
}
