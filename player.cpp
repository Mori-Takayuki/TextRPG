#include "player.h"
#include <cstdlib>
#include <iostream>

Player::Player(const std::string& name, const std::string& job)
    : name(name), job(job), level(1), experience(0), health(0), maxHealth(0), minAttack(0), maxAttack(0), dodgeRate(0.0) {
    if (job == "勇者") {
        health = maxHealth = 40;
        minAttack = 5;
        maxAttack = 8;
    }
    else if (job == "戦士") {
        health = maxHealth = 50;
        minAttack = 3;
        maxAttack = 10;
        dodgeRate = 0.05;
    }
    else if (job == "武闘家") {
        health = maxHealth = 30;
        minAttack = 4;
        maxAttack = 8;
        dodgeRate = 0.30;
    }
}

//敵を倒すと経験値獲得
void Player::gainExperience(int amount) {
    experience += amount;
    while (experience >= 100) {
        levelUp();
    }
}

//レベルアップ
void Player::levelUp() {
    experience -= 100;
    level++;
    health = static_cast<int>(maxHealth * 1.2);
    maxHealth = health;
    maxAttack = static_cast<int>(minAttack * 1.2);
    minAttack = static_cast<int>(maxAttack * 1.2);
    std::cout << "レベルアップ!プレイヤーはレベル" << level << "になった!" << std::endl;
    std::cout << std::endl;
}

int Player::attack() {
    int attackPower = minAttack + rand() % (maxAttack - minAttack + 1);
    if (rand() % 100 < 1) { // 1%の確率でクリティカルが発生
        attackPower *= 2;   //攻撃力2倍
        std::cout << "クリティカル!" << std::endl;
    }
    return attackPower;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

//敵を倒すと体力全回復
void Player::healToFull() {
    health = maxHealth;
    std::cout << "体力が全回復した!" << std::endl;
}

std::string Player::getName() const {
    return name;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

bool Player::isAlive() const {
    return health > 0;
}

bool Player::dodge() const {
    return rand() / (RAND_MAX + 1.0) < dodgeRate;
}
