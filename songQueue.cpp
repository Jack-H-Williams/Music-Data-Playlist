#include "songQueue.h"
//Author: Jack Williams
//Email: Jack.H.Willi@gmail.com

//Default Constructor: initialize all member vars
Song::Song() {
  m_name = "none";
  m_artist = "none";
  m_duration = 0;

  m_next = nullptr;
  m_previous = nullptr;
}

//Overloaded Constructor: use params to initialize all member vars
Song::Song(string name, string artist, double length) {
  m_name = name;
  m_artist = artist;
  m_duration = length;

  m_next = nullptr;
  m_previous = nullptr;
}

//Getters
string Song::getName() const {
  return m_name;
}

string Song::getArtist() const {
  return m_artist;
}

double Song::getLength() const {
  return m_duration;
}

//Setters
void Song::setName(string title) {
  m_name = title;
}

void Song::setArtist(string artist) {
  m_artist = artist;
}

void Song::setLength(double time) {
  m_duration = time;
}

//Default Constructor: initialize all member vars
Playlist::Playlist() {
  m_head = nullptr;
  m_tail = nullptr;
  m_current = nullptr;
  m_size = 0;
  m_shuffleMode = false;
}

//Destructor: free all nodes
Playlist::~Playlist() {
  Song* temp = m_head; //points to first song node
  Song* prev = nullptr;

  while (temp != nullptr) {
    prev = temp;
    temp = temp -> m_next;
    delete prev;
  }

  m_head = nullptr;
  m_tail = nullptr;
  m_current = nullptr;
  m_size = 0;
}

//Copy Constructor: deep copy all nodes to replicate playlist
Playlist::Playlist(const Playlist& rhs) {
  Song* temp = rhs.m_head;
  Song* prev = nullptr;

  //ensure all values a null/0
  m_size = 0;
  m_head = nullptr;
  m_tail = nullptr;
  m_current = nullptr;

  while (temp != nullptr) { //temp hits null but does not re-enter loop
    Song* newSong = new Song(temp -> m_name, temp -> m_artist, temp -> m_duration);

    newSong -> m_previous = prev;
    newSong -> m_next = nullptr;

    if (prev != nullptr) {
      prev -> m_next = newSong; //safe to set prev song's m_next
    }
    else {
      m_head = newSong;  //first song added
    }

    m_tail = newSong;
    prev = newSong;
    
    temp = temp -> m_next;
    m_size++;
  }

  //copy current's position
  if (rhs.m_current == nullptr) { //safey check
    m_current = nullptr;
    return;
  }
  
  temp = m_head;
  while (temp != nullptr) {
    if ((temp -> m_name == rhs.m_current -> m_name) and (temp -> m_artist == rhs.m_current -> m_artist)) {
      m_current = temp;
    }

    temp = temp -> m_next;
  }
}

Playlist& Playlist::operator=(const Playlist& rhs) {
  if (this == &rhs) {
    return *this; //self-assignment protection
  }

  if (m_head != nullptr) { //ensure playlist is empty
    Song* temp = m_head;
    Song* prev = nullptr;

    while (temp != nullptr) {
      prev = temp;
      temp = temp -> m_next;

      delete prev;
    }
  }

  m_head = nullptr;
  m_tail = nullptr;
  m_current = nullptr;
  m_size = 0;

  //copy nodes
  Song* temp = rhs.m_head;
  Song* prev = nullptr;

  while (temp != nullptr) { //temp hits null but does not re-enter loop                                                                                                                                                      
    Song* newSong = new Song(temp -> m_name, temp -> m_artist, temp -> m_duration);
    newSong -> m_previous = prev;
    newSong -> m_next = nullptr;
    
    if (prev != nullptr) {
      prev -> m_next = newSong; //safe to set prev song's m_next                                                                                                                                                              
    }
    else {
      m_head = newSong; //first song added                                                                                                                                                                                   
    }

    m_tail = newSong;
    prev = newSong;
    temp = temp -> m_next;
    m_size++;
  }

  //copy current's position
  if (rhs.m_current == nullptr)	{ //safety check
    m_current =	nullptr;
    return *this;
  }
  
  temp = m_head;
  while (temp != nullptr) {
    if ((temp -> m_name == rhs.m_current -> m_name) and (temp -> m_artist == rhs.m_current -> m_artist)) { //meets cond
      m_current = temp;
    }

    temp = temp -> m_next; //keep moving
  }

  return *this;
}

void Playlist::addSong(string name, string artist, double time) {
  Song* newSong = new Song(name, artist, time); //create new node
  
  if (m_size == 0) {
    m_head = newSong;
    m_tail = newSong;
    m_current = newSong;  //set current as first song added
    }
  else {
    m_tail -> m_next = newSong; //tail points to old last node
    newSong -> m_previous = m_tail;
    m_tail = newSong;
  }

  m_size++;
}

void Playlist::removeCurrent() {

  if (m_current == nullptr) { //no song playing
    return;
  }
  
  Song* temp = m_current;
  
  if (temp -> m_previous != nullptr) {
    temp -> m_previous -> m_next = temp -> m_next; //skip over (forward)
  }
  else { //head node
    m_head = temp -> m_next;
  }

  if (temp -> m_next != nullptr) {
    temp -> m_next -> m_previous = temp -> m_previous; //skip over (backward)
  }
  else { //tail node
    m_tail = temp -> m_previous;
  }

  //adjust current song
  if (temp -> m_next != nullptr) {
    m_current = temp -> m_next;
  }
  else {
    m_current = temp -> m_previous;
  }

  delete temp;
  m_size--;
}

void Playlist::skipForward() {
  if (m_current == nullptr) { //no song playing                                                                                                                     
    return;
  }

  if (m_size <= 1) { //no shuffle for 1 song
    return;
  }

  if (m_shuffleMode == false) {
    if (m_current -> m_next == nullptr) {
      m_current = m_head; //loop to start
      return;
    }

    m_current = m_current -> m_next;
    return;
  }

  //shuffle mode is on
  int jump = rand() % m_size; //mod to ensure jump in bounds
  Song* temp = m_head;

  for (int i = 0; i < jump; i++) {
    temp = temp -> m_next;
  }

  m_current = temp;
}
  

void Playlist::skipBack() { //always linear 
  if (m_current == nullptr) { //no song playing                                                                                                             
    return;
  }

  if (m_current -> m_previous == nullptr) {
    m_current = m_tail; //loop to end
    return;
  }

  m_current = m_current -> m_previous;
}

void Playlist::shuffleSwitch() {

  if (m_size <= 3) {
    cout << "Cannot change shuffle mode with less than 3 songs" << endl;
    return;
  }
  
  m_shuffleMode = !m_shuffleMode; //changes skip behavior

  if (m_shuffleMode == true) {
    cout << "Shuffle mode is on!" << endl;
  }
  else if (m_shuffleMode == false) {
    cout << "Shuffle mode is off." << endl;
  }
  
}

void Playlist::clear() {
  Song* temp = m_head; //points to first song node
  Song* prev = nullptr;

  while (temp != nullptr) {
    prev = temp;
    temp = temp -> m_next;
    delete prev;
  }

  m_head = nullptr;
  m_tail = nullptr;
  m_current = nullptr;
  m_size = 0;
}

void Playlist::displayPlaylist() const {
  Song* temp = m_head;
  int order = 1;

  if (m_head == nullptr) {
    cout << "playlist is empty." << endl;
    return;
  }

  cout << "Here is your playlist!" << endl;
  
  while (temp != nullptr) { // includes/processes last node
    cout << order << ". " << temp -> getName() << " by " << temp -> getArtist() << " ("
	 << temp -> getLength() << ")." << endl;

    temp = temp -> m_next;
    order = order + 1;
  }

}

void Playlist::displayCurrent() const {
  if (m_current == nullptr) {
    cout << "No song is currently playing." << endl;
    return;
  }

  cout << "Song Playing: " << m_current -> getName() << " by " << m_current -> getArtist() << endl;
}

bool Playlist::isEmpty() const {
  if (m_size == 0) {
    return true;
  }

  return false;
}

int Playlist::getSize() const {
  if (m_size >= 0) {
    return m_size;
  }

  return 0; //default value
}

bool Playlist::getMode() const {
  if (m_shuffleMode == true) {
    return true;
  }
  else {
    return false;
  }
}




  

  

      
  
    

    
  








  
