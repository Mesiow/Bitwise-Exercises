#pragma once
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
#include "Button.h"

/*


Write a C program to check Least Significant Bit (LSB) of a number is set or not. //Complete
Write a C program to check Most Significant Bit (MSB) of a number is set or not. //Complete
Write a C program to get nth bit of a number. //Complete
Write a C program to set nth bit of a number. //Complete
Write a C program to clear nth bit of a number.
Write a C program to toggle nth bit of a number.
Write a C program to get highest set bit of a number. //Complete
Write a C program to get lowest set bit of a number. //Complete
Write a C program to count trailing zeros in a binary number. //Complete
Write a C program to count leading zeros in a binary number. //Complete
Write a C program to flip bits of a binary number using bitwise operator.
Write a C program to count total zeros and ones in a binary number.
Write a C program to rotate bits of a given number. //Complete
Write a C program to convert decimal to binary number system using bitwise operator.
Write a C program to swap two numbers using bitwise operator.
Write a C program to check whether a number is even or odd using bitwise operator.


*/


// Override base class with your custom functionality
class BitwiseExercises : public olc::PixelGameEngine
{
public:
	BitwiseExercises()
	{
		srand((0));
		// Name your application
		sAppName = "Bitwise Exercises";
		input_ = "";
	
	}

public:
	// Called once at the start, so create things here
	bool OnUserCreate() override
	{
		generateBtn_ = new Button(ScreenWidth() - 105, ScreenHeight() - 25, 55, 15);
		generateBtn_->setString("Generate");

		notBtn_ = new Button(ScreenWidth() - 155, ScreenHeight() - 25, 45, 15);
		notBtn_->setString("~NOT");

		rotateRightBtn_ = new Button(ScreenWidth() - 245, ScreenHeight() - 25, 75, 15);
		rotateRightBtn_->setString("Rotate Right");

		rotateLeftBtn_ = new Button(ScreenWidth() - 245, ScreenHeight() - 45, 75, 15);
		rotateLeftBtn_->setString("Rotate Left");
		generatedNumber = generateNumber();

		return true;
	}

	//called once per frame
	bool OnUserUpdate(float fElapsedTime) override
	{

		//clear display
		Clear(olc::Pixel(0, 0, 255, 255)); //blue background
		
		checkInput();

		//draw
		drawBorder();
		drawButtons();

		//title
		DrawString(olc::vi2d(10, 10), "Bitwise Visualizations");
		drawBitwiseOperations();

		return true;
	}

	bool OnUserDestroy() override {
		delete generateBtn_;
		delete notBtn_;
		delete rotateRightBtn_;

		return true;
	}

	void checkInput() {

		olc::vi2d mousePos = GetMousePos();
	
		if (GetMouse(0).bPressed) { //left mouse pressed
			//bounding box of button
			if(generateBtn_->isInBounds(mousePos.x, mousePos.y)){
				//change color when clicked
				//generate new value 0 - 255
				generatedNumber = generateNumber();
				generateBtn_->setTextColor(olc::WHITE);
			}

			if (notBtn_->isInBounds(mousePos.x, mousePos.y)) {
				//flip bits of generated number
				flipBits();
				notBtn_->setTextColor(olc::WHITE);
			}

			if (rotateRightBtn_->isInBounds(mousePos.x, mousePos.y)) {
				generatedNumber = rotateBitsRight(generatedNumber);
				rotateRightBtn_->setTextColor(olc::WHITE);
			}

			if (rotateLeftBtn_->isInBounds(mousePos.x, mousePos.y)) {
				generatedNumber = rotateBitsLeft(generatedNumber);
				rotateLeftBtn_->setTextColor(olc::WHITE);
			}
		
			
		}

		if (GetMouse(0).bReleased) { //left mouse released
			generateBtn_->setTextColor(olc::DARK_GREY); //change color back after releasing
			notBtn_->setTextColor(olc::DARK_GREY);
			rotateRightBtn_->setTextColor(olc::DARK_GREY);
			rotateLeftBtn_->setTextColor(olc::DARK_GREY);
		}
	}


	//draw functions
	void drawBorder() {
		//top line
		DrawLine(5, 5, ScreenWidth() - 5, 5);
		//left line
		DrawLine(5, 5, 5, ScreenHeight() - 5);
		//right line
		DrawLine(ScreenWidth() - 5, 5, ScreenWidth() - 5, ScreenHeight() - 5);
		//bottom line
		DrawLine(5, ScreenHeight() - 5, ScreenWidth() - 5, ScreenHeight() - 5);
	}
	
	void drawButtons() {
		generateBtn_->draw(this); //pass in pointer to instance of this class for drawing
		notBtn_->draw(this);
		rotateRightBtn_->draw(this);
		rotateLeftBtn_->draw(this);
	}

	void drawBitwiseOperations() { //Draw operations of generated number
		//Draw number
		DrawString(10, 30, "Decimal: ");
		DrawString(75, 30, std::to_string(generatedNumber));

		//Draw Hexadecimal Representation
		DrawString(10, 50, "Hexadecimal:0x");
		DrawString(117, 50, toHex(generatedNumber));
		//Draw Binary Representation of the number
		DrawString(10, 70, "Binary: ");
		DrawString(70, 70, toBin(generatedNumber));

		//LSB
		DrawString(10, 90, "LSB: ");
		DrawString(50, 90, std::to_string(checkLSB(generatedNumber)));

		//MSB
		DrawString(10, 110, "MSB: ");
		DrawString(50, 110, std::to_string(checkMSB(generatedNumber)));

		//Highest order set bit
		int b = highestSetBit(generatedNumber);
		std::string s;
		if (b == -1)
			s = "None";
		else
			s = std::to_string(b);
		DrawStringDecal(olc::vf2d(10, 125), "Highest Order set bit pos: " + s, olc::WHITE, olc::vf2d(0.8, 0.8));
		

		//Lowest order set bit
		DrawStringDecal(olc::vf2d(10, 140), "Lowest Order set bit pos: " + std::to_string(lowestSetBit(generatedNumber)) , olc::WHITE, olc::vf2d(0.8, 0.8));

		//Trailing Zeros
		DrawStringDecal(olc::vf2d(10, 155), "# of Trailing Zeros: " + std::to_string(trailingZeros(generatedNumber)), olc::WHITE, olc::vf2d(0.8, 0.8));

		//Leading Zeros
		DrawStringDecal(olc::vf2d(10, 165), "# of Leading Zeros: " + std::to_string(leadingZeros(generatedNumber)), olc::WHITE, olc::vf2d(0.8, 0.8));
	}


	int generateNumber() {
		int ran = rand() % 255 + 0;
		return ran;
	}

	void flipBits() { //flip bits of current number
		for (int i = 0; i < 8; i++) {
			generatedNumber = (generatedNumber ^ (1 << i));
		}
	}

private:
	//Exercises
	std::string toBin(std::uint8_t val) { //takes in an 8 bit number and returns that number in binary form in a string
		std::string binary = "";
		for (int i = 7; i >= 0; i--) {
			if (i == 3) binary.push_back(' '); //make a space in between nibbles
			if ((val & (1 << i)) >= 1) { //bit is set
				binary.push_back('1');
			}
			else
				binary.push_back('0');
		}
		return binary;
	}

	std::string toHex(std::uint8_t val) { //converts val to hex, returns string equivalent
		int temp = val;
		char hex[50];

		int result;
		int i = 1;

		while (temp != 0) {
			result = temp % 16;
			if (result < 10)
				hex[i++] = result + 48;
			else
				hex[i++] = result + 55;

			temp = temp / 16; 
		}
		std::string hexValue;
		for (int j = i; j > 0; j--)
			hexValue.push_back(hex[j]);
		
		return hexValue;
	}
	
	//checks if lsb of a value is set or not, returns 1 or 0, 1 is set, 0 is not
	int checkLSB(std::uint8_t value) {
		return (value & 0x01);
	}

	int checkMSB(int value) {
		return ((value & 0x80) == 0 ? 0: 1);
	}

	//return 1 if nth bit is set, else 0
	std::uint8_t getNthBit(int value, int n) { //n - 1 so we can pass in 1 - 8 instead of 0 - 7
		return ((value & (1 << (n - 1))) == 0 ? 0 : 1);
	}

	//sets nth bit in value
	void setNthBit(int &value, int n) {
		value = (value | (1 << (n - 1)));
	}

	int highestSetBit(int number) { //returns bit position of highest set bit of the number
		int order = -1;
		for (int i = 0; i < 8; i++) { //loop over high nibble
			if ((number >> i) & 0x1) //if bit set found
				order = i; //bit position
		}
		return order;
	}

	int lowestSetBit(int number) { //returns bit position of lowest set bit of number
		int order = -1;
		for (int i = 0; i < 4; i++) {
			if ((number >> i) & 0x1) {
				order = i;
				break;
			}
		}
		return order;
	}

	int rotateBitsRight(int number) { //rotates bits of number to the right, returns new rotated number
		//save lsb value to put on the other side after rotation
		int lsb = (number & 0x1);
		int rotate = number >> 1; //rotate right by 1
		int rotatedNumber = (rotate | (lsb << 7)); //move lsb to msb position and merge the rotated number together

		return rotatedNumber;
	}

	int rotateBitsLeft(int number) {
		int msb = (number & 0x80);
		int rotate = number << 1; //rotate left
		int rotatedNumber = (rotate | (msb >> 7)) & 0xff; //merge, then mask out the 8 bits

		return rotatedNumber;
	}

	int trailingZeros(int number) { //counts number of trailing zeros in a binary number, returns number of trailing zeros
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if ((number & (1 << i)) == 0) { //found zero
				count++;
			}
			else
				break;
		}
		return count;
	}

	int leadingZeros(int number) { //returns number of leading zeros
		int count = 0;
		for (int i = 7; i >= 0; i--) {
			if ((number & (1 << i)) == 0) {
				count++;
			}
			else
				break;
		}
		return count;
	}

private:
	Button *generateBtn_; //generates new number
	Button* notBtn_; //flips bits
	Button* rotateRightBtn_; //rotates bits right by 1
	Button* rotateLeftBtn_;
	int generatedNumber = 0;

	std::string input_;
};