/*
 * Conversions.h
 *
 *  Created on: Nov 14, 2018
 *      Author: jack
 */

#ifndef GTKHPP_CONVERSIONS_H_
#define GTKHPP_CONVERSIONS_H_

#include "gtk_include.h"
#include "Widget.h"
#include "Container.h"
#include "Button.h"
#include "Entry.h"
#include "Menu.h"

namespace gtk {

//Button*toButton(Widget*w){
//	Button*b=new Button();
//	b->widget=GTK_BUTTON(w->widget);
//	return b;
//}

inline Button*button(void*w){
	return static_cast<Button*>(w);
}

inline Entry*entry(void*w){
	return static_cast<Entry*>(w);
}

inline Label*label(void*w){
	return static_cast<Label*>(w);
}

inline Menu*menu(void*w){
	return static_cast<Menu*>(w);
}

};


#endif /* GTKHPP_CONVERSIONS_H_ */
