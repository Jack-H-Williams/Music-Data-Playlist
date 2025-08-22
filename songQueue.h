/*
  File: songQueue.h
  Author: Jack Williams
  Desc:
      Declares the Song and Playlist classes used to manage and store song data.
      - Song Class: Includes links to the next and previous nodes for use in a doubly linked list.
      - Playlist class: Manages a doubly linked list of Song nodes. Supports
        adding, removing, traversing, shuffling, and displaying songs.
*/


#ifndef SONGQUEUE_H
#define SONGQUEUE_H
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Song { //serves as a node in the Linked List
  friend class Playlist; //give access to private vars
  
 public: 
  Song();
  Song(string name, string artist, double length);

  //Getters
  string getName() const;
  string getArtist() const;
  double getLength() const;

  //Setters
  void setName(string title);
  void setArtist(string artist);
  void setLength(double time);

 private:
  string m_name;
  string m_artist;
  double m_duration;

  Song* m_next;
  Song* m_previous;
};


class Playlist {
 public:
  //Manage Memory and Rule of 3
  Playlist(); 
  ~Playlist();
  Playlist(const Playlist& rhs); //copy con
  Playlist& operator=(const Playlist& rhs); //overloaded assign

  //Menu Functionality
  void addSong(string name, string artist, double time);
  void removeCurrent();
  void skipForward();
  void skipBack();
  void shuffleSwitch();
  void clear();

  //Dump Fcns
  void displayPlaylist() const;
  void displayCurrent() const;

  //internal Functionality
  bool isEmpty() const;
  int getSize() const;
  bool getMode() const;

 private:
  Song* m_head;
  Song* m_tail;
  Song* m_current;
  int m_size;
  bool m_shuffleMode;
};
#endif
  
  
  

