
# OpenGL Horror Game

![Current Screenshot](https://github.com/user-attachments/assets/eda289ed-fe3e-4b77-86a9-239f457e24cb)

**Хоррор в стиле PSX** с полностью процедурным контентом.  
Все модели, текстуры и звуки генерируются кодом в реальном времени.

## 📦 Технологии
- **Ядро:** C++11, Qt 5.14
- **Рендеринг:** OpenGL 3.3, GLFW 3.3, GLM
- **Сборка:** QMake
- **Особенности:** 
  - CRT-эффекты с дизерингом
  - Динамическое освещение
  - Low-poly геометрия (до 32 полигонов на объект)

## 🎮 Управление
- **Действие**	Клавиши
- **Движение**	WASD
- **Камера**	ЛКМ + мышь
- **Прыжок**	Пробел

  
## ✅ Реализовано

  **Генерация текстур стен/пола**

  **Базовая система передвижения**

  **Процедурное мерцание освещения**

  **CRT-постобработка**

  **Система прыжков и гравитации**

  **Простейшие коллизии**

## 🚧 Roadmap

  **v0.2 (Текущие цели):**



  **v0.3:**



  **v1.0:**

## 🚀 Установка
```bash
git clone https://github.com/Zaborovnet/OpenGl_Horror_Game.git
cd OpenGl_Horror_Game
qmake && make -j4
./NightStoreHorror
```

