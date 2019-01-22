Program Krzysztofa Widackiego
C Pracownicze Plany Kapitalowe
Program napisany w C, przy użyciu biblioteki Ncurses, do obliczania opłacalności emerytury Pracowniczych Planów Kapitałowych

# Jak uruchomić
Na systemie Linux uruchom program poprzez ./main

# Wymagania do kompilacji
Zainstaluj na swoim komputerze:

- GCC
- Ncurses


GCC można zainstalować poprzez:
```
sudo apt install gcc
```
Ncurses można zainstalować poprzez:

Debian/Ubuntu Linux 
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older 
```
sudo yum install ncurses-devel
```

Fedora Linux 22.x+ 
```
sudo dnf install ncurses-devel
```
# Jak kompilować
Następnie wprowadź komendę:
```
gcc -Wall -o "main" "main.c" "myNcursesLib.c" "fileOperations.c" "simulate.c" -lmenu -lncurses -lm  && ./main
```
Albo:
```
gcc -Wall -o "main" *.c -lmenu -lncurses -lm && ./main
```
