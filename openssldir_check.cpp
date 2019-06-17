/* openssldir_check - Windows utility to check for potential insecure OPENSSLDIR paths built into OpenSSL libraries
*  Author: Rich Mirch @0xm1rch
*  Project: https://github.com/mirchr/openssldir_check
*/


#include "pch.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>

#define SSLEAY_VERSION 0
#define SSLEAY_DIR 5

using namespace std;

// https://www.openssl.org/docs/man1.0.2/man3/SSLeay_version.html
// https://www.openssl.org/docs/man1.1.0/man3/OpenSSL_version.html
#ifdef _WIN64
	typedef char*(__stdcall *f_SSLeay_version)(int);
	typedef char*(__stdcall *f_OpenSSL_version)(int);
	const unsigned int bits = 64;
#else
	typedef char*(__cdecl *f_SSLeay_version)(int);
	typedef char*(__cdecl *f_OpenSSL_version)(int);
	const unsigned int bits = 32;
#endif


int wmain(int argc, wchar_t **argv)
{
	int USE_SSLEAY = 0;

	cout << "openssldir_check v1.0 by 0xm1rch\n\n";

	if (argv[1] == NULL)
	{
		wcerr << "\nUsage: openssldir_check <path\\to\\libeay32.dll>          OpenSSL < 1.1";
		wcerr << "\n   or  openssldir_check <path\\to\\libcrypto-version.dll> OpenSSL >= 1.1+";
		wcerr << "\n\nWARNING: Do not use an untrusted path!\n";
		exit(EXIT_FAILURE);
	}

	wchar_t filename[MAX_PATH];
	wchar_t *has_slash = NULL;

	// Extract the filename and store it in filename.
	// Just copy the argument if a \ is not found
	has_slash = wcschr(argv[1], '\\');
	if (has_slash == NULL)
	{
		wcsncpy_s(filename, wcsnlen_s(argv[1], MAX_PATH) + 1, argv[1], MAX_PATH);
	}
	else
	{
		// Copy the filename starting at the slash
		wcsncpy_s(filename, wcsnlen_s(argv[1], MAX_PATH) + 1, wcsrchr(argv[1], '\\') + 1, MAX_PATH);
	}

	// Compare filename with libeay32.dll. If not matched, assume libcrypto* / OpenSSL 1.1+
	if ((wcsncmp(L"libeay32.dll", filename, wcslen(L"libeay32.dll"))) == 0)
	{
		USE_SSLEAY = 1;
	}

	HINSTANCE hLibModule = LoadLibrary(argv[1]);

	if (!hLibModule)
	{
		if (GetLastError() == ERROR_BAD_EXE_FORMAT)
		{
			wcout << "Error: Library is not a " << bits << "-bit library" << endl;
			return ERROR_BAD_EXE_FORMAT;
		}
		wcerr << "Could not load the dynamic library " << argv[1] << " Error=" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	if (USE_SSLEAY)
	{
		f_SSLeay_version SSLeay_version = (f_SSLeay_version)GetProcAddress(hLibModule, "SSLeay_version");

		if (!SSLeay_version)
		{
			cerr << "SSLeay_version() not found" << endl;
			return EXIT_FAILURE;
		}

		cout << "SSLeay_version() returned " << SSLeay_version(0) << endl;
		cout << "SSLeay_version() returned " << SSLeay_version(5) << endl;
	}
	else
	{
		// OpenSSL 1.1+
		f_OpenSSL_version OpenSSL_version = (f_OpenSSL_version)GetProcAddress(hLibModule, "OpenSSL_version");

		if (!OpenSSL_version)
		{
			cerr << "OpenSSL_version() not found" << endl;
			return EXIT_FAILURE;
		}
		cout << "OpenSSL_version() returned " << OpenSSL_version(0) << endl;
		cout << "OpenSSL_version() returned " << OpenSSL_version(4) << endl;
	}

	bool retval = FreeLibrary(hLibModule);
	if (!retval)
	{
		wcerr << "Error unloading library " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
