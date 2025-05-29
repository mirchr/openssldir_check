#######################################################################################
# openssldir_check.ps1
# Descryption: Wrapper script to find OpenSSL libraries and call openssldir_check.exe
# Author: Rich Mirch @0xm1rch
# Project: https://github.com/mirchr/openssldir_check
#######################################################################################

# change to the path where openssldir_check_*.exe binaries are installed
cd /code

# Use libcrypto-1*.dll for OpenSSL 1.1+
Get-ChildItem -Path c:\ -Include libeay32.dll -Recurse -ErrorAction SilentlyContinue | ForEach-Object -Process {

    $f = $_.Fullname;
    Write-Host -ForegroundColor Yellow -NoNewline "Checking Library: ";
    Write-Host $f;

    .\openssldir_check_x64.exe $f
    # ERROR_BAD_EXE_FORMAT = 193. Assume the library is 32-bit.
    if($LastExitCode -eq 193)
    {
        Write-Debug "64-bit check failed - trying 32-bit"
        .\openssldir_check_x86.exe $f
    }
    Write-Host
}
