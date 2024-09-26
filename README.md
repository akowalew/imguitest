# imguitest

Simple test application to verify how small static executable can we produce with ImGUI library for Win32-OpenGL target.

Few important things:
- No external dependencies - only ImGUI. Single translation unit build, Win32 platform code written by hand.
- To make test results more realistic I've made two sets of tests: drawn with ImGUI demo window and drawn with only single label on empty window. ImGui's demo window contains a lot of widgets and logic and may ilustrate some edge case how our app can grow in case of big UI.
- In order to achieve even better results I've decided to use UPX compressor on final .EXE file.
- Of course app contains no external DLL dependencies (except Windows native DLLs). Standard library is bundled statically into executable.
- I performed tests for two architectures: 32bit and 64bit - x86, because I expect 32-bit binary to be simply smaller.
- I use MSVC's `/O1` option for generation of "small" code. Also I pass to linker `/OPT:REF`, and `/OPT:ICF` for removing unnused/duplicated sections.
- Note that generation of debug info doesn't change .EXE size, since for MSVC it is stored in .PDB files (externally)
- UPX is invoked with `--ultra-brute` option
- For x64 I've used MSVC 19.41.34120, for x86 I've used MSVC 19.16.27051
- Haven't tested clang yet, but maybe it can achieve even better results.
  
How looks the app with ImGUI demo window:
![image](https://github.com/user-attachments/assets/43630c24-f7b2-481f-9cf2-1062bf802f21)

How looks the app with only single label on it:
![image](https://github.com/user-attachments/assets/b743eea4-84cf-410b-aa63-174874f9c497)

App is fully static, so we can just copy it to other PC and run it without any installers:
![image](https://github.com/user-attachments/assets/548f1fc1-985a-424a-bc0f-cd999e4d0518)

## Results for x86 64-bit

With ImGui demo window:

![image](https://github.com/user-attachments/assets/ee73405f-1958-482a-a6c0-d7480fac0ae6)

Single label on empty window:

![image](https://github.com/user-attachments/assets/0922f468-ef19-434d-9646-0c5510950213)

## Results for x86 32-bit

With ImGui demo window:

![image](https://github.com/user-attachments/assets/aa765139-055a-41f3-8aa1-cccf7e3f6fcc)

Single label on empty window:

![image](https://github.com/user-attachments/assets/420134b5-988a-4506-878c-25a2b8e4c4b4)

# Summary

As expected, UPX gives huge space reduction, even 2-3x. 

Also, as expected, 32-bit binaries are smaller, and probably also much faster (pointers are 32bit instead of 64bit, so the app is not loosing cache/mem bandwith). 

To summarize - depending on app complexity, we can produce the EXE to be around 200-400KB of just GUI code with ImGUI and UPX, for Win32-OpenGL target.
