#include "./headers/D15box.h"


D15box::D15box(){}

void D15box::insertOrUpdate(D15lense l) {
	bool broke = false;
	for (int i = 0; i < this->lenses.size(); ++i) {
		//if we find a matching label, update it
		if (l.getLabel() == this->lenses[i].getLabel()) {
			this->lenses[i].setFocalLength(l.getFocalLength()); 
			broke = true;
			break;
		}
	}
	//there wasnt a matching label
	//insert the lense into the box
	if (!broke) { this->lenses.push_back(l); }
}


void D15box::remove(std::string label) {
	for(int i = 0; i < this->lenses.size(); ++i){
		//if the label is the same, removes it from box.
		if (this->lenses[i].getLabel() == label) {
			this->lenses.erase(this->lenses.begin() + i);
			return; //there should only be 1 lense with a label.
		}
	}
}

int D15box::getBoxPower() {
	int boxPower = 0;
	for (int i = 0; i < this->lenses.size(); ++i) {
		boxPower += (i+1) * this->lenses[i].getFocalLength();
	}
	return boxPower;
}