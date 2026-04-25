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
* TODO: Code-sign released binaries (evaluate Azure Trusted Signing vs. EV cert from a cloud signing service)

## Download
The binaries can be downloaded directly from the latest GitHub Actions https://github.com/mirchr/openssldir_check/actions build. Note: This is a temporary solution. Long term the binaries will be available directly from Github releases.

## Usage
> [!WARNING]
> Do not use this on untrusted paths. The utility attempts to load the library and call the OpenSSL function to determine the version and OPENSSLDIR path.

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
| [CVE-2026-3991](https://nvd.nist.gov/vuln/detail/CVE-2026-3991) | Symantec/Broadcom DLP Agent | https://labs.infoguard.ch/advisories/cve-2026-3991_symantec-dlp-agent_local-privilege-escalation/ | [Manuel Feifel](https://labs.infoguard.ch/) (InfoGuard Labs) |
| [CVE-2025-53841](https://nvd.nist.gov/vuln/detail/CVE-2025-53841) | Akamai Guardicore Platform Agent | https://www.akamai.com/blog/security/2025/dec/advisory-cve-2025-53841-guardicore-local-privilege-escalation | [SECURITEAM / Beyond Security SSD](https://securiteam.io/2025/09/08/privilege-escalation-akamai-guardicore-platform-agent/) |
| [CVE-2025-47161](https://nvd.nist.gov/vuln/detail/CVE-2025-47161) | Microsoft Defender for Endpoint (MDE) | https://msrc.microsoft.com/update-guide/vulnerability/CVE-2025-47161<br>https://www.stratascale.com/resource/cve-2025-47161-osquery-defender-linux/ | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE-2025-35471](https://nvd.nist.gov/vuln/detail/CVE-2025-35471) | conda-forge | https://github.com/conda-forge/openssl-feedstock/issues/201 | [Will Dormann](https://github.com/wdormann) |
| [CVE-2025-2272](https://nvd.nist.gov/vuln/detail/CVE-2025-2272) | Forcepoint Endpoint DLP | https://www.triskelelabs.com/blog/cve-2025-2272-forcepoint-endpoint-dlp-privilege-escalation | [Triskele Labs](https://www.triskelelabs.com/) |
| [CVE-2024-6975](https://nvd.nist.gov/vuln/detail/CVE-2024-6975) | Cato Networks SDP Client | https://blog.amberwolf.com/blog/2024/july/cve-2024-6975-cato-client-local-privilege-escalation-via-openssl-configuration-file/ | [AmberWolf](https://blog.amberwolf.com/) |
| [CVE-2024-0394](https://nvd.nist.gov/vuln/detail/CVE-2024-0394) | Rapid7 Minerva Armor | https://www.rapid7.com/blog/post/2024/04/03/cve-2024-0394-rapid7-minerva-armor-privilege-escalation-fixed/ | [Will Dormann](https://github.com/wdormann) |
| [CVE-2023-41840](https://nvd.nist.gov/vuln/detail/CVE-2023-41840) | FortiClient Windows | https://www.fortiguard.com/psirt/FG-IR-23-274 | Undisclosed |
| [CVE-2023-40596](https://nvd.nist.gov/vuln/detail/CVE-2023-40596) | Splunk Enterprise for Windows | https://advisory.splunk.com/advisories/SVD-2023-0805 | Undisclosed |
| [CVE-2022-32223](https://nvd.nist.gov/vuln/detail/CVE-2022-32223) | Node.js / npm CLI | https://www.aquasec.com/blog/cve-2022-32223-dll-hijacking/ | [Yakir Kadkoda](https://www.aquasec.com/) (Aqua Security) |
| [CVE-2022-26872](https://nvd.nist.gov/vuln/detail/CVE-2022-26872) | Tychon Endpoint | https://www.kb.cert.org/vuls/id/730007 | [Will Dormann](https://github.com/wdormann) |
| [CVE-2022-0166](https://nvd.nist.gov/vuln/detail/CVE-2022-0166) | McAfee Agent | https://www.kb.cert.org/vuls/id/287178 | [Will Dormann](https://github.com/wdormann) |
| [CVE-2021-2356](https://nvd.nist.gov/vuln/detail/CVE-2021-2356) | MySQL for Windows | https://www.kb.cert.org/vuls/id/567764 | [Will Dormann](https://github.com/wdormann) |
| [CVE-2021-2307](https://nvd.nist.gov/vuln/detail/CVE-2021-2307) | OPENSSLDIR class research paper | https://www.exploit-db.com/docs/english/50747-openssldir-privilege-escalation-cve-2021-2307---paper.pdf | Marlon Petry |
| [CVE-2020-10143](https://nvd.nist.gov/vuln/detail/CVE-2020-10143) | Macrium Reflect | https://www.kb.cert.org/vuls/id/760767 | [Will Dormann](https://github.com/wdormann) |
| [CVE-2019-12572](https://nvd.nist.gov/vuln/detail/CVE-2019-12572) | PIA VPN | https://blog.mirch.io/2019/06/10/cve-2019-12572-pia-windows-privilege-escalation-malicious-openssl-engine/ | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE-2019-10211](https://nvd.nist.gov/vuln/detail/CVE-2019-10211) | PostgreSQL | https://www.postgresql.org/support/security/CVE-2019-10211/ | [Daniel Gustafsson](https://github.com/danielgustafsson) |
| [CVE-2019-5443](https://nvd.nist.gov/vuln/detail/CVE-2019-5443) | curl | https://curl.se/docs/CVE-2019-5443.html<br>https://daniel.haxx.se/blog/2019/06/24/openssl-engine-code-injection-in-curl/ | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE-2019-2390](https://nvd.nist.gov/vuln/detail/CVE-2019-2390) | mongoDB | https://jira.mongodb.org/browse/SERVER-42233 | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE-2019-1552](https://nvd.nist.gov/vuln/detail/CVE-2019-1552) | OpenSSL | https://www.openssl.org/news/secadv/20190730.txt | [Rich Mirch](https://x.com/0xm1rch) |
| N/A | stunnel | [https://www.openssl.org/news/secadv/20190730.txt](https://www.stunnel.org/pipermail/stunnel-announce/2019-June/000145.html) | [Rich Mirch](https://x.com/0xm1rch) |


