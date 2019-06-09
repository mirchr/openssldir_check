#######################################################################################
# openssldir_check.ps1
# Descryption: Wrapper script to find OpenSSL libraries and call openssldir_check.exe
# Author: Rich Mirch @0xm1rch
# Project: https://github.com/mirchr/openssldir_check
#######################################################################################

# change to the path where openssldir_check.exe is installed
cd /code

# Use libcrypt-1*.dll for OpenSSL 1.1+
Get-ChildItem -path c:\ -Include libeay32.dll -recurse -ErrorAction SilentlyContinue | ForEach-Object -Process {

    $f = $_.Fullname;
    Write-Host -ForegroundColor Yellow -NoNewline "Checking Library: ";
    Write-host $f;

    .\openssldir_check.exe $f
    # XXX: check return code and execute 32-bit version if bad image
    #openssldir_check32.exe $f
    Write-host
}
