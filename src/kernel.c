#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

#define DEFAULT 0x0F

byte currentTextAttribute = DEFAULT;

void textColor(byte attribute) {
    currentTextAttribute = attribute;
}

void printString(char *str) {
    while (*str != '\0') {
        if (*str == '\n') {
            interrupt(0x10, 0x0E0A, 0, 0, 0);
            interrupt(0x10, 0x0E0D, 0, 0, 0);
        } else {
            interrupt(0x10, 0x0E00 + *str, 0, 0, 0);
        }
        str++;
    }
}

void readString(char *buf) {
    int i = 0;
    char c;
    while (1) {
        c = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;
        if (c == 0x0D) {
            break;
        } else if (c == 0x08) {
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else {
            buf[i++] = c;
            interrupt(0x10, 0x0E00 + c, 0, 0, 0);
        }
    }
    buf[i] = '\0';
    printString("\r\n");
}

void setCursorPosition(int row, int col) {
    interrupt(0x10, 0x0200, 0, 0, (row << 8) | col);
}

unsigned int randBiosTick() {
    return getBiosTick();
}

void clearScreen() {
    int i;
    for (i = 0; i < 80 * 25; i++) {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, currentTextAttribute);
    }
    setCursorPosition(0, 0);
}