#include "bitwise_exercises.h"


int main() {

	BitwiseExercises e;
	if (e.Construct(256, 256, 3, 3))
		e.Start();
	return 0;
	
}

char getCharFromKey(olc::Key key) {
	switch (key) {
	case olc::Key::A: return 'A';
	case olc::Key::B: return 'B';
	case olc::Key::C: return 'C';
	case olc::Key::D: return 'D';
	case olc::Key::E: return 'E';
	case olc::Key::F: return 'F';
	case olc::Key::G: return 'G';
	case olc::Key::H: return 'H';
	case olc::Key::I: return 'I';
	case olc::Key::J: return 'J';
	case olc::Key::K: return 'K';
	case olc::Key::L: return 'L';
	case olc::Key::M: return 'M';
	case olc::Key::N: return 'N';
	case olc::Key::O: return 'O';
	case olc::Key::P: return 'P';
	case olc::Key::Q: return 'Q';
	case olc::Key::R: return 'R';
	case olc::Key::S: return 'S';
	case olc::Key::T: return 'T';
	case olc::Key::U: return 'U';
	case olc::Key::V: return 'V';
	case olc::Key::W: return 'W';
	case olc::Key::X: return 'X';
	case olc::Key::Y: return 'Y';
	case olc::Key::Z: return 'Z';
	case olc::Key::K0: return '0';
	case olc::Key::K1: return '1';
	case olc::Key::K2: return '2';
	case olc::Key::K3: return '3';
	case olc::Key::K4: return '4';
	case olc::Key::K5: return '5';
	case olc::Key::K6: return '6';
	case olc::Key::K7: return '7';
	case olc::Key::K8: return '8';
	case olc::Key::K9: return '9';
	}
}