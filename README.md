# Introduction
A little side project I hacked together when I got too lazy to set up boilerplate files and directories for new projects. It’s also a way for me to practice some C++.

With TemplateMaker, you can create reusable project templates and apply them anywhere with just one command.

## 🚀 Installation

### Dependecies
Make sure you have these installed:
- `cmake`
- `fd`
- `fzf`

### Steps
1. Clone this repository and go into the build directory
2. Build the Makefile with CMake. Run:
```bash
cmake ..
```
3. Then Make the Makefile. Run:
```bash
make
```
4. Then copy the executable to your local bin folder:
```bash
cp TemplateMaker ~/.local/bin/TemplateMaker
```


## 📦 Usage
1. Create a directory called `~/TemplateMaker/`
2. Add your templates inside `~/TemplateMaker/` as subdirectories. Each template can contain any structure you want.

Example:
```
── CompetitiveProgrammingTemplate
│   ├── a
│   │   ├── in
│   │   ├── out
│   │   └── sol.cpp
│   ├── b
│   │   ├── in
│   │   ├── out
│   │   └── sol.cpp
│   ├── c
│   │   ├── in
│   │   ├── out
│   │   └── sol.cpp
│   ├── d
│   │   ├── in
│   │   ├── out
│   │   └── sol.cpp
│   └── e
│       ├── in
│       ├── out
│       └── sol.cpp
└── ShawnTemplate
    ├── CMakeLists.txt
    ├── file1.txt
    ├── file2.txt
    └── file3.txt
```

3. Apply the template by running:
```bash
TemplateMaker {TemplateName}
```
Example:
```bash
TemplateMaker ShawnTemplate
```
4. Or if you don't remember the template name, you can just fuzzy-find it with:
```bash
TemplateMaker --fzf
```

# TODO
- [X] make a fzf option
- [ ] make a config file parser

