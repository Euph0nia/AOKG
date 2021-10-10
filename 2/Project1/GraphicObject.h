#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

class GraphicObject
{
private:
	// Позиция и угол поворота для объекта
	Glfloat position[3];
	Glfloat angle;
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	Glfloat modelMatrix[16];
	// Цвет модели
	Glfloat color[3];
public:
	// Конструктор
	GraphicObject(void);
	// Задать позицию объекта
	void setPosition(float x, float y, float z);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setСolor(float r, float g, float b);
	// Вывести объект
	void draw(void);
};

#endif