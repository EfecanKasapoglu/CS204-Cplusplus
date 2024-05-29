#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

bool gemefinish=false;
bool correctnumberguess=false;
int correctnumber;
mutex generalmutex;
vector<int> score;
int iduser=-1;
mutex coutmutex;
bool newgame=false;

void printtime() { // This function prints the current time
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); //Gets the current time period
    struct tm *ptm = localtime(&tt);
    cout<<put_time(ptm, "%X") << endl;
}
int randomNumber(const int& randomRangeStart,const int& randomRangeEnd){// this function generates number in the given range. This is also in the lecture slide+recitation
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(randomRangeStart, randomRangeEnd);
    return distribution(generator);
}

void host(const int randomRangeStart,const int randomRangeEnd,const int numberOfRounds){
    for (int x=1;x<=numberOfRounds;x++){
        generalmutex.lock();
        iduser=-1;
        correctnumberguess=false;
        correctnumber=randomNumber(randomRangeStart,randomRangeEnd);
        newgame=true;
        coutmutex.lock();
        if(x!=1){
            cout<<"Round "<<x<< " started at: ";
            printtime();
            cout<<"Target is "<<correctnumber<<endl<<endl;
            generalmutex.unlock();
        }
        else{
            cout<<"Game started at: ";
            printtime();
            cout<<"Round "<<x<<" will start 3 seconds later"<<endl;
            cout<<endl;
            cout<<"Target is "<<correctnumber<<endl<<endl;
            this_thread::sleep_for(chrono::seconds(3));
            generalmutex.unlock();
        }
        coutmutex.unlock();
        while(!correctnumberguess){
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        generalmutex.lock();
        score[iduser]++;
        newgame = false;
        generalmutex.unlock();
    }
    generalmutex.lock();
    gemefinish=true;
    generalmutex.unlock();
}

void player(const int randomRangeStart, const int randomRangeEnd, int id) {
    bool continues=true;
    while(continues){
        this_thread::sleep_for(chrono::seconds(1));
        generalmutex.lock();
        if(gemefinish){
            generalmutex.unlock();
            continues=false;
        }
        if(!newgame){
            generalmutex.unlock();
        }
        generalmutex.unlock();
        int guess=randomNumber(randomRangeStart, randomRangeEnd);
        generalmutex.lock();
        if(guess==correctnumber && !correctnumberguess){
            correctnumberguess=true;
            iduser=id;
            generalmutex.unlock();
            coutmutex.lock();
            cout<<"Player with id "<<id<<" guessed "<<guess<<" correctly at: ";
            printtime();
            cout<<endl;
            coutmutex.unlock();
        }
        generalmutex.unlock();
        coutmutex.lock();
        if(!correctnumberguess){
            cout<<"Player with id "<<id<<" guessed "<<guess<< " incorrectly at: ";
            printtime();
        }
        coutmutex.unlock();
    }
}

int main() {
    int numberOfPlayers, numberOfRounds, randomRangeStart, randomRangeEnd;

    do{
        cout<<"Please enter number of players: ";
        cin>>numberOfPlayers;
        if(numberOfPlayers<=0){
            cout<<"Number of players cannot be lower than 1!"<<endl;
        }
    } while(numberOfPlayers<=0);

    do{
        cout<<"Please enter number of rounds: ";
        cin>>numberOfRounds;
        if(numberOfRounds<=0){
            cout<<"Number of rounds cannot be lower than 1!"<<endl;
        }
    }while(numberOfRounds<=0);

    do{
        cout<<"Please enter the randomization range: ";
        cin>>randomRangeStart>>randomRangeEnd;
        if(randomRangeStart>randomRangeEnd){
            cout<<"Lower bound has to be smaller than or equal to higher bound"<<endl;
        }
    }while(randomRangeStart>randomRangeEnd);

    cout<<endl<<endl;
    cout<<"---------------------------------------------------"<<endl;
    for(int x=0;x<numberOfPlayers;x++){
        score.push_back(0);
    }
    vector<thread> gameplayers(numberOfPlayers);
    for(int x=0;x<numberOfPlayers;x++){
        gameplayers[x]=thread(player,randomRangeStart,randomRangeEnd,x);
    }
    thread hostT(host,randomRangeStart,randomRangeEnd,numberOfRounds);
    hostT.join();
    for(int x=0;x<gameplayers.size();x++){
        gameplayers[x].join();
    }
    cout<<"Game is over!"<<endl;
    cout<<"Leaderboard:"<<endl;
    for(int x=0;x<numberOfPlayers;x++){
        cout<<"Player "<<x<<" has won "<<score[x]<<" times"<<endl;
    }
    return 0;
}
