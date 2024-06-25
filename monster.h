#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
public:
    Monster(const std::string& name, int health, int minAttack, int maxAttack, double dodgeRate, const std::string& specialMove);
    std::string getName() const;
    int getHealth() const;
    bool isAlive() const;
    int attack();
    void takeDamage(int damage);
    std::string getSkillName() const;
    bool dodge() const;

private:
    std::string name;
    int health;
    int minAttack;
    int maxAttack;
    double dodgeRate;
    std::string specialMove;
    std::string skillName;
};

#endif // MONSTER_H
