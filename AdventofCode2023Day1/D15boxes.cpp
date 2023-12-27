#include "./headers/D15boxes.h"


D15boxes::D15boxes() {
	this->boxes = std::vector<D15box>(256);
}

int D15boxes::decideBox(std::string label) {
	//hash the label, will be between 0-255
	int current = 0;
	for (char c : label) {
		current += c - 0;
		current *= 17;
		current %= 256;
	}
	return current;
}

void D15boxes::insertOrUpdate(D15lense l) {
	int a = this->decideBox(l.getLabel());
	this->boxes[a].insertOrUpdate(l);
}

void D15boxes::remove(std::string label) {
	int a = this->decideBox(label);
	this->boxes[a].remove(label);
}

int D15boxes::calcFocalPower() {
	int totalPower = 0;
	for (int i = 0; i < this->boxes.size(); ++i) {
		int boxPower = i + 1;
		boxPower *= this->boxes[i].getBoxPower();
		totalPower += boxPower;
	}
	return totalPower;
}