Checkpoint 2 Writeup
====================

My name: [your name here]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

I would like to thank/reward these classmates for their help: [list sunetids here]

This lab took me about [7] hours to do. I [did/did not] attend the lab session.

Program Structure and Design of the TCPReceiver and wrap/unwrap routines:
[]

Implementation Challenges:
[]

Remaining Bugs:
[]

- Optional: I had unexpected difficulty with: 

## docker

**current: it can compile some tests and pass, but can't run lldb**
because my github codespace usage reached limit, so I need rebuild environment
on my devbox, sadly I can't solve include directory. I hope I have some luck
in my old docker build.
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
I met Servname not supported for ai_socktype, I found I have no  /etc/services in docker,
I copy my devbox this file here, it works.

I download lldb-15 but run lldb-15 --version it says No module named 'lldb.embedded_interpreter',
this is llvm bug, link correct llvm lib site-packages to `lldb-15 -P` result directory.

I solve above lldb issue, but I can't run in lldb and it says `error: 'A' packet returned an error: 8`
I google it and answer says I need docker run with `--cap-add=SYS_PTRACE --security-opt seccomp=unconfined`
But cap-add seems work, security-opt not appear in docker run command. Unfortunately it still report error again.
Maybe I should try my old MBP, this M1 has some architecture issue.

## devbox(give up)
**current:it reported header file not found, I config include path correctly but VSC didn't recognize**
I had include/c++/6.0 in my devbox, I moved to another name but it still reported weird header
not found, I confirmed /usr/lib/llvm-15/include/c++/v1 had every header but VSC and cmake
told it couldn't find. give up.

## mac(give up)
**current:it told `use of undeclared identifier 'AF_PACKET'` that macOS can't suite POSIX**
I install llvm@15 but it still not work because `use of undeclared identifier 'AF_PACKET'`
this is POSIX standard not suite for macOS.

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]

- Optional: I made an extra test I think will be helpful in catching bugs: [describe where to find]
