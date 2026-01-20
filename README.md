#  Competitive Programming C+0

This repository contains my solutions to various competitive programming problems from Codeforces and others, as well as other items which I use for my environment.  

### Prerequisites
- A Linux distro  
- clang++ supporting C++23 (changeable)  
- lldb (for debugging, changeable)  
- Neovim (for editing, changeable)  

### Setup  
```bash
# Intended to work at home directory
cd ~
git clone https://github.com/The-Blinking-Brownie/cppcp.git

# Setting up symbolic links for the scripts
cd cppcp
chmod +x bin/*
scripts=("ed.sh" "cl.sh" "tst.sh" "db.sh")
ln -t ~/.local/bin -s "${scripts[@]/#/$(pwd)/bin/}"
for f in ~/.local/bin/*; do mv "$f" "${f%.*}"; done
# You can also choose another location such as /usr/local/sbin 
# Be sure it's in the PATH

```  

### Configuring
If you use a different compiler or want to disable pch then change config/compile.sh  
Example script for generating pch:  
```bash
mkdir bits
clang++ -c -fno-omit-frame-pointer -std=c++23 -x c++-header -o bits/stdc++.h -g /usr/include/c++/14.2.1/x86_64-pc-linux-gnu/bits/stdc++.h
```  
Change config/debug.sh for a different debugger.  
Change config/editor.sh for a different editor. It is called locally with $name set to the file name without the file extension.  
Change config/template.sh to update the template.  

## Directory structure
The working directory is cppcp. Here, all the problems I am working on are displayed.  
The scripts are intended to only modify files here as well.  
The scripts themselves lie in cppcp/bin/  
Completed problems go to codeforces/ or timus/ or othercompleted/  
config/ has been demonstrated.  
headers/ contains header files which can be included (intended for debugging) or copied into solutions.  
.tmp/ contains temporary files which will be deleted any time bin/cl is called.  
.tmp/source.txt contains the name of the file that was last edited, sometimes referred to as last ed-modified file. It should not have a file extension. (If source.txt wasn't deleted.)  
.tmp/inp0.txt is used by bin/tst (which is called by bin/ed if -t flag used).  

## Scripts
All scripts (ed, tst, cl, db) have descriptions which can be viewed in their source files and are displayed when passing wrong flags.  
ed - Modifies file.  
tst - Runs the executable with .tmp/inp0.txt .tmp/inp1.txt... and displays .tmp/out0.txt...  
db - Runs debugger, passing .tmp/inp0.txt as input to the executable.  
cl - Marks file as completed (or removes it) and clears .tmp/
