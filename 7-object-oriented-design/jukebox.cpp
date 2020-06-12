/*
Author: John Furlong
Date: June 12, 2020
Description: Jukebox
    Design a musical jukebox using object oriented principles.
*/
#include <iostream>
#include <vector>
using namespace std;

struct Song{
    string title;
    string artist;
    int length; // Duration in seconds
};

class Jukebox{
    private:
        vector<Song> songs;
    public:
        Jukebox(){

        }

        void display(){

        }

        void chooseSong(){
            
        }

        void queueSong(){

        }

        void addSongToLibrary(){

        }
};