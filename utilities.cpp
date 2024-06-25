#include "utilities.h"


Monster createNextMonster(int index) {
    switch (index) {
    case 0:
        return Monster("スライム", 20, 3, 5, 0.05, "たいあたり");//("敵名",体力,最小・最大攻撃力,回避率,"技名")
    case 1:
        return Monster("ゴブリン", 30, 5, 7, 0.10, "ゴブリンパンチ");
    case 2:
        return Monster("ゴーレム", 60, 7, 10, 0.00, "岩石おとし");
    case 3:
        return Monster("あくまのきし", 50, 7, 10, 0.30, "なぎはらい");
    case 4:
        return Monster("魔王", 100, 10, 15, 0.30, "あくのはどう");
    default:
        return Monster("Unknown", 0, 0, 0, 0.0, "Unknown");
    }
}

