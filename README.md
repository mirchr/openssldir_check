# openssldir_check
![Build Status](https://github.com/mirchr/openssldir_check/actions/workflows/msbuild.yml/badge.svg)

A Windows utility written in C++ to check for potential insecure paths used by the OPENSSLDIR build parameter in OpenSSL libraries. Applications that bundle OpenSSL libraries may have OPENSSLDIR set to a path that could be writable from a low privileged user account. Depending on how the application is written, it may automatically load OPENSSLDIR/openssl.cnf during startup or other specific conditions.

The openssl.cnf configuration file can be leveraged to load a malicious OpenSSL Engine library resulting in the execution of arbitrary code with the authority of the account running the vulnerable application. For a detailed example of how I obtained SYSTEM with the Private Internet Access Desktop VPN client, read https://blog.mirch.io/2019/06/10/cve-2019-12572-pia-windows-privilege-escalation-malicious-openssl-engine/. Information on how this works is described at https://wiki.openssl.org/index.php/Library_Initialization.

Additional functionality will be added as time permits. Here is functionality I may implement.
* Check permissions on all folders listed in the OPENSSLDIR path
* Check permissions of OPENSSLDIR/openssl.cnf
* Check permissions of OPENSSL_ENGINES_DIR for OpenSSL 1.1+
* Create option to search the file system for OpenSSL libraries
* Logging
* XMl/json output

## Download
The binaries can be downloaded directly from the CI [build server](https://ci.appveyor.com/project/mirchr/openssldir-check?branch=master). Click on the desired platform and then select Artifacts. Note: This is a temporary solution. Long term the binaries will be available directly from Github.

## Usage
Note: Do not use this on untrusted paths. The utility attempts to load the library and call the OpenSSL function to determine the version and OPENSSLDIR path.

> [!NOTE]
> Use `openssldir_check_x86` for 32-bit libraries, and `openssldir_check_x64` for 64-bit libraries.
```
# OpenSSL v1.1+
openssldir_check <path/to/libcrypto-<version>.dll>

# OpenSSL < v1.1
openssldir_check <path/to/libeay32.dll>
```

## Example
![Usage](https://mirchhome.files.wordpress.com/2019/06/openssldir_check-usage.png)

## Known OPENSSLDIR Vulnerabilities 
| CVE | Application | References | Credit |
|----------|----------|----------|----------|
| [CVE-2019-1552](https://nvd.nist.gov/vuln/detail/CVE-2019-1552)   | OpenSSL  | https://www.openssl.org/news/secadv/20190730.txt   | [Rich Mirch](https://x.com/0xm1rch) |
