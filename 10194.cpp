#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

struct Team {
    string name;
    int points;
    int wins;
    int ties;
    int losses;
    int goalsScored;
    int goalsAgainst;
    int gamesPlayed;

    Team() {
        points = 0;
        wins = 0;
        ties = 0;
        losses = 0;
        goalsScored = 0;
        goalsAgainst = 0;
        gamesPlayed = 0;
    }
    Team(string name_): name(name_) {}

    bool operator< (const Team& other) const {
        if(points > other.points)       return true;
        else if (other.points > points) return false;
        else {
            if(wins > other.wins)       return true;
            else if (other.wins > wins) return false;
            else {
                if(goalsScored-goalsAgainst > other.goalsScored-other.goalsAgainst)       return true;
                else if (other.goalsScored-other.goalsAgainst > goalsScored-goalsAgainst) return false;
                else {
                    if(goalsScored > other.goalsScored)       return true;
                    else if (other.goalsScored > goalsScored) return false;
                    else {
                        if(gamesPlayed < other.gamesPlayed)       return true;
                        else if (other.gamesPlayed < gamesPlayed) return false;
                        else {
                            string n1 =  name;
                            transform(name.begin(), name.end(), n1.begin(), ::tolower);
                            string n2 = other.name;
                            transform(other.name.begin(), other.name.end(), n2.begin(), ::tolower);
                            return n1 < n2;
                        }
                    }
                }
            }
        }
    }

    void print() {
        printf("%s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                name.c_str(),
                points,
                gamesPlayed,
                wins,
                ties,
                losses,
                goalsScored-goalsAgainst,
                goalsScored,
                goalsAgainst
            );
    }
};

int getTeamIndex(vector<Team>& teams, string n1) {
    for(int i = 0 ; i < teams.size(); i++) {
        if(teams[i].name == n1) return i;
    }
    return 0;
}

int main() {

    int cases;
    scanf("%d\n", &cases);
    for(int k = 0 ; k < cases; k++) {
        string tName;

        getline(cin, tName);
        int numT, numGames;
        scanf("%d\n", &numT);
        std::vector<Team> teams(numT);
        for(int i = 0; i < numT; i++) {
            getline(cin, teams[i].name);
        }

        scanf("%d\n", &numGames);
        string s, n1, n2, aux;
        int g1, g2;
        int index;
        for(int i = 0; i < numGames; i++) {
            getline(cin, s);
            index = s.find("#");
            n1 = s.substr(0, index);
            s = s.substr(index+1);
            index = s.find("@");
            aux = s.substr(0, index);
            g1 = atoi(aux.c_str());
            s = s.substr(index+1);
            index = s.find("#");
            aux = s.substr(0, index);
            g2 = atoi(aux.c_str());
            n2 = s.substr(index+1);

            int ind1 = getTeamIndex(teams, n1);
            int ind2 = getTeamIndex(teams, n2);

            teams[ind1].goalsScored += g1;
            teams[ind2].goalsScored += g2;

            teams[ind1].goalsAgainst += g2;
            teams[ind2].goalsAgainst += g1;

            teams[ind1].gamesPlayed ++;
            teams[ind2].gamesPlayed ++;

            if (g1 > g2) {
                teams[ind1].wins ++;
                teams[ind2].losses ++;
                teams[ind1].points += 3;

            } else if (g2 > g1) {
                teams[ind2].wins ++;
                teams[ind1].losses ++;
                teams[ind2].points += 3;
            } else {
                teams[ind1].points += 1;
                teams[ind2].points += 1;
                teams[ind1].ties ++;
                teams[ind2].ties ++;
            }

        }

        sort(teams.begin(), teams.end());
        if(k != 0) printf("\n");
        printf("%s\n", tName.c_str());
        for(int i = 0; i < teams.size(); i++) {
            printf("%d) ", i+1);
            teams[i].print();
        }
    }
}
