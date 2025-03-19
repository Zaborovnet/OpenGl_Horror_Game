#pragma once

class PlayerState {
public:
  PlayerState();

  void updateStress(float delta);
  float getStress() const;
  bool isInDanger() const;

private:
  float stressLevel; // Уровень стресса
  const float maxStressLevel = 100.0f; // Максимальный уровень стресса
};
