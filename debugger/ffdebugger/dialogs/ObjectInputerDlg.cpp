#include "ObjectInputerDlg.h"
#include "FFCustomGui.h"
#include "utils/string_util.hpp"
#include "utils/FFSpyClient.h"

using namespace ci;
using namespace ci::app;

ObjectInputerDlg::ObjectInputerDlg(ci::app::WindowRef window) :
	FFDialog("Add object", 300, 300, window) {
	pretzel::PretzelGuiRef nativeDlg = getNative();

	_objectTypes = { "OpenCV Mat", "OpenCV Rect", "OpenCV Contour" };
	_sortTypes = { "AsIs", "PointCountIncrease", "PointCountDecrease", "AreaIncrease", "AreaDecrease" };
	_pointArrayTypes = {"polygon", "point array"};

	nativeDlg->addTextField("Address", &_objectAddress, true);
	nativeDlg->addEnum("Object type", &_objectTypes, &_objectTypeIdx);
	nativeDlg->addButton("Add", &ObjectInputerDlg::onAddObjectButtonPress, this);
	nativeDlg->addButton("Close", &FFDialog::onClose, (FFDialog*)this);
	nativeDlg->addEnum("Contour sort type", &_sortTypes, &_sortTypeIdx);
	nativeDlg->addEnum("points array types", &_pointArrayTypes, &_pointArrayTypeIdx);
	nativeDlg->loadSettings();
}

ObjectInputerDlg::~ObjectInputerDlg() {}

int ObjectInputerDlg::getSelectedTypeIndex() const {
	return _objectTypeIdx;
}

int ObjectInputerDlg::getPointArrayTypeIndex() const {
	return _pointArrayTypeIdx;
}

ObjectInputerDlg& ObjectInputerDlg::setSelectedTypeIndex(int idx) {
	_objectTypeIdx = idx;
	return *this;
}

void ObjectInputerDlg::onAddObjectButtonPress() {
	if (_onAddObjectBtnClick) {
		_onAddObjectBtnClick(this);
	}
}

void* ObjectInputerDlg::getObjectAddress() const {
	return convertToAddress(_objectAddress);
}

void* ObjectInputerDlg::convertToAddress(const std::string& address) {
	auto str = address;
	trim(str);
	if (str.find("0x", 0, 2) == 0) {
		str = str.substr(2);
	}

	// check if str is in hexa fromat
	//auto c = str.c_str();
	//auto end = c + str.size();
	//while (c < end) {
	//	if (isdigit(*c) == 0) {
	//		break;
	//	}
	//	c++;
	//}

	//// if the while loop is not run to the end
	//if (c != end) {

	//}

	// try to convert hexa string first
	char * p;
	auto number = strtoull(str.c_str(), &p, 16);
	if (*p != 0) {
		// not a hexa string, try with decimal string
		number = strtoull(str.c_str(), &p, 10);
		if (*p != 0) {
			return nullptr;
		}
	}

	// invaid pointer address in x86 platform
	if (sizeof(void*) == 4 && number > 0xFFFFFFFF) {
		return nullptr;
	}

	// invaid pointer address in x64 platform
	//if (sizeof(void*) == 8 && number < 0x100000000) {
	//	return nullptr;
	//}

	return (void*)number;
}

ObjectInputerDlg& ObjectInputerDlg::setObjectAddress(void* address) {
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(sizeof(address) * 2)
		<< std::hex << address;
	_objectAddress = ss.str();
	return *this;
}


ButtonClickEventHandler& ObjectInputerDlg::getAddObjectButtonSignal() {
	return _onAddObjectBtnClick;
}