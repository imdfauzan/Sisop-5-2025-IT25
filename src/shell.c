#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

#define DEFAULT 0x0F
#define MAELSTROM_RED     0x0C
#define TWINADDER_YELLOW  0x0E
#define IMMORTALFLAMES_BLUE    0x0B

#define GC_DEFAULT     0
#define MAELSTROM      1
#define TWINADDER      2
#define IMMORTALFLAMES 3

char* yogurt_responses[] = {
    "yo",
    "ts unami gng </3",
    "sygau"
};
#define NUM_YOGURT_RESPONSES (sizeof(yogurt_responses) / sizeof(yogurt_responses[0]))

byte currentGC = GC_DEFAULT;
char baseUsername[64];

void shell(){
  char buf[128];
  char cmd[64];
  char arg[2][64];
  int i, j;

  for (i = 0; i < 64; i++) {
    baseUsername[i] = '\0';
  }
  baseUsername[0] = 'u';
  baseUsername[1] = 's';
  baseUsername[2] = 'e';
  baseUsername[3] = 'r';
  baseUsername[4] = '\0';

  for (i = 0; i < 2; i++)
    for (j = 0; j < 64; j++)
      arg[i][j] = '\0';

  printString("Welcome to EorzeOS!\r\n");

  while (true) {
    if (currentGC == MAELSTROM) {
      textColor(MAELSTROM_RED);
    } else if (currentGC == TWINADDER) {
      textColor(TWINADDER_YELLOW);
    } else if (currentGC == IMMORTALFLAMES) {
      textColor(IMMORTALFLAMES_BLUE);
    } else {
      textColor(DEFAULT);
    }

    printString(baseUsername);
    if (currentGC == MAELSTROM) {
      printString("@Storm");
    } else if (currentGC == TWINADDER) {
      printString("@Serpent");
    } else if (currentGC == IMMORTALFLAMES) {
      printString("@Flame");
    }
    printString("> ");

    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "yo")) {
      printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
      printString("yo\r\n");
    } else if (strcmp(cmd, "user")) {
        if (arg[0][0] != '\0') {
          strcpy(baseUsername, arg[0]);
          printString("Username changed to ");
          printString(arg[0]);
          printString("\r\n");
      } else {
      strcpy(baseUsername, "user");
      printString("Username changed to user\r\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
        if (arg[0][0] == '\0') {
          printString("Error: Missing argument for grandcompany.\r\n");
        } else if (strcmp(arg[0], "maelstrom")) {
          currentGC = MAELSTROM;
          textColor(MAELSTROM_RED);
          clearScreen();
        } else if (strcmp(arg[0], "twinadder")) {
          currentGC = TWINADDER;
          textColor(TWINADDER_YELLOW);
          clearScreen();
        } else if (strcmp(arg[0], "immortalflames")) {
          currentGC = IMMORTALFLAMES;
          textColor(IMMORTALFLAMES_BLUE);
          clearScreen();
        } else {
          printString("Error: Invalid Grand Company '");
          printString(arg[0]);
          printString("'.\r\n");
        }
    } else if (strcmp(cmd, "clear")) {
      currentGC = GC_DEFAULT;
      textColor(DEFAULT);
      clearScreen();
    } else if (strcmp(cmd, "add")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      result = x + y;
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");
    } else if (strcmp(cmd, "sub")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      result = x - y;
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");
    } else if (strcmp(cmd, "mul")) {
      int x, y, result, i;
      char resultStr[64];
      result = 0;
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      if (x < 0 && y < 0) {
        x = -x;
        y = -y;
      } else if (y < 0) {
        int temp = x;
        x = y;
        y = temp;
      }
      for (i = 0; i < y; i++) {
        result = result + x;
      }
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");
    } else if (strcmp(cmd, "div")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      result = div(x, y);
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");
    } else if (strcmp(cmd, "yogurt")) {
        unsigned int tick = randBiosTick();
        int random_index;
        if (NUM_YOGURT_RESPONSES > 0) {
            random_index = mod(tick, NUM_YOGURT_RESPONSES);
        } else {
            random_index = 0;
        }
        if (random_index >= 0 && random_index < NUM_YOGURT_RESPONSES) {
            printString(yogurt_responses[random_index]);
        } else {
            printString(yogurt_responses[0]);
        }
        printString("\r\n");
    } else {
      printString(buf);
      printString("\r\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argIndex = 0;
  bool readingArg = false;

  for (i = 0; i < 64; i++) cmd[i] = '\0';
  for (i = 0; i < 2; i++)
    for (j = 0; j < 64; j++) arg[i][j] = '\0';

  i = 0;
  j = 0;

  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[j++] = buf[i++];
  }
  cmd[j] = '\0';

  while (buf[i] == ' ') i++;

  argIndex = 0;
  j = 0;
  while (buf[i] != '\0') {
    if (buf[i] == ' ') {
      arg[argIndex][j] = '\0';
      argIndex++;
      j = 0;
      i++;
      if (argIndex >= 2) break;
    } else {
      arg[argIndex][j++] = buf[i++];
    }
  }
  arg[argIndex][j] = '\0';
}