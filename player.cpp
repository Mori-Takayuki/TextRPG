#include "player.h"
#include <cstdlib>
#include <iostream>

Player::Player(const std::string& name, const std::string& job)
    : name(name), job(job), level(1), experience(0), health(0), maxHealth(0), minAttack(0), maxAttack(0), dodgeRate(0.0) {
    if (job == "�E��") {
        health = maxHealth = 40;
        minAttack = 5;
        maxAttack = 8;
    }
    else if (job == "��m") {
        health = maxHealth = 50;
        minAttack = 3;
        maxAttack = 10;
        dodgeRate = 0.05;
    }
    else if (job == "������") {
        health = maxHealth = 30;
        minAttack = 4;
        maxAttack = 8;
        dodgeRate = 0.30;
    }
}

//�G��|���ƌo���l�l��
void Player::gainExperience(int amount) {
    experience += amount;
    while (experience >= 100) {
        levelUp();
    }
}

//���x���A�b�v
void Player::levelUp() {
    experience -= 100;
    level++;
    health = static_cast<int>(maxHealth * 1.2);
    maxHealth = health;
    maxAttack = static_cast<int>(minAttack * 1.2);
    minAttack = static_cast<int>(maxAttack * 1.2);
    std::cout << "���x���A�b�v!�v���C���[�̓��x��" << level << "�ɂȂ���!" << std::endl;
    std::cout << std::endl;
}

int Player::attack() {
    int attackPower = minAttack + rand() % (maxAttack - minAttack + 1);
    if (rand() % 100 < 1) { // 1%�̊m���ŃN���e�B�J��������
        attackPower *= 2;   //�U����2�{
        std::cout << "�N���e�B�J��!" << std::endl;
    }
    return attackPower;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

//�G��|���Ƒ̗͑S��
void Player::healToFull() {
    health = maxHealth;
    std::cout << "�̗͂��S�񕜂���!" << std::endl;
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
