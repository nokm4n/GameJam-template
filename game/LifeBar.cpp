#include "LifeBar.h"



LifeBar::LifeBar(String F)
{
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(50, 96, 166));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 59, 200));

	bar.setFillColor(Color(0, 0, 0));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
	max = 100;
}

void LifeBar::update(int k)// k-текущее здоровье

{
	if (k > 0)
		if (k < max)
			bar.setSize(Vector2f(20, (max - k) * 170 / max));//если не отрицательно и при этом меньше максимума, то устанавливаем новое значение (новый размер) для черного прямоугольника
}

void LifeBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//позиция на экране
	bar.setPosition(center.x - size.x / 2 + 30, center.y - size.y / 2 + 28);

	window.draw(s);//сначала рисуем полоску здоровья
	window.draw(bar);//поверх неё уже черный прямоугольник, он как бы покрывает её
}