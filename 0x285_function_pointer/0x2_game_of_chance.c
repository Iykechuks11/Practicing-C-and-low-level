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
  int (*current_game)();
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

  while(choice != 7) {
    printf("-=[ Game of Chance Menu ]=-\n");
    printf("1 - Play the Pick a Number game\n");
    printf("2 - Play the No Match Dealer game\n");
    printf("3 - Play the Find the Ace game\n");
    printf("4 - View current high score\n");
    printf("5 - Change your user name\n");
    printf("6 - Reset your account at 100 credits\n");
    printf("7 - Quit\n");
    printf("[Name: %s]\n", player.name);
    printf("[You have %u credits] -> ", player.credits);
    scanf("%d", &choice);

    if ((choice < 1) || (choice > 7))
      printf("\n[!!] The number %d is an invalid selection.\n\n", choice);
    else if (choice < 4) {        // Otherwise, choice was a game of some sort.
      if (choice != last_game) {  // If the function ptr isn't set,
        if (choice == 1)          // then point it at the selected game
          player.current_game = pick_a_number;
          // puts("I am here");
        else if (choice == 2)
          player.current_game = dealer_no_match;
        else
          player.current_game = find_the_ace;
        last_game = choice;       // and set last game.
      }
      play_the_game();            // Play the game
    }
    else if (choice == 4)
      show_highscore();
    else if (choice == 5) {
      // Let's test here <------------
      puts("\nChange user name\n");
      puts("Enter your new name");
      input_name();
      puts("Your name has been chnaged.\n\n");
    }
    else if (choice == 6) {
      printf("\nYour account has been reset with 100 credits.\n\n");
      player.credits = 100;
    }
  }
  update_player_data();
  printf("\nThanks for playing! Bye.\n");
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
  if (fd == -1)     // Can't open the file, maybe it doesn't exist. >> fixed
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

// This function simply awards the jackpot for the Pick a Number game.
void jackpot() {
  puts("*+*+*+*+*+* JACKPOT *+*+*+*+*+*\n");
  puts("You have won the jackpot of 100 credits!\n");
  player.credits += 100;
}

// This function inputs wagers for both the No Match Dealer game and
// Find the Ace games. It expects the available credits and the previous wager
// as arguments. The previous_wager is also important for the second wager in the
// Find the Ace game. The function returns -1 if the wager is too big or too little
// and it returns the wager amount otherwise.
int take_wager(int available_credits, int previous_wager) {
  int wager, total_wager;

  printf("How many of your %d credits would you like to wager? ", available_credits);
  scanf("%d", &wager);
  if (wager < 1) {      // Make sure the wager is greater than 0.
    puts("Nice try, but you must wager a positive number!");
    return -1;
  }

  total_wager = previous_wager + wager;

  if (total_wager > available_credits) {      // Confirm available credits
    printf("The wager of %d you are offering is more than you have!\n", total_wager);
    printf("You credit balance is %d, try again.\n", available_credits);
    return -1;
  }

  return wager;
}

// GAME 1: This function is the Pick a Number game.
// It returns -1 if the player doesn't have enough credits.
int pick_a_number() {
  int pick, winning_number;

  printf("\n####### Pick a Number ######\n");
  printf("This game costs 10 credits to play. Simply pick a number\n");
  printf("between 1 and 20, and if you pick the winning number, you\n");
  printf("will win the jackpot of 100 credits!\n\n");
  winning_number = (rand() % 20) + 1;      // Pick a number between 1 and 20.
  printf("winning number = %d\n", winning_number);
  if (player.credits < 10)
  {
    printf("You only have %d credits. That's not enough to play!\n\n", player.credits);
    return -1;      // Not enough credits to play.
  }
  player.credits -= 10;     // Deduct 10 credits.
  puts("10 credits have been deducted from your account.\n");
  puts("Pick a number between 1 and 20: ");
  scanf("%d", &pick);

  printf("The winning number is %d\n", winning_number);
  if (pick == winning_number)
    jackpot();
  else
    puts("Sorry, you didn't win.\n");
  return 0;
}

// GAME 2: This is the No Match Dealer game.
// It returns -1 if the player has 0 credits.
int dealer_no_match() {
  int i, j, numbers[16], wager = -1, match = -1;

  puts("::::::: No Match Dealer :::::::");
  puts("In this game, you can wager up to all of your credits.");
  puts("The dealer will deal out 16 random numbers between 0 and 99.");
  puts("If there are no matches among them, you double your money!");

  if (player.credits == 0) {
    puts("You don't have any credits to wayer!");
    return -1;
  }

  while (wager == -1)
    wager = take_wager(player.credits, 0);

  puts("\t\t::: Dealing out 16 random numbers :::");
  for (i = 0; i < 16; i++) {
    numbers[i] = rand() % 100;     // Pick a number between 0 and 99.
    printf("%2d\t", numbers[i]);
    if (i % 8 == 7)                // Print a line break every 8 numbers.
      puts("");
  }
  for (i = 0; i < 15; i++) {       // Loop looking for matches: sweet search algorithm
    j = i + 1;
    while (j < 16) {
      if (numbers[i] == numbers[j])
        match = numbers[i];       // All we need to find is just one match, and that's it
      j++;
    }
  }
  if(match != -1) {
    printf("The dealer matched the number %d!\n", match);
    printf("You lose %d credits.\n", wager);
    player.credits -= wager;
  } else {
    printf("There were no matches! You win %d credits!\n", wager);
    player.credits += wager;
  }
  return 0;
}

int find_the_ace() {
  return 1;
}

// This function writes the current player data to the file.
// It is used primarily for updating the credits after games.
void update_player_data() {
  int fd, i, read_uid;
  char burned_byte;

  fd = open(DATAFILE, O_RDWR);
  if (fd == -1)     // If open fails here, something is really wrong.
    fatal("In update_player_data() while opening file");
  // puts("I am here");
  // close(fd);
  read(fd, &read_uid, 4);     // Read the uid from the first struct.
  while (read_uid != player.uid) {      // Loop until correct uid is found
    for (i = 0; i < sizeof(struct user) - 4; i++)       // Read through the
      read(fd, &burned_byte, 1);                        // rest of that struct.
    read(fd, &read_uid, 4);
  }
  write(fd, &(player.credits), 4);      // Update credits.
  write(fd, &(player.highscore), 4);    // Update highscore.
  write(fd, &(player.name), 100);       // Update name/
  close(fd);
}

// This function contains a loop to allow the current game to be
// played again. It also writes the new credit totals to file
// after each game is played.
void play_the_game() {
  int play_again = 1;
  int (*game)();
  char selection;

  while (play_again) {
    printf("\n[DEBUG] current_game pointer @ 0x%08x\n", player.current_game);
    if (player.current_game() != -1) {        // If the game plays without error and
      if (player.credits > player.highscore)  // a new high score is set,
        player.highscore = player.credits;    // update the highscore.
      printf("\nYou now have %u credits\n", player.credits);
      update_player_data();                   //Write the new credit total to file.
      puts("Would you like to play again (y/n)");
      selection = '\n';
      while (selection == '\n')               // Flush any extra newlines.
        scanf("%c", &selection);
      if (selection == 'n')
        play_again = 0;
    }
    else                  // This means the game returned an error,
      play_again = 0;     // so return to main menu.
  }
}

void show_highscore() {
}

