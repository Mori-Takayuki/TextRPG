#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name, const std::string& job);
    void gainExperience(int amount);
    void levelUp();
    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;
    int attack();
    void takeDamage(int damage);
    void healToFull();
    bool dodge() const;

private:
    std::string name;
    std::string job;
    int level;
    int experience;
    int health;
    int maxHealth;
    int minAttack;
    int maxAttack;
    double dodgeRate;
    std::string specialMove;
};

#endif // PLAYER_H
