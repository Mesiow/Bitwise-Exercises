#pragma once


class Button {
public:
	Button(int xpos, int ypos, int width, int height, olc::Pixel color = olc::BLACK,
		olc::Pixel textColor = olc::DARK_GREY) {
		this->buttonX = xpos;
		this->buttonY = ypos;
		this->w = width;
		this->h = height;

		this->buttonText = "";
		this->buttonColor = color;
		this->buttonTextColor = textColor;

	}

	void draw(olc::PixelGameEngine *pge) {
		//draw
		pge->FillRect(buttonX, buttonY, w, h, buttonColor);
		pge->DrawStringDecal(olc::vf2d(buttonX + 6, buttonY + h / 2.6), buttonText, buttonTextColor, olc::vf2d(0.7, 0.7));
	}


public:
	bool isInBounds(int x, int y) { //returns true if coordinates are within bounds of button
		return ((x >= buttonX && x <= buttonX + w) 
			&& (y >= buttonY && y <= buttonY + h));
	}

	void setString(const std::string& str) {
		this->buttonText = str;
	}

	void setTextColor(olc::Pixel color) {
		buttonTextColor = color;
	}

public:
	int getX()const { return this->buttonX; } //get x position
	int getY()const { return this->buttonY; } //get y position
	int getWidth()const { return this->w; }
	int getHeight()const { return this->h; }

private:
	int buttonX;
	int buttonY;
	int w = 70, h = 20;

	olc::Pixel buttonColor;
	olc::Pixel buttonTextColor;
	std::string buttonText;
};