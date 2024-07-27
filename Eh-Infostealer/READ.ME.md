# Attacker's Infostealer

## Pre-Creation Configurations
1. Download curl/libcurl binaries and build them.
2. Compile the infostealer into an .exe file.
3. Convert that .exe file into shellcode using.
4. Place the shellcode into the placeholder of the actual malware.
5. Build and compile to get the final malware.

## How the Infostealer works
The Infostealer code here is broken into two parts. First is the actual infostealer that is later translated into shellcode. Second is the malware executable that we would be sending to the