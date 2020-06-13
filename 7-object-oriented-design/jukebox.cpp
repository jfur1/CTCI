/*
Author: John Furlong
Date: June 12, 2020
Description: Jukebox
    Design a musical jukebox using object oriented principles.
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Song{
    string title;
    string artist;
    string album;
    string imgFilename;
    int length; // Duration in seconds
};

struct Playlist{
    string name;
    queue<Song> tracks;
};

struct User{
    string name;
    Playlist playlist;
};

class Jukebox{
    private:
        queue<Song> q;
        vector<Song> library;
        Song currentSong;
    public:

        Jukebox(){
            
        }

        void display(Song song){
            // print(/songs/...)
            cout << song.title << endl;
            cout << song.artist << endl;
            cout << song.album << endl;
            cout << song.length << endl;
        }

        void chooseSong(Song song){
            if(q.empty())
                currentSong = song;
            else
                queueSong(song);
        }

        void queueSong(Song song){
            q.push(song);
        }

        void addSongToLibrary(Song song){
            library.push_back(song);
            song.imgFilename = "/songs/" + song.title;
        }
};