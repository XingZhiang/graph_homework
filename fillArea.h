#pragma once
#ifndef GRAPH_LAB_FILL_H
#define GRAPH_LAB_FILL_H
#include "Point.h"
#include <stack>
#include <vector>


void fillArea(Point& p, COLOR newcolor) {
	COLOR oldcolor = p.getColor();
	if (oldcolor == newcolor)
		return;
	Point seed = p;
	std::stack<Point> p_stack;
	bool spanNeedFill;
	int xr, xl;
	p_stack.push(seed);
	while (!p_stack.empty()) {
		seed = p_stack.top();
		p_stack.pop();
		Point temp(seed);
		while (!temp.isValid() && temp.getColor() == oldcolor) {
			setPixel(temp.x, temp.y, newcolor);
			temp.x++;
		}
		xr = temp.x - 1;
		temp.x = seed.x - 1;
		while (!temp.isValid() && temp.getColor() == oldcolor) {
			setPixel(temp.x, temp.y, newcolor);
			temp.x--;
		}
		xl = temp.x + 1;
		temp.x = xl;
		temp.y++;
		if (temp.isValid())
			continue;
		while (temp.x < xr) {
			spanNeedFill = false;
			while (!temp.isValid() && temp.getColor() == oldcolor) {
				spanNeedFill = true;
				temp.x++;
			}
			if (spanNeedFill) {
				seed.x = temp.x - 1;
				seed.y = temp.y;
				p_stack.push(seed);
				spanNeedFill = false;
			}
			while (temp.getColor() != oldcolor && temp.x < xr)
				temp.x++;

		}
		temp.x = xl;
		temp.y -= 2;
		if (temp.isValid())
			continue;
		while (temp.x < xr) {
			spanNeedFill = false;
			while (!temp.isValid() && temp.getColor() == oldcolor) {
				spanNeedFill = true;
				temp.x++;
			}
			if (spanNeedFill) {
				seed.x = temp.x - 1;
				seed.y = temp.y;
				p_stack.push(seed);
				spanNeedFill = false;
			}
			while (temp.getColor() != oldcolor && temp.x < xr)
				temp.x++;

		}
	}
	return;
}
 
#endif //GRAPH_LAB_FILL_H
