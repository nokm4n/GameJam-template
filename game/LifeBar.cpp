#include "LifeBar.h"



LifeBar::LifeBar(String F)
{
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(50, 96, 166));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 59, 200));

	bar.setFillColor(Color(0, 0, 0));//������ ������������� ������������� ������ � ���������� ������ ���������� ��������
	max = 100;
}

void LifeBar::update(int k)// k-������� ��������
{
	if (k < max && k > 0)
		bar.setSize(Vector2f(20, (max - k) * 170 / max));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
}

void LifeBar::draw(RenderWindow& window, float scale)
{
	s.setScale(scale, scale);
	bar.setScale(scale, scale);
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition((center.x  - size.x / 2 + 10*scale), (center.y  - size.y / 2 + 10*scale));//������� �� ������
	bar.setPosition(center.x - size.x / 2 + 30*scale, center.y - size.y / 2 + 28*scale);

	window.draw(s);//������� ������ ������� ��������
	window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
}