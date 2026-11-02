
#include <iostream>
#include <string>
using namespace std;

// Abstract Media base class
class Media {
protected:
    string title;

public:
    Media(string t) : title(t) {}

    virtual void displayInfo() const = 0;
    virtual void play() const = 0;

    string getTitle() const {
        return title;
    }

    bool operator==(const Media& other) const {
        return title == other.title;
    }

    virtual ~Media() {}
};

// Song class
class Song : public Media {
private:
    string artist;
    string genre;

public:
    Song(string t, string a, string g)
        : Media(t), artist(a), genre(g) {}

    void displayInfo() const override {
        cout << "[SONG] Title: " << title
             << " Artist: " << artist
             << " Genre: " << genre << endl;
    }

    void play() const override {
        cout << "Now playing: " << title << endl;
    }
};

// Podcast class
class Podcast : public Media {
private:
    string host;
    int episode;

public:
    Podcast(string t, string h, int e)
        : Media(t), host(h), episode(e) {}

    void displayInfo() const override {
        cout << "[PODCAST] Title: " << title
             << " Host: " << host
             << " Episode: " << episode << endl;
    }

    void play() const override {
        cout << "Playing podcast: " << title << endl;
    }
};

// Audiobook class
class Audiobook : public Media {
private:
    string author;
    string narrator;

public:
    Audiobook(string t, string a, string n)
        : Media(t), author(a), narrator(n) {}

    void displayInfo() const override {
        cout << "[AUDIOBOOK] Title: " << title
             << " Author: " << author
             << " Narrator: " << narrator << endl;
    }

    void play() const override {
        cout << "Playing audiobook: " << title << endl;
    }
};

// Function overloading: search by title
int searchMedia(Media* library[], int size,
                const string& target) {
    for (int i = 0; i < size; i++) {
        if (library[i]->getTitle() == target) {
            return i;
        }
    }
    return -1;
}

// Function overloading: search by index
Media* searchMedia(Media* library[], int size, int index) {
    if (index >= 0 && index < size) {
        return library[index];
    }
    return nullptr;
}

// Generic Playlist class template
template <typename T>
class Playlist {
private:
    T items[10];
    int count;

public:
    Playlist() : count(0) {}

    void addItem(T item) {
        if (count < 10) {
            items[count] = item;
            count++;
        }
        else {
            cout << "Playlist is full!" << endl;
        }
    }

    void displayPlaylist() const {
        for (int i = 0; i < count; i++) {
            items[i]->displayInfo();
            items[i]->play();
        }
    }

    int getCount() const {
        return count;
    }
};

int main() {
    cout << "=== RECMIX PART 2 ===" << endl;

    // Create media objects
    Media* library[5];

    library[0] = new Song("Blinding Lights",
                          "The Weeknd", "Synth-pop");

    library[1] = new Podcast("Tech Talk",
                             "Alex Morgan", 12);

    library[2] = new Audiobook("The Time Machine",
                               "H. G. Wells",
                               "Taylor Brooks");

    library[3] = new Song("Levitating",
                          "Dua Lipa", "Pop");

    library[4] = new Podcast("Daily News",
                             "Jordan Lee", 8);

    int size = 5;

    // Function overloading demonstrations
    cout << "\n=== FUNCTION OVERLOADING ===" << endl;

    cout << "Searching for: Blinding Lights" << endl;

    int found = searchMedia(library, size,
                            "Blinding Lights");

    if (found != -1) {
        cout << "Found at index: " << found << endl;
    }

    cout << "\nSearching index: 2" << endl;

    Media* result = searchMedia(library, size, 2);

    if (result != nullptr) {
        cout << "Found: " << result->getTitle() << endl;
    }

    cout << "\nSearching index: 15" << endl;

    result = searchMedia(library, size, 15);

    if (result == nullptr) {
        cout << "Invalid index." << endl;
    }

    // Operator overloading demonstration
    cout << "\n=== OPERATOR OVERLOADING ===" << endl;

    cout << "Comparing media items..." << endl;

    if (*library[0] == *library[1]) {
        cout << "These items have the same title."
             << endl;
    }
    else {
        cout << "These items have different titles."
             << endl;
    }

    // Create a generic playlist
    cout << "\n=== FAVORITES PLAYLIST ===" << endl;

    Playlist<Media*> favorites;

    favorites.addItem(library[0]);
    favorites.addItem(library[1]);
    favorites.addItem(library[2]);
    favorites.addItem(library[3]);

    favorites.displayPlaylist();

    cout << "\nTotal playlist items: "
         << favorites.getCount() << endl;

    // Demonstrate a second template data type
    Playlist<Song*> songs;

    songs.addItem(static_cast<Song*>(library[0]));
    songs.addItem(static_cast<Song*>(library[3]));

    cout << "\nTotal songs in song playlist: "
         << songs.getCount() << endl;

    // Delete dynamically allocated objects once
    for (int i = 0; i < size; i++) {
        delete library[i];
    }

    return 0;
}