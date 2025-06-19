// About game

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "../0x280_building_on_the_basics/hacking.h"

#define DATAFILE "/var/chance.data"     // File to store user data.

// Custom user struct to store information abour users.
struct user {
  /* data */
  int uid;
  int credits;
  int highscore;
  char name[100];
  int (*current_game) ()
};

// Function prototypes.
int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game();
int pick_a_number();
int dealer_no_match();
int find_the_ace();
void fatal(char *);

// Global variables.
struct user player;     // Player struct.

int main() {
  int choice, last_game;

  srand(time(0));     // Seed the randomizer with the current time.

  if (get_player_data() == -1)      // Try to read player data from file.
    register_new_player();          //If not found, register a new player.
}

int get_player_data() {
  /* 
    This function reads the player data from the current uid
    from the file. It returns -1 if player data is not found
    for the current uid.
  */
  int fd, uid, read_bytes;
  struct user entry;

  uid = getuid();

  fd = open(DATAFILE, O_RDONLY);
  printf("%d\n", fd);
  if (fd == -1)     // Can't open the file, maybe it doesn't exist.
    return -1;
  read_bytes = read(fd, &entry, sizeof(struct user));     // Read the first chunk.
  while (entry.uid != uid && read_bytes > 0)              // Loop until proper uid is found.
    read_bytes = read(fd, &entry, sizeof(struct user));   // Keep reading.


  close(fd);      // Close the file.
  if (read_bytes < sizeof(struct user))     // This means that the end of file (EOF) was reached.
    return -1;
  else
    player = entry;     // Copy the read into the player struct.

  return 1;
}

void register_new_player() {
  int fd;

  puts("-=-={ New Player Registration }=-=-\n");
  puts("Enter your name: ");
  input_name();

  player.uid = getuid();
  player.highscore = player.credits = 100;

  fd = open(DATAFILE, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
  if (fd == -1)
    fatal("In register_new_player() while opening file");     // Got a permission denied error
  write(fd, &player, sizeof(struct user));
  close(fd);

  printf("\nWelcome to the Game of Chnace %s.\n", player.name);
  printf("You have been given %u credits.\n", player.credits);
}

void input_name() {
  /*
    This function is used to input the player name
  */
  char *name_ptr, input_char = '\n';
  while (input_char == '\n')      // Flush from leftover
    scanf("%c", &input_char);     // newline chars.

  name_ptr = (char *)&(player.name);      // name_ptr = player name's address
  while (input_char != '\n') {    // Loop until newline.
    *name_ptr = input_char;       // Put the input char into name field.
    scanf("%c", &input_char);     // Get the next char.
    name_ptr++;                   // Increment the name pointer.
  }
  *name_ptr = 0;      // Terminate the string.
}
