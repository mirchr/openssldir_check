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
> Use `openssldir_check_x86.exe` for 32-bit libraries, and `openssldir_check_x64.exe` for 64-bit libraries.
```
# OpenSSL v1.1+
openssldir_check_x64.exe <path/to/libcrypto-<version>.dll>

# OpenSSL < v1.1
openssldir_check_x86.exe <path/to/libeay32.dll>
```

## Example
TODO: Add screenshot of example usage

## Known OPENSSLDIR Vulnerabilities 
| CVE | Application | References | Credit |
|----------|----------|----------|----------|
| [CVE&#8209;2026&#8209;34054](https://nvd.nist.gov/vuln/detail/CVE-2026-34054) | Microsoft vcpkg (OpenSSL Windows build) | [GHSA-p322-v6vw-vrq9](https://github.com/microsoft/vcpkg/security/advisories/GHSA-p322-v6vw-vrq9) | Xavier DANEST (via [Trend Micro ZDI](https://www.zerodayinitiative.com/)) |
| [CVE&#8209;2026&#8209;6482](https://nvd.nist.gov/vuln/detail/CVE-2026-6482) | Rapid7 Insight Agent (Windows) | [Rapid7 Release Notes](https://docs.rapid7.com/insight/release-notes-2026-april/) | Dell Security Assurance |
| [CVE&#8209;2026&#8209;3991](https://nvd.nist.gov/vuln/detail/CVE-2026-3991) | Symantec/Broadcom DLP Agent | [InfoGuard Labs Advisory](https://labs.infoguard.ch/advisories/cve-2026-3991_symantec-dlp-agent_local-privilege-escalation/) | [Manuel Feifel](https://labs.infoguard.ch/) (InfoGuard Labs) |
| [CVE&#8209;2025&#8209;53841](https://nvd.nist.gov/vuln/detail/CVE-2025-53841) | Akamai Guardicore Platform Agent | [Akamai Advisory](https://www.akamai.com/blog/security/2025/dec/advisory-cve-2025-53841-guardicore-local-privilege-escalation) | [SECURITEAM / Beyond Security SSD](https://securiteam.io/2025/09/08/privilege-escalation-akamai-guardicore-platform-agent/) |
| [CVE&#8209;2025&#8209;47161](https://nvd.nist.gov/vuln/detail/CVE-2025-47161) | Microsoft Defender for Endpoint (MDE) | [MSRC](https://msrc.microsoft.com/update-guide/vulnerability/CVE-2025-47161)<br>[Stratascale](https://www.stratascale.com/resource/cve-2025-47161-osquery-defender-linux/) | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE&#8209;2025&#8209;35471](https://nvd.nist.gov/vuln/detail/CVE-2025-35471) | conda-forge | [conda-forge issue #201](https://github.com/conda-forge/openssl-feedstock/issues/201) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2025&#8209;2272](https://nvd.nist.gov/vuln/detail/CVE-2025-2272) | Forcepoint Endpoint DLP | [Triskele Labs Blog](https://www.triskelelabs.com/blog/cve-2025-2272-forcepoint-endpoint-dlp-privilege-escalation) | [Triskele Labs](https://www.triskelelabs.com/) |
| [CVE&#8209;2024&#8209;6975](https://nvd.nist.gov/vuln/detail/CVE-2024-6975) | Cato Networks SDP Client | [AmberWolf Blog](https://blog.amberwolf.com/blog/2024/july/cve-2024-6975-cato-client-local-privilege-escalation-via-openssl-configuration-file/) | [AmberWolf](https://blog.amberwolf.com/) |
| [CVE&#8209;2024&#8209;0394](https://nvd.nist.gov/vuln/detail/CVE-2024-0394) | Rapid7 Minerva Armor | [Rapid7 Blog](https://www.rapid7.com/blog/post/2024/04/03/cve-2024-0394-rapid7-minerva-armor-privilege-escalation-fixed/) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2023&#8209;41840](https://nvd.nist.gov/vuln/detail/CVE-2023-41840) | FortiClient Windows | [FortiGuard PSIRT](https://www.fortiguard.com/psirt/FG-IR-23-274) | Undisclosed |
| [CVE&#8209;2023&#8209;40596](https://nvd.nist.gov/vuln/detail/CVE-2023-40596) | Splunk Enterprise for Windows | [Splunk SVD-2023-0805](https://advisory.splunk.com/advisories/SVD-2023-0805) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2022&#8209;32223](https://nvd.nist.gov/vuln/detail/CVE-2022-32223) | Node.js / npm CLI | [Aqua Security Blog](https://www.aquasec.com/blog/cve-2022-32223-dll-hijacking/) | [Yakir Kadkoda](https://www.aquasec.com/) (Aqua Security) |
| [CVE&#8209;2022&#8209;29505](https://nvd.nist.gov/vuln/detail/CVE-2022-29505) | LINE for Windows | — | Undisclosed |
| [CVE&#8209;2022&#8209;26872](https://nvd.nist.gov/vuln/detail/CVE-2022-26872) | Tychon Endpoint | [CERT VU#730007](https://www.kb.cert.org/vuls/id/730007) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2022&#8209;0166](https://nvd.nist.gov/vuln/detail/CVE-2022-0166) | McAfee Agent | [CERT VU#287178](https://www.kb.cert.org/vuls/id/287178) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2021&#8209;2356](https://nvd.nist.gov/vuln/detail/CVE-2021-2356) | Oracle MySQL for Windows | [Oracle CPU July 2021](https://www.oracle.com/security-alerts/cpujul2021.html) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2021&#8209;2307](https://nvd.nist.gov/vuln/detail/CVE-2021-2307) | MySQL for Windows |  [CERT VU#567764](https://www.kb.cert.org/vuls/id/567764)  | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2020&#8209;36169](https://nvd.nist.gov/vuln/detail/CVE-2020-36169) | Veritas NetBackup / OpsCenter (Windows) | [Veritas VTS20-016](https://www.veritas.com/content/support/en_US/security/VTS20-016) | Undisclosed |
| [CVE&#8209;2020&#8209;36168](https://nvd.nist.gov/vuln/detail/CVE-2020-36168) | Veritas Resiliency Platform | [Veritas VTS20-015](https://www.veritas.com/content/support/en_US/security/VTS20-015) | Undisclosed |
| [CVE&#8209;2020&#8209;36167](https://nvd.nist.gov/vuln/detail/CVE-2020-36167) | Veritas Backup Exec | [Veritas VTS20-010](https://www.veritas.com/content/support/en_US/security/VTS20-010)<br>[CERT VU#429301](https://www.kb.cert.org/vuls/id/429301) | Undisclosed |
| [CVE&#8209;2020&#8209;36166](https://nvd.nist.gov/vuln/detail/CVE-2020-36166) | Veritas InfoScale / Storage Foundation / VIOM | [Veritas VTS20-014](https://www.veritas.com/content/support/en_US/security/VTS20-014) | Undisclosed |
| [CVE&#8209;2020&#8209;36165](https://nvd.nist.gov/vuln/detail/CVE-2020-36165) | Veritas Desktop and Laptop Option (DLO) | [Veritas VTS20-012](https://www.veritas.com/content/support/en_US/security/VTS20-012) | Undisclosed |
| [CVE&#8209;2020&#8209;36164](https://nvd.nist.gov/vuln/detail/CVE-2020-36164) | Veritas Enterprise Vault | [Veritas VTS20-013](https://www.veritas.com/content/support/en_US/security/VTS20-013) | Undisclosed |
| [CVE&#8209;2020&#8209;36163](https://nvd.nist.gov/vuln/detail/CVE-2020-36163) | Veritas NetBackup / OpsCenter (Windows) | [Veritas VTS20-016](https://www.veritas.com/content/support/en_US/security/VTS20-016) | Undisclosed |
| [CVE&#8209;2020&#8209;36162](https://nvd.nist.gov/vuln/detail/CVE-2020-36162) | Veritas CloudPoint (Windows Agent) | [Veritas VTS20-011](https://www.veritas.com/content/support/en_US/security/VTS20-011) | Undisclosed |
| [CVE&#8209;2020&#8209;36161](https://nvd.nist.gov/vuln/detail/CVE-2020-36161) | Veritas APTARE IT Analytics | [Veritas VTS20-009](https://www.veritas.com/content/support/en_US/security/VTS20-009) | Undisclosed |
| [CVE&#8209;2020&#8209;36160](https://nvd.nist.gov/vuln/detail/CVE-2020-36160) | Veritas System Recovery | [Veritas VTS20-017](https://www.veritas.com/content/support/en_US/security/VTS20-017) | Undisclosed |
| [CVE&#8209;2020&#8209;10143](https://nvd.nist.gov/vuln/detail/CVE-2020-10143) | Macrium Reflect | [CERT VU#760767](https://www.kb.cert.org/vuls/id/760767) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2020&#8209;10139](https://nvd.nist.gov/vuln/detail/CVE-2020-10139) | Acronis True Image 2021 | [CERT VU#114757](https://www.kb.cert.org/vuls/id/114757) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2020&#8209;10138](https://nvd.nist.gov/vuln/detail/CVE-2020-10138) | Acronis Cyber Backup / Cyber Protect | [CERT VU#114757](https://www.kb.cert.org/vuls/id/114757) | [Will Dormann](https://github.com/wdormann) |
| [CVE&#8209;2020&#8209;8224](https://nvd.nist.gov/vuln/detail/CVE-2020-8224) | Nextcloud Desktop Client | [HackerOne #622170](https://hackerone.com/reports/622170) | [l00ph0le](https://hackerone.com/l00ph0le) |
| [CVE&#8209;2020&#8209;7224](https://nvd.nist.gov/vuln/detail/CVE-2020-7224) | Aviatrix OpenVPN Client | [blog.mirch.io](https://blog.mirch.io/cve/) | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE&#8209;2019&#8209;12572](https://nvd.nist.gov/vuln/detail/CVE-2019-12572) | PIA VPN | [blog.mirch.io](https://blog.mirch.io/2019/06/10/cve-2019-12572-pia-windows-privilege-escalation-malicious-openssl-engine/) | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE&#8209;2019&#8209;10211](https://nvd.nist.gov/vuln/detail/CVE-2019-10211) | PostgreSQL | [PostgreSQL Security](https://www.postgresql.org/support/security/CVE-2019-10211/) | [Daniel Gustafsson](https://github.com/danielgustafsson) |
| [CVE&#8209;2019&#8209;5443](https://nvd.nist.gov/vuln/detail/CVE-2019-5443) | curl | [curl.se](https://curl.se/docs/CVE-2019-5443.html)<br>[daniel.haxx.se](https://daniel.haxx.se/blog/2019/06/24/openssl-engine-code-injection-in-curl/) | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE&#8209;2019&#8209;2390](https://nvd.nist.gov/vuln/detail/CVE-2019-2390) | mongoDB | [MongoDB SERVER-42233](https://jira.mongodb.org/browse/SERVER-42233) | [Rich Mirch](https://x.com/0xm1rch) |
| [CVE&#8209;2019&#8209;1552](https://nvd.nist.gov/vuln/detail/CVE-2019-1552) | OpenSSL | [OpenSSL Security Advisory](https://www.openssl.org/news/secadv/20190730.txt) | [Rich Mirch](https://x.com/0xm1rch) |
| N/A | Monero Wallet GUI (Windows) | [HackerOne #630903](https://hackerone.com/reports/630903) | [l00ph0le](https://hackerone.com/l00ph0le) |
| N/A | stunnel | [stunnel-announce](https://www.stunnel.org/pipermail/stunnel-announce/2019-June/000145.html) | [Rich Mirch](https://x.com/0xm1rch) |


