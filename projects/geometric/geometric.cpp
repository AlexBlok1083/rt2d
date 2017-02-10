/**
 * This class describes geometric behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "geometric.h"

GeoMetric::GeoMetric() : Entity()
{

}

GeoMetric::~GeoMetric()
{

}

void GeoMetric::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation.y += HALF_PI * deltaTime / 2;
	if (this->rotation.y > TWO_PI) {
		this->rotation.y -= TWO_PI;
	}
}

void GeoMetric::makeSphere(float radius, int lats, int longs)
{
	std::vector<Point3> longcoords;

	float latitude_increment = 360.0f / lats;
    float longitude_increment = 180.0f / longs;

	// create longitudes
    for (float u = 0; u <= 360.0f; u += latitude_increment) {
		Line semicircle;
        for (float t = 0; t <= 180.0f; t += longitude_increment) {
            float x = (float) (radius * sin(t*DEG_TO_RAD) * sin(u*DEG_TO_RAD));
            float y = (float) (radius * cos(t*DEG_TO_RAD));
            float z = (float) (radius * sin(t*DEG_TO_RAD) * cos(u*DEG_TO_RAD));

			semicircle.addPoint(x, y, z);

			// remember points on first latitude to create longitude circles
			if (u == 0) {
				longcoords.push_back(Point3(x,y,z));
			}
        }
		// optionally, some nice colors
		if (u < 0.1f && u > -0.1f) { semicircle.color = GREEN; } // greenwich
		if (u < 180.2f && u > 179.8f) { semicircle.color = GREEN; } // greenwich
		if (u < 90.1f && u > 89.8) { semicircle.color = BLUE; }
		if (u < 270.1f && u > 269.8) { semicircle.color = BLUE; }

		this->addLine(&semicircle);
    }

	// create latitudes
	size_t s = longcoords.size();
	for (size_t i = 0; i < s; i++) {
		float rad = longcoords[i].z;
		float height = longcoords[i].y;

		Line circle;
		for (float u = 0; u <= 360.0f; u += latitude_increment) {
			circle.addPoint(rad * sin(u*DEG_TO_RAD), height, rad * cos(u*DEG_TO_RAD));
			if (height < 0.1f && height > -0.1f) { circle.color = RED; } // equator
		}
		this->addLine(&circle);
	}
	longcoords.clear();
}

void GeoMetric::makeCube(int halfwidth, int halfheight, int halfdepth)
{
	Line front;
	front.color = GREEN;
	front.addPoint(-halfwidth, -halfheight, -halfdepth);
	front.addPoint( halfwidth, -halfheight, -halfdepth);
	front.addPoint( halfwidth,  halfheight, -halfdepth);
	front.addPoint(-halfwidth,  halfheight, -halfdepth);
	front.addPoint(-halfwidth, -halfheight, -halfdepth);
	this->addLine(&front);

	Line back;
	back.color = RED;
	back.addPoint(-halfwidth, -halfheight, halfdepth);
	back.addPoint( halfwidth, -halfheight, halfdepth);
	back.addPoint( halfwidth,  halfheight, halfdepth);
	back.addPoint(-halfwidth,  halfheight, halfdepth);
	back.addPoint(-halfwidth, -halfheight, halfdepth);
	this->addLine(&back);

	Line conn1;
	conn1.color = YELLOW;
	conn1.addPoint(-halfwidth, -halfheight, halfdepth);
	conn1.addPoint(-halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn1);

	Line conn2;
	conn2.color = YELLOW;
	conn2.addPoint( halfwidth, -halfheight, halfdepth);
	conn2.addPoint( halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn2);

	Line conn3;
	conn3.color = YELLOW;
	conn3.addPoint(-halfwidth,  halfheight, halfdepth);
	conn3.addPoint(-halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn3);

	Line conn4;
	conn4.color = YELLOW;
	conn4.addPoint( halfwidth,  halfheight, halfdepth);
	conn4.addPoint( halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn4);
}