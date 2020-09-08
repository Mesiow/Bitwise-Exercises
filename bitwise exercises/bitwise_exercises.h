#pragma once
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
#include "Bitmanipulation_buttons.h"

/*


Write a C program to check Least Significant Bit (LSB) of a number is set or not. //Complete
Write a C program to check Most Significant Bit (MSB) of a number is set or not. //Complete
Write a C program to get nth bit of a number. //Complete
Write a C program to set nth bit of a number. //Complete
Write a C program to clear nth bit of a number. //Complete
Write a C program to toggle nth bit of a number. //Complete
Write a C program to get highest set bit of a number. //Complete
Write a C program to get lowest set bit of a number. //Complete
Write a C program to count trailing zeros in a binary number. //Complete
Write a C program to count leading zeros in a binary number. //Complete
Write a C program to flip bits of a binary number using bitwise operator. //Complete
Write a C program to count total zeros and ones in a binary number. //Complete
Write a C program to rotate bits of a given number. //Complete
Write a C program to convert decimal to binary number system using bitwise operator. //Complete
Write a C program to swap two numbers using bitwise operator. //Complete
Write a C program to check whether a number is even or odd using bitwise operator. //Complete


*/


// Override base class with your custom functionality
class BitwiseExercises : public olc::PixelGameEngine
{
public:
	BitwiseExercises()
		:buttons_(this)
	{
		srand(time(NULL));
		// Name your application
		sAppName = "Bitwise Exercises";
		input_ = "";
	

		int a = 62;
		int b = 43;
		std::cout << "a = " << a;
		std::cout << "  b = " << b << std::endl;
		std::cout << "Swapped" << std::endl;
		swap(a, b);
		std::cout << "a = " << a;
		std::cout << "  b = " << b << std::endl;

		int a = 94;
		if (isOdd(a))
			std::cout << a << " is odd" << std::endl;
		else
			std::cout << a << " is even" << std::endl;

	}

public:
	// Called once at the start, so create things here
	bool OnUserCreate() override
	{
		

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
		

		return true;
	}

	void checkInput() {

		olc::vi2d mousePos = GetMousePos();
	
	
		if (GetMouse(0).bPressed) { //left mouse pressed
			//bounding box of button
			//Generate btn
			if(buttons_.generateBtn_->isInBounds(mousePos.x, mousePos.y)){
				//change color when clicked
				//generate new value 0 - 255
				generatedNumber = generateNumber();
				buttons_.generateBtn_->setTextColor(olc::WHITE);
			}

			//~NOT btn
			if (buttons_.notBtn_->isInBounds(mousePos.x, mousePos.y)) {
				//flip bits of generated number
				flipBits();
				buttons_.notBtn_->setTextColor(olc::WHITE);
			}

			//Rotate btns
			if (buttons_.rotateRightBtn_->isInBounds(mousePos.x, mousePos.y)) {
				generatedNumber = rotateBitsRight(generatedNumber);
				buttons_.rotateRightBtn_->setTextColor(olc::WHITE);
			}

			if (buttons_.rotateLeftBtn_->isInBounds(mousePos.x, mousePos.y)) {
				generatedNumber = rotateBitsLeft(generatedNumber);
				buttons_.rotateLeftBtn_->setTextColor(olc::WHITE);
			}

			//Toggle btn
			if (buttons_.toggleBtn_->isInBounds(mousePos.x, mousePos.y)) {
				toggleNthBit(generatedNumber, 7); //hard coded value for now
				buttons_.toggleBtn_->setTextColor(olc::WHITE);
		   }

			//Clear btn
			if (buttons_.clearBtn_->isInBounds(mousePos.x, mousePos.y)) {
				clearNthBit(generatedNumber, 6);
				buttons_.clearBtn_->setTextColor(olc::WHITE);
			}
		
			
		}

		if (GetMouse(0).bReleased) { //left mouse released
			buttons_.resetColor();
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
		buttons_.draw(this); //pass in pointer to instance of this class for drawing
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

		//Total number of ones and zeros in binary number
		DrawStringDecal(olc::vf2d(10, 180), "Total # of Zeros: " + std::to_string(totalZeros(generatedNumber)), olc::WHITE, olc::vf2d(0.8, 0.8));
		DrawStringDecal(olc::vf2d(10, 195), "Total # of Ones: " + std::to_string(totalOnes(generatedNumber)), olc::WHITE, olc::vf2d(0.8, 0.8));
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

	void toggleNthBit(int& value, int n) {
		value = (value ^ (1 << (n - 1)));
	}

	void clearNthBit(int& value, int n) {
		value = (value & ~(1 << (n - 1))); //clear bit at position n - 1
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

	int totalZeros(int value) { //returns total amount of zeros in binary number
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if ((value & (1 << i)) == 0)
				count++;
		}
		return count;
	}

	int totalOnes(int value) { //returns total amount of ones in binary number
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if (value & (1 << i))
				count++;
		}
		return count;
	}



	void swap(int& v1, int &v2) { //swap two numbers using a bitwise AND and OR operator
		int temp = v1; //hold v1

		//assign v1 to v2 via bit operators
		for (int i = 0; i < 8; i++) { //loop over first value and store the value bit by bit into temp1
			int bit_v2 = (v2 & (1 << i));
			v1 = (v1 | bit_v2);  //merge v1 to v2's value bit by bit
			v1 &= v2; //mask out to get original value of v2
		}

		//assign v2 to v1 via bit operators
		for (int i = 0; i < 8; i++) {
			int bit_v1 = (temp & (1 << i)); //get v1's original bit value
			v2 = (v2 | bit_v1); //merge v1 value to v2
			v2 &= temp; //mask out to get original value of v1
		}
	}

	//Least Significant Bit of an odd number is always set (1).
	//To check whether a number is even or odd we need to figure out if LSB is set or not.
	bool isOdd(int number) { //checks if number is odd using bitwise operators
		return ((number & 0x1));
	}

private:
	BitManipButtons buttons_;

	int generatedNumber = 0;
	std::string input_;
};