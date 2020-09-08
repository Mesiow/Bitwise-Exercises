#pragma once
#include "olcPixelGameEngine.h"
#include "Button.h"


struct BitManipButtons {
	BitManipButtons(olc::PixelGameEngine *pge) {
		//Create Buttons
		generateBtn_ = new Button(pge->ScreenWidth() - 105, pge->ScreenHeight() - 10, 55, 15);
		generateBtn_->setString("Generate");

		notBtn_ = new Button(pge->ScreenWidth() - 155, pge->ScreenHeight() - 10, 45, 15);
		notBtn_->setString("Flip");

		rotateRightBtn_ = new Button(pge->ScreenWidth() - 245, pge->ScreenHeight() - 30, 75, 15);
		rotateRightBtn_->setString("Rotate Right");

		rotateLeftBtn_ = new Button(pge->ScreenWidth() - 245, pge->ScreenHeight() - 10, 75, 15);
		rotateLeftBtn_->setString("Rotate Left");

		toggleBtn_ = new Button(pge->ScreenWidth() - 155, pge->ScreenHeight() - 30, 45, 15);
		toggleBtn_->setString("Toggle");

		clearBtn_ = new Button(pge->ScreenWidth() - 105, pge->ScreenHeight() - 30, 45, 15);
		clearBtn_->setString("Clear");
	}

	~BitManipButtons() {
		delete generateBtn_;
		delete notBtn_;
		delete rotateRightBtn_;
		delete rotateLeftBtn_;
		delete toggleBtn_;
	}

	void draw(olc::PixelGameEngine* pge) {
		generateBtn_->draw(pge);
		notBtn_->draw(pge);
		rotateRightBtn_->draw(pge);
		rotateLeftBtn_->draw(pge);
		toggleBtn_->draw(pge);
		clearBtn_->draw(pge);
	}

	void resetColor() {
		generateBtn_->setTextColor(olc::DARK_GREY); //change color back after releasing
		notBtn_->setTextColor(olc::DARK_GREY);
		rotateRightBtn_->setTextColor(olc::DARK_GREY);
		rotateLeftBtn_->setTextColor(olc::DARK_GREY);
		toggleBtn_->setTextColor(olc::DARK_GREY);
		clearBtn_->setTextColor(olc::DARK_GREY);
	}

	Button* generateBtn_; //generates new number
	Button* notBtn_; //flips bits
	Button* rotateRightBtn_; //rotates bits right by 1
	Button* rotateLeftBtn_; //rotates bits left by 1
	Button* toggleBtn_; //toggles a bit
	Button* clearBtn_; //clears a bit
};