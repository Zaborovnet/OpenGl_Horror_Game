#include "PlayerState.h"

PlayerState::PlayerState() : stressLevel(0.0f) {}

void PlayerState::updateStress(float delta) {
  stressLevel += delta;
  if (stressLevel > maxStressLevel) {
      stressLevel = maxStressLevel; // Ограничиваем уровень стресса
    }
}

float PlayerState::getStress() const {
  return stressLevel;
}

bool PlayerState::isInDanger() const {
  return stressLevel > 75.0f; // Определяем, когда игрок в опасности
}
