/*
  File: driver.cpp
  Author: Jack Williams
  Desc:
      Provides a simple command-line interface that allows a user to utilize playlist functions.
*/

#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>    
#include <limits>   
#include "songQueue.h"

int main() {

  bool quit = false; //end bool
  int input = 0; //user menu input
  
  srand(static_cast<unsigned>(time(nullptr)));

  Playlist mySongs;
  cout << "Welcome! Here are a few notes: " << endl;
  cout << " - This menu holds song data and will not play music" << endl;
  cout << " - Songs skip based on user action (not length)" << endl;
  cout << " - Shuffle mode may loop back to the same song and requires at least 4 songs to activate" << endl;
  cout << "Enjoy!" << endl;

  while (quit != true) { //stop when user picks 8
    cout << "**Music Playlist**" << endl;
    cout << "Please select an action." << endl;

    cout << "1. Add song" << endl;
    cout << "2. Remove current song from list" << endl;
    cout << "3. Skip forward" << endl;
    cout << "4. Skip back" << endl;
    cout << "5. Toggle shuffle" << endl;
    cout << "6. Show playlist + current song playing" << endl;
    cout << "7. Clear playlist" << endl;
    cout << "8. quit" << endl;

    cin >> input;
  
    while ((input > 8) or (input < 1)) { //check for valid input
      cout << "please enter a valid number." << endl;
      cin >> input;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ensure cin is clear
    
    if (input == 1) {
      string author;
      string title;
      double time;

      cout << "Please enter the author's name:" << endl;
      getline(cin, author);

      cout << "Please enter the title:" << endl;
      getline(cin, title);

      cout << "Please enter the song's length: (sec)" << endl;
      cin >> time;

      mySongs.addSong(title, author, time);
      cout << "Song added!" << endl;
      
    }

    //utilize playlist class functions
    if (input == 2) {
      mySongs.removeCurrent();
      cout << "Removed current (if any)" << endl;
    }

    if (input == 3) {
      mySongs.skipForward();
      cout << "Moved up (if possible)" << endl;
    }

    if (input == 4) {
      mySongs.skipBack();
      cout << "Moved back (if possible" << endl;
    }

    if (input == 5) {
      mySongs.shuffleSwitch();
    }
    
    if (input == 6) {
      mySongs.displayPlaylist();

      mySongs.displayCurrent();
    }

    if (input == 7) {
      mySongs.clear();
      cout << "Songs cleared!" << endl;
    }

    if (input == 8) {
      quit = true;
      cout << "Thanks for playing!!" << endl;
    }

    cout <<  '\n' << endl; //break up each input
  }
}
    
