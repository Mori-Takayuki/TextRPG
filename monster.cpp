#include "monster.h"
#include <cstdlib>

Monster::Monster(const std::string& name, int health, int minAttack, int maxAttack, double dodgeRate, const std::string& specialMoveconst)
    : name(name), health(health), minAttack(minAttack), maxAttack(maxAttack), dodgeRate(dodgeRate), specialMove(specialMove){}

std::string Monster::getName() const {
    return name;
}

int Monster::getHealth() const {
    return health;
}

bool Monster::isAlive() const {
    return health > 0;
}

int Monster::attack() {
    return minAttack + rand() % (maxAttack - minAttack + 1);
}

void Monster::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

bool Monster::dodge() const {
    return rand() / (RAND_MAX + 1.0) < dodgeRate;
}

std::string Monster::getSkillName() const {
    return skillName;
}
